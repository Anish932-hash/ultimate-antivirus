# Database Schema

## Overview
The database uses SQLite for lightweight, embedded storage with encryption enabled via SQLCipher. It supports the antivirus's data requirements for signatures, threat tracking, logging, AI models, and configuration.

## Tables

### signatures
Stores malware signatures for fast lookup during scanning.

```sql
CREATE TABLE signatures (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    hash TEXT UNIQUE NOT NULL,              -- SHA256 hash of malware sample
    signature_type TEXT NOT NULL,           -- 'file', 'behavior', 'network', 'yara'
    description TEXT,                       -- Human-readable description
    severity INTEGER CHECK(severity >= 1 AND severity <= 10), -- Threat severity level
    category TEXT,                          -- 'trojan', 'ransomware', 'spyware', etc.
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    source TEXT                             -- 'local', 'cloud', 'user_defined'
);
```

### threats
Tracks detected threats and their handling.

```sql
CREATE TABLE threats (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    file_path TEXT NOT NULL,                 -- Full path to infected/quarantined file
    threat_type TEXT NOT NULL,               -- 'virus', 'trojan', 'worm', 'ransomware'
    detection_method TEXT NOT NULL,          -- 'signature', 'heuristic', 'ai', 'behavioral'
    confidence REAL CHECK(confidence >= 0.0 AND confidence <= 1.0), -- AI confidence score
    status TEXT DEFAULT 'detected',          -- 'detected', 'quarantined', 'removed', 'ignored'
    ai_model_used TEXT,                      -- Name/version of AI model used
    actions_taken TEXT,                      -- JSON array of actions (quarantine, delete, etc.)
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    user_response TEXT                       -- 'auto', 'manual_allow', 'manual_block'
);
```

### logs
Centralized logging for all components.

```sql
CREATE TABLE logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    level TEXT NOT NULL,                     -- 'debug', 'info', 'warning', 'error', 'critical'
    component TEXT NOT NULL,                 -- 'core', 'ai', 'gui', 'updater', 'network'
    message TEXT NOT NULL,                   -- Log message
    details TEXT,                            -- JSON with additional context
    session_id TEXT,                         -- For grouping related events
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

### ai_models
Metadata for AI/ML models used in detection.

```sql
CREATE TABLE ai_models (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,                      -- Model name (e.g., 'anomaly_detector_v2')
    version TEXT NOT NULL,                   -- Semantic version
    model_path TEXT NOT NULL,                -- Path to model file
    framework TEXT NOT NULL,                 -- 'tensorflow', 'pytorch', 'onnx'
    accuracy REAL CHECK(accuracy >= 0.0 AND accuracy <= 1.0), -- Validation accuracy
    training_data_size INTEGER,              -- Number of samples used in training
    features TEXT,                           -- JSON array of input features
    last_trained DATETIME,                   -- Last training timestamp
    status TEXT DEFAULT 'active',            -- 'active', 'training', 'deprecated', 'failed'
    performance_metrics TEXT                 -- JSON with precision, recall, F1 scores
);
```

### settings
Application configuration and user preferences.

```sql
CREATE TABLE settings (
    key TEXT PRIMARY KEY,                    -- Setting key (e.g., 'scan_schedule')
    value TEXT NOT NULL,                     -- Setting value
    type TEXT NOT NULL,                      -- 'string', 'int', 'bool', 'json'
    category TEXT,                           -- 'general', 'scanning', 'ai', 'gui'
    description TEXT,                        -- Human-readable description
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

### quarantine
Tracks quarantined files and their metadata.

```sql
CREATE TABLE quarantine (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    original_path TEXT NOT NULL,             -- Original file location
    quarantine_path TEXT NOT NULL,           -- Quarantine location
    threat_id INTEGER,                       -- FK to threats table
    file_hash TEXT,                          -- SHA256 of quarantined file
    file_size INTEGER,                       -- File size in bytes
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (threat_id) REFERENCES threats(id) ON DELETE SET NULL
);
```

## Indexes
For optimal query performance:

```sql
CREATE INDEX idx_signatures_hash ON signatures(hash);
CREATE INDEX idx_signatures_type ON signatures(signature_type);
CREATE INDEX idx_threats_path_timestamp ON threats(file_path, timestamp DESC);
CREATE INDEX idx_threats_status ON threats(status);
CREATE INDEX idx_logs_timestamp_level ON logs(timestamp DESC, level);
CREATE INDEX idx_logs_component ON logs(component);
CREATE INDEX idx_ai_models_name_version ON ai_models(name, version DESC);
CREATE INDEX idx_settings_category ON settings(category);
```

## Views
Pre-computed views for common queries:

```sql
-- Active threats view
CREATE VIEW active_threats AS
SELECT * FROM threats WHERE status IN ('detected', 'quarantined');

-- Recent logs view
CREATE VIEW recent_logs AS
SELECT * FROM logs WHERE timestamp > datetime('now', '-7 days') ORDER BY timestamp DESC;

-- Model performance view
CREATE VIEW model_performance AS
SELECT name, version, accuracy, performance_metrics FROM ai_models WHERE status = 'active';
```

## Triggers
Automatic maintenance:

```sql
-- Update timestamp trigger for signatures
CREATE TRIGGER update_signatures_timestamp 
    AFTER UPDATE ON signatures
    BEGIN
        UPDATE signatures SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
    END;

-- Log threat actions
CREATE TRIGGER log_threat_actions
    AFTER UPDATE ON threats
    WHEN OLD.status != NEW.status
    BEGIN
        INSERT INTO logs (level, component, message, details)
        VALUES ('info', 'core', 'Threat status changed', 
                json_object('threat_id', NEW.id, 'old_status', OLD.status, 'new_status', NEW.status));
    END;
```

## Migration Strategy
- Versioned schema migrations stored in `data/migrations/`
- Automatic migration on startup
- Backward compatibility maintained

This schema provides a robust foundation for storing and retrieving antivirus data efficiently, supporting advanced features like AI model tracking and comprehensive logging.