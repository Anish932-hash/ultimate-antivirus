# Project Structure

## Overview
The project follows a modular directory structure that aligns with the system architecture, promoting separation of concerns, ease of maintenance, and scalability. It supports multi-language development with clear boundaries between components.

## Root Directory Layout

```
AntivirusProject/
├── .vscode/                    # VS Code workspace settings and extensions
├── build/                      # Build outputs, binaries, and installers
│   ├── debug/
│   ├── release/
│   └── installers/
├── data/                       # Data assets and resources
│   ├── models/                 # Pre-trained AI models (TensorFlow/PyTorch)
│   ├── signatures/             # Malware signature databases
│   ├── configs/                # Default configuration files
│   └── test_samples/           # Safe test files for validation
├── docs/                       # Documentation and specifications
│   ├── api/                    # API reference documentation
│   ├── guides/                 # User and developer guides
│   ├── architecture.md
│   ├── requirements.md
│   └── diagrams/               # Architecture and flow diagrams
├── include/                    # Public C++ header files
│   ├── core/
│   ├── common/
│   └── third_party/
├── lib/                        # Third-party libraries and dependencies
│   ├── boost/                  # Boost C++ libraries
│   ├── tensorflow/             # TensorFlow C++ API
│   ├── opencv/                 # For image processing in AI
│   └── sqlite/                 # SQLite amalgamation
├── scripts/                    # Automation scripts
│   ├── build/                  # Build scripts (CMake, MSBuild)
│   ├── deploy/                 # Deployment and packaging
│   ├── ci/                     # CI/CD pipelines
│   └── tools/                  # Development utilities
├── src/                        # Main source code
│   ├── common/                 # Shared utilities across components
│   │   ├── crypto/             # Cryptographic functions
│   │   ├── logging/            # Centralized logging
│   │   ├── ipc/                # Inter-process communication
│   │   └── utils/              # General utilities
│   ├── core/                   # Core scanning engine (C++)
│   │   ├── scanner/            # File and memory scanning
│   │   ├── monitor/            # Real-time monitoring
│   │   ├── quarantine/         # Threat isolation
│   │   ├── network/            # Network inspection
│   │   └── api/                # Core API interfaces
│   ├── ai/                     # AI/ML engine (Python)
│   │   ├── models/             # ML model definitions
│   │   ├── preprocessing/      # Data preprocessing pipelines
│   │   ├── training/           # Model training scripts
│   │   ├── inference/          # Inference engines
│   │   └── api/                # REST/gRPC API for AI services
│   ├── gui/                    # GUI application (C#)
│   │   ├── App.xaml
│   │   ├── MainWindow.xaml
│   │   ├── views/              # XAML views
│   │   ├── viewmodels/         # MVVM view models
│   │   ├── controls/           # Custom controls
│   │   ├── services/           # GUI services (notifications, etc.)
│   │   └── resources/          # Styles, templates, icons
│   └── updater/                # Update service (C#)
│       ├── client/             # Update client
│       └── server/             # Update server logic
├── tests/                      # Test suites
│   ├── unit/                   # Unit tests (Google Test, NUnit, pytest)
│   │   ├── core/
│   │   ├── ai/
│   │   └── gui/
│   ├── integration/            # Integration tests
│   ├── e2e/                    # End-to-end tests
│   └── performance/            # Performance and load tests
├── tools/                      # Development and analysis tools
│   ├── analyzers/              # Static analysis tools
│   ├── generators/             # Code generation scripts
│   └── profilers/              # Performance profiling tools
├── .gitignore                  # Git ignore rules
├── CMakeLists.txt              # Root CMake configuration
├── Antivirus.sln               # Visual Studio solution file
├── README.md                   # Project overview and setup
├── LICENSE                     # License information
└── .clang-format               # Code formatting rules
```

## Key Design Principles

### Modularity
- Each major component (core, ai, gui) has its own directory with internal sub-structure.
- Shared code resides in `src/common/` to avoid duplication.

### Language Separation
- C++ code in `src/core/` and `include/`
- Python in `src/ai/`
- C# in `src/gui/` and `src/updater/`

### Build System Integration
- CMake handles C++ builds and cross-language dependencies.
- MSBuild for .NET components.
- Separate build directories prevent conflicts.

### Data Management
- Sensitive data (signatures, models) in `data/` with careful version control.
- Test data isolated to prevent accidental deployment.

### Testing Strategy
- Mirrors source structure for easy maintenance.
- Supports automated CI/CD with comprehensive coverage.

This structure ensures the project remains maintainable as it scales, with clear boundaries for team collaboration and automated tooling.