#include "stdafx.h"
#include "Parameters.h"

Parameters params;

Parameters::Parameters(void)
{

	testIndMode = false;

	minConnectionWeight = -5; 
	maxConnectionWeight = 5;
	timeStep=1; //ms
	neuronalType=ADX;
	
	//network 
	noOfInputs=3;
	noOfinterNeurons=3;
	noOfOutputs=1;
	ge_gain=gi_gain=0.007;

	synapticDelay=4;
	minWeightThreshold=0.0; 
	maxWeightRhreshold=0.0;

	//GA
	popSize=100;
	eliteCount=10;
	randomizeCount=5;
	randomizeEveryXGen=10;
	weightDeletionProb=0.1;
	mutationProb= 0.1; //10 percent
	signChangeProb=0.1;
	mutationStength = 2.0;
	maxGen=100;

	weightReductionProb = 0.2; 
	weightReductionStength = 1.0;

	//noise
	noiseVectorSize = 10000;
	variationOnSignal=0;
	variationOnSilence=0;
	//Gaussian
	gaussianNoiseOnVoltage=false;
	gMean=0.0;
	gStdDev=2.0;

	//sequence 
	letterSize = 6;
	silenctinterval = 24;
	noOfLetters = 5000;
	sequenceSize= noOfLetters*(letterSize+silenctinterval);
}


Parameters::~Parameters(void)
{
}
