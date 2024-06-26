#include "MesmerFlags.h"

namespace mesmer {
  MesmerFlags::MesmerFlags() : testDOSEnabled(false),
    testRateConstantEnabled(false),
    microRateEnabled(false),
    grainBoltzmannEnabled(false),
    grainDOSEnabled(false),
    grainTSsosEnabled(false),
    cyclePrintGrainDOS(false),
    cellDOSEnabled(false),
    cyclePrintCellDOS(false),
    reactionOCSEnabled(false),
    kfEGrainsEnabled(false),
    kbEGrainsEnabled(false),
    TunnellingCoeffEnabled(false),
    CrossingCoeffEnabled(false),
    cellFluxEnabled(false),
    grainFluxEnabled(false),
    rateCoefficientsOnly(false),
    useTheSameCellNumber(true),
    grainedProfileEnabled(false),
    speciesProfileEnabled(false),
    printPhenomenologicalEvolution(false),
    viewEvents(false),
    shortestTimeOfInterest(1.0e-11),
    maxEvolutionTime(1.0e+05),
    printEigenValuesNum(0),
    printEigenVectors(false),
    printReactionOperatorNum(0),
    printSinkFluxes(false),
    allowSmallerDEDown(false),
    showCollisionOperator(0),
    useDOSweightedDT(false),
    punchSymbols(),
    punchNumbers(),
    punchFileName(),
    overwriteXmlAnalysis(false),
    autoSetMaxEne(false),
    // Default poulation threshold for automatic calculation of energy above the top barrier.
    popThreshold(1.0e-5),
    bForceMacroDetailedBalance(false),
    bIsSystemSecondOrder(false),
    bIndependentErrors(true),
    useOrigFreqForZPECorrection(true),
    bIncludeDiffusiveLoss(false),
    useTraceWeighting(false),
    updateTraceWeights(false),
    printZMatrixRatios(false),
    bThermoTableContribute(false)
  {}
}//namespace

