
// #include "stdafx.h"
#include "Parameters.h"

Parameters params;

Parameters::Parameters(void) {
    doEvolution = false;
    getAlmostCorrectNWs = false;
    writeNetworkActivity = false;
    doAllSequencesTest = false;

    outputdir = "3_loops_test/";

    minConnectionWeight = -10;
    maxConnectionWeight = 10;
    timeStep = 1; // ms
    neuronalType = ADX;

    // network
    noOfInputs = noOfSignals = 3;
    noOfinterNeurons = 5;
    noOfOutputs = 1;
    ge_gain = gi_gain = 0.007;

    synapticDelay = 4; // 4
    minWeightThreshold = 0.0;
    maxWeightRhreshold = 0.0;

    // GA
    popSize = 100;
    eliteCount = 5; // 10
    randomizeCount = 5; // 5
    randomizeEveryXGen = 10; // 10
    weightDeletionProb = 0.0; // 0.1
    mutationProb = 0.4; // 10 percent //0.3 (0.1-0.5 6signals)
    signChangeProb = 0.0; // 0.3
    mutationMean = 1; //0.5
    mutationStength = 0.5; // 1.0
    maxGen = 100;
    maxRuns = 10;

    weightReductionProb = 0.2;
    weightReductionStength = 0.1;

    // noise
    noiseVectorSize = 100;
    variationOnSignal = 0;
    variationOnSilence = 0;
    // Gaussian
    gaussianNoiseOnVoltage = true;
    gMean = 0.0;
    gStdDev = 1.0; // 1.0

    // sequence
    letterSize = 6;
    silenctinterval = 24;
    noOfLetters = 1500;
    reevaluateSeq = 10000;
    sequenceSize = noOfLetters * (letterSize + silenctinterval);
}

Parameters::~Parameters(void) {}
