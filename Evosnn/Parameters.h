#pragma once
#include "typedefs.h"

class Parameters
{
public:
	Parameters(void);
	~Parameters(void);

	bool testIndMode;
	int minConnectionWeight; 
	int maxConnectionWeight;
	double timeStep;
	NeuronType neuronalType;
	int noOfInputs; 
	int noOfinterNeurons; 
	int noOfOutputs;
	double ge_gain, gi_gain;
	
	int synapticDelay;
	double minWeightThreshold; 
	double maxWeightRhreshold;

	//GA
	int popSize;
	int eliteCount;
	int randomizeCount;
	int randomizeEveryXGen;
	double weightDeletionProb;
	double mutationProb; 
	double signChangeProb;
	double mutationStength;
	int maxGen;
	double weightReductionProb; 
	double weightReductionStength;
	
	//noise
	int variationOnSignal;
	int variationOnSilence;
	//Gaussian Noise
	bool gaussianNoiseOnVoltage; 
	double gMean;
	double gStdDev;

	//sequence 
	int letterSize;
	int silenctinterval;
	long double noOfLetters;
	long int sequenceSize;
	long int noiseVectorSize; 


};

