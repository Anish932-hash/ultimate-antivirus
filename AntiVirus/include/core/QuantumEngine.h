#pragma once

#include <complex>
#include <vector>
#include <string>

namespace Core {

class QuantumEngine {

public:

    using Qubit = std::complex<double>;

    std::vector<Qubit> CreateQuantumState(int numQubits);

    bool MeasureThreat(const std::vector<Qubit>& state);

    void EntangleSystems();

    void SuperpositionScan(const std::string& filePath);

    void ApplyHadamardGate(std::vector<Qubit>& state, int targetQubit);

    void ApplyPauliXGate(std::vector<Qubit>& state, int targetQubit);

    void ApplyCNOTGate(std::vector<Qubit>& state, int controlQubit, int targetQubit);

    void QuantumFourierTransform(std::vector<Qubit>& state);

    void ApplyControlledPhaseGate(std::vector<Qubit>& state, int control, int target, double phase);

    void ShorAlgorithm(int number);

    void GroverSearch(const std::vector<Qubit>& oracle);

    void TeleportQubit(const Qubit& qubit);

    void CreateQuantumKeyDistribution();

    void QuantumErrorCorrection(std::vector<Qubit>& state);

};

}