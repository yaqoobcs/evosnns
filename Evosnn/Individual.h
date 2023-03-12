#pragma once
#include <vector>
#include "UtilityFunctions.h"
#include "Parameters.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Neuron.h"


using namespace std;
extern Parameters params;
class Individual
{
private: 
	
public:
	double long fitness;
	double long rewardn, penaltyn;
	double reward, penalty;
	double absWeightSum;
	int rank;
	std::vector<std::vector<double>> indMatrix;
	//double** indMatrix;
	vector<Neuron> inputNeurons;
	vector<Neuron> interNeurons; 
	vector<Neuron> outputNeurons; 
	int noOfInputs, noOfinterNeurons, noOfOutputNeurons; 
	int noOfNodesInNetwork;
	vector<double> gaussNoiseVector;
	vector<string> missIdentifiedPatterns; 

	Individual(void);
	~Individual(void);

	void initializeMatrix(int size);
	vector<vector<double>> getIndividualMatrix();
	void printIndividualMatrix(int gNo,int irun);	
	void outputNetworkActivity();
	void readIndividualMatrix(string fname);
	void makeRandomIndividual(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs);
	void makeIndividualWithFixedInputOutputConnections(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs);
	void makeIndividualWithFixedLoops(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs);
	void replicate();
	void replicateinterConnections();
	void randomizeinterconnections();
	void replicateExceptLoops();
	void replicateByOnlyReducingWeights();
	void deleteWeight();
	void mutateWeight();
	void mutateSign();
	void removeLowWeights();
	void deleteIndMatrix();
	void networkStep(long long int stepNo);
	void activateOutput(long long int stepNo);
	void setInput(char inputSignal, long int index);
	void setGap();
	void sumOfConnectionWeights();
	void resetIndividual();

	
};

