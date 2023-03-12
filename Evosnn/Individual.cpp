#include "stdafx.h"
#include "Individual.h"
#include <time.h>
using namespace std;

Individual::Individual(void)
{
	fitness=0.0, reward=0.0; penalty=0.0, rewardn=0.0, penalty=0.0;
	rank=0;
	absWeightSum=0.0;
	noOfNodesInNetwork=0;
	inputNeurons.clear();
	interNeurons.clear();
	outputNeurons.clear();
	gaussNoiseVector.clear();
	//individualMatrix.clear();
	missIdentifiedPatterns.clear();
}
Individual::~Individual(void)
{
//	for(int i = 0; i < noOfNodesInNetwork; ++i)
//		delete indMatrix[i];
//	delete indMatrix;
}
void Individual::deleteIndMatrix()
{
		//for(int i = 0; i < noOfNodesInNetwork; ++i)
		//	delete indMatrix[i];
		//delete indMatrix;
}



vector<vector<double>> Individual::getIndividualMatrix()
{
	return indMatrix;

}

void Individual::printIndividualMatrix(int gNo, int iRun)
{
	ofstream ofs;
	ofs.open("indMatrix.dat", ofstream::out|ofstream::app);
	ofs<<"run:"<<iRun<<" gen:"<<gNo<<"  fitness = "<<fitness<<"\tReward = "<<reward<<"\tPenalty = "<<penalty<<"\tWeight sum = "<<absWeightSum<<endl;
	//wxString tempstr;
	for (int i = 0; i<noOfNodesInNetwork; i++)
	{
		for (int j = 0; j < noOfNodesInNetwork; j++)
		{
			ofs<<indMatrix[i][j]<<"\t";
		}
		ofs<<endl;
	}
	ofs<<"---------X---------X---------X---------X---------X---------X"<<endl<<endl;
	ofs.close();
}

void Individual::outputNetworkActivity()
{
	ofstream ofs;
	ofs.open("netActivity.dat", ofstream::out|ofstream::app);
	//ofs<<"#No\t Out\t A\t B\t C\t D\t E\t N0\t N1\t N2\t N3\t N4"<<endl;
	//ofs<<"-1\t -70\t -100\t -100\t -100\t -100\t -100\t -70\t -70\t -70\t -70\t -70"<<endl;

	ofs << "#No\t Out\t A\t B\t C\t N0\t N1\t N2" << endl;
	ofs << "-1\t -70\t -100\t -100\t -100\t -70\t -70\t -70" << endl;
	cout << outputNeurons[0].voltageBuffer.size() << endl;
	//wxString tempstr;
	for (int i=0; i< this->outputNeurons[0].voltageBuffer.size(); i++)
	{
		ofs<<i<<"\t"<<outputNeurons[0].voltageBuffer[i]<<"\t";
		for(int inpN=0; inpN<inputNeurons.size(); inpN++)
			ofs<<inputNeurons[inpN].voltageBuffer[i]<<"\t";
		for(int intN=0; intN<interNeurons.size(); intN++)
			ofs<<interNeurons[intN].voltageBuffer[i]<<"\t";
		ofs<<endl;

	}
	ofs.close();

}

void Individual::readIndividualMatrix(string fname)
{
	indMatrix.clear();
	//vector<vector<double>> indMat;
	string line;
	double value;

	// read in matrix

		ifstream file(fname);
		if (file.fail()) {
			cout << "adj_matrix of the network not found, change the path";
			exit(1);
		}
		else
		{
			while (std::getline(file, line))
			{
				vector<double> row;
				std::stringstream iss(line);
				while (iss >> value)
				{
					row.push_back(value);
				}
				indMatrix.push_back(row);
			}
		}

}
void Individual::initializeMatrix(int size)
{

	int no_of_cols = size;
	int no_of_rows = size;
	double initial_value = 0.0;
	std::vector<std::vector<int>> matrix;
	indMatrix.resize(no_of_rows, std::vector<double>(no_of_cols, initial_value));

}

//void Individual::initializeMatrix(int size)
//{
//	indMatrix = new double*[size];
//
//	for(int i = 0; i < size; ++i)
//		indMatrix[i] = new double[size]; // build rows
//
//	for(int i = 0; i < size; ++i)
//	{
//		for(int j = 0; j < size; ++j)
//		{
//			indMatrix[i][j]=0.0;
//		}
//	}
//
//
//}
void Individual::setInput(char inputSignal, long int index)
{
	for (int i=0; i<this->inputNeurons.size(); i++)
	{
		this->inputNeurons[i].voltage=-100;
		if (params.testIndMode)
		this->inputNeurons[i].voltageBuffer.push_back(-100);
	}
	if (inputSignal=='A') //input A
	{
		this->inputNeurons[0].voltage = 0.0;
		if (params.testIndMode)
		this->inputNeurons[0].voltageBuffer[index]=0.0;
	}
	else if (inputSignal=='B') //input B
	{
		this->inputNeurons[1].voltage=0.0;
		if (params.testIndMode)
		this->inputNeurons[1].voltageBuffer[index]=0.0;
	}
	else if (inputSignal=='C') // input C
	{
		this->inputNeurons[2].voltage=0.0;
		if (params.testIndMode)
		this->inputNeurons[2].voltageBuffer[index]=0.0;
	}
	else if (inputSignal=='D') // input D
	{
		this->inputNeurons[3].voltage=0.0;
		if (params.testIndMode)
		this->inputNeurons[3].voltageBuffer[index]=0.0;
	}
	else if (inputSignal=='E') // input E
	{
		this->inputNeurons[4].voltage=0.0;
		if (params.testIndMode)
		this->inputNeurons[4].voltageBuffer[index]=0.0;
	}
	else if (inputSignal == 'F') // input F
	{
		this->inputNeurons[5].voltage = 0.0;
		if (params.testIndMode)
		this->inputNeurons[5].voltageBuffer[index] = 0.0;
	}
}
void Individual::setGap()
{
	for (int i=0; i<inputNeurons.size(); i++)
	{
		inputNeurons[i].voltage=-100;
	}

}

void Individual::resetIndividual()
{
	
	for (int in_n = 0; in_n < interNeurons.size(); in_n++)
	{
		interNeurons[in_n].voltage = interNeurons[in_n].cUnit.resetVoltage();
		interNeurons[in_n].adaptation = interNeurons[in_n].cUnit.resetAdaptation(interNeurons[in_n].adaptation);
	//	interNeurons[in_n].exConductance = 0;
	//	interNeurons[in_n].inConductance = 0;

	}

	for (int out_n = 0; out_n < outputNeurons.size(); out_n++)
	{
		outputNeurons[out_n].voltage = outputNeurons[out_n].cUnit.resetVoltage();
		outputNeurons[out_n].adaptation = outputNeurons[out_n].cUnit.resetAdaptation(outputNeurons[out_n].adaptation);
	//	outputNeurons[out_n].exConductance = 0; 
	//	outputNeurons[out_n].inConductance = 0;

	}

}

void Individual::networkStep(long long int stepNo)
{
	for (int n=0; n<interNeurons.size(); n++)
	{
		
		Neuron &currNeuron = interNeurons[n];

		if (currNeuron.cUnit.hasSpike(currNeuron.voltage))
		{
			currNeuron.cUnit.hasSpiked=true;
			currNeuron.voltage=currNeuron.cUnit.resetVoltage();
			currNeuron.adaptation=currNeuron.cUnit.resetAdaptation(currNeuron.adaptation);
			currNeuron.refrectoryPeriod=currNeuron.cUnit.absRefractoryTime;
			if (params.testIndMode)
			{
				currNeuron.voltageBuffer.push_back(currNeuron.voltage);
				currNeuron.spikeBitmap.push_back(true);

			}

			currNeuron.cUnit.spikeCount++;
		}
		else
		{
			if (currNeuron.refrectoryPeriod<=0)
			{
				double tempVoltage=currNeuron.voltage;
				currNeuron.voltage=currNeuron.cUnit.updateVoltage(currNeuron.voltage, currNeuron.exConductance, currNeuron.inConductance, currNeuron.adaptation);
				currNeuron.adaptation=currNeuron.cUnit.updateAdaptation(currNeuron.adaptation, tempVoltage);
				//if noise add to voltage
				if (params.gaussianNoiseOnVoltage)
				{
					if (gaussNoiseVector.size()==0)
						gaussNoiseVector=getGaussianValueWithGivenMeanAndSD(params.gMean, params.gStdDev, params.noiseVectorSize);
					else
						currNeuron.voltage+=gaussNoiseVector[(int)getRandomValue(0,gaussNoiseVector.size()-1)];

				}
				//set peak to V_spike
				if (currNeuron.cUnit.hasSpike(currNeuron.voltage))
				{
					currNeuron.voltage=currNeuron.cUnit.Vspike;
				}
			}
			else //refractory period
			{
				currNeuron.refrectoryPeriod--;
				//if noise
			}
			if (params.testIndMode)
			{
				currNeuron.voltageBuffer.push_back(currNeuron.voltage);
				currNeuron.spikeBitmap.push_back(false);
			}
		}

		currNeuron.exConductance=currNeuron.cUnit.updateExcitatoryCond(currNeuron.exConductance);
		currNeuron.inConductance=currNeuron.cUnit.updateInhibitoryCond(currNeuron.inConductance);

		//input conductance from connected inter neurons 
		for (int interConn=0; interConn<interNeurons.size(); interConn++)
		{
			double connWeight = indMatrix[noOfInputs+interConn][noOfInputs+n]; //chnage row, fixed col
			if (interNeurons[interConn].cUnit.hasSpike(interNeurons[interConn].voltage))
			{
			/*
				//delay on loops
				if (noOfInputs+interConn == noOfInputs+n)
				{
					//synaptic delay 
					currNeuron.synapticDelayBuffer +=params.synapticDelay;
				}
				else
				{ 
					*/
					
					if (connWeight>0)
					{
						currNeuron.exConductance+= params.ge_gain*connWeight;
					}
					else if(connWeight<0)
					{
						currNeuron.inConductance+=params.gi_gain*(-connWeight);
					}
				//} // else: synaptic delay
			}
			/*
			// delay on loops
			if ((noOfInputs+interConn == noOfInputs+n) && currNeuron.synapticDelayBuffer>0)
			{
				currNeuron.synapticDelayBuffer--;
				currNeuron.delayCount++;
				if (currNeuron.delayCount==params.synapticDelay)
				{
					if (connWeight>0)
					{
						currNeuron.exConductance+= params.ge_gain*connWeight;
					}
					else if(connWeight<0)
					{
						currNeuron.inConductance+=params.gi_gain*(-connWeight);
					}
					currNeuron.delayCount=0;
				}
			}	*/	
		}
		
		//input conductance from input neurons 
		for (int inputConn=0; inputConn<inputNeurons.size(); inputConn++)
		{
			double connWeight = indMatrix[inputConn][noOfInputs+n]; //chnage row, fixed col
			if (inputNeurons[inputConn].cUnit.hasSpike(inputNeurons[inputConn].voltage))
			{
				if (connWeight>0)
				{
					currNeuron.exConductance+= params.ge_gain*connWeight;
				}
				else if(connWeight<0)
				{
					currNeuron.inConductance+=params.gi_gain*(-connWeight);
				}
			}

		}
		//voltage
	}
	this->activateOutput(stepNo);

}
void Individual::activateOutput(long long int stepNo)
{
	for (int out_n=0; out_n<outputNeurons.size(); out_n++)
	{
		Neuron &outputNeuron= outputNeurons[out_n];

	if (outputNeuron.cUnit.hasSpike(outputNeuron.voltage))
	{
		outputNeuron.voltage=outputNeuron.cUnit.resetVoltage();
		outputNeuron.adaptation=outputNeuron.cUnit.resetAdaptation(outputNeuron.adaptation);
		outputNeuron.refrectoryPeriod=outputNeuron.cUnit.absRefractoryTime;
		outputNeuron.spikeBitmap.push_back(true);
		if (params.testIndMode)
		outputNeuron.voltageBuffer.push_back(outputNeuron.voltage); //on for writing file

		outputNeuron.cUnit.spikeCount++;
	}
	else
	{
		if (outputNeuron.refrectoryPeriod<=0)
		{
			double tempVoltage= outputNeuron.voltage;
			outputNeuron.voltage=outputNeuron.cUnit.updateVoltage(outputNeuron.voltage, outputNeuron.exConductance, outputNeuron.inConductance, outputNeuron.adaptation);
			outputNeuron.adaptation=outputNeuron.cUnit.updateAdaptation(outputNeuron.adaptation, tempVoltage);
			//if noise add here
			if (params.gaussianNoiseOnVoltage)
			{
				if (gaussNoiseVector.size()==0)
					gaussNoiseVector=getGaussianValueWithGivenMeanAndSD(params.gMean, params.gStdDev, params.noiseVectorSize);
				else
					outputNeuron.voltage+=gaussNoiseVector[(int)getRandomValue(0,gaussNoiseVector.size()-1)];
			}
			//set peak to V_spike
			if (outputNeuron.cUnit.hasSpike(outputNeuron.voltage))
			{
				outputNeuron.voltage=outputNeuron.cUnit.Vspike;
			}

		}
		else
		{
			//refractory period 
			outputNeuron.refrectoryPeriod--;
		}
		if (params.testIndMode)
		outputNeuron.voltageBuffer.push_back(outputNeuron.voltage);
		outputNeuron.spikeBitmap.push_back(false);

	}

	outputNeuron.exConductance=outputNeuron.cUnit.updateExcitatoryCond(outputNeuron.exConductance);
	outputNeuron.inConductance=outputNeuron.cUnit.updateInhibitoryCond(outputNeuron.inConductance);


		for (int outConn=0; outConn<interNeurons.size(); outConn++) //max conn on output = no. of interneurons
		{
			double connWeight= indMatrix[noOfInputs+outConn][noOfInputs+noOfinterNeurons+out_n];
			if (interNeurons[outConn].cUnit.hasSpike(interNeurons[outConn].voltage))
			{
				if (connWeight>0)
				{
					outputNeuron.exConductance+= params.ge_gain*connWeight;
				}
				else if(connWeight<0)
				{
					outputNeuron.inConductance+=params.gi_gain*(-connWeight);
				}
			}

		}
	//outputVoltage
	}
}
void Individual::makeIndividualWithFixedLoops(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs)
{
	noOfInputs=noInputs; 
	noOfinterNeurons=nointerNeurons;
	noOfOutputNeurons=noOutputs;
	//create Neuron array
	Neuron neuron;
	neuron.cUnit.nModel=ntype;
	inputNeurons.clear();interNeurons.clear();outputNeurons.clear();
	neuron.voltage=0.0;
	for (int i=0; i < noOfInputs; i++)
		inputNeurons.push_back(neuron);
	neuron.voltage=-70.0;
	for (int i=0; i<noOfinterNeurons; i++)
		interNeurons.push_back(neuron);
	for (int i=0; i<noOfOutputNeurons; i++)
		outputNeurons.push_back(neuron);

	noOfNodesInNetwork= noInputs+nointerNeurons+noOutputs;
	initializeMatrix(noOfNodesInNetwork);

	double tempmat[7][7]=
	{{0,	0,	0,	0,		2.0,	0,		0},
	{0,		0,	0,	0,		-5.0,	1.0,	0},
	{0,		0,	0,	2.0,	0,		0,		0},
	{0,		0,	0,	0,		0,		1.0,	1.0},
	{0,		0,	0,	0,		3.0,	1.0,	1.0},
	{0,		0,	0,	0,		1.0,	4.0,	0},
	{0,		0,	0,	0,		0,		0,		0}};

	for (int i=0; i<7; i++)
	{
		for (int j=0; j<7; j++)
		{
			indMatrix[i][j]=tempmat[i][j];
		}
	}

	for (int i = noOfInputs; i < indMatrix.size(); i++)
	{
		for (int j = noOfInputs; j < indMatrix.size(); j++)
		{
			if (indMatrix[i][j]!=0 && indMatrix[i][j]!=3.0 && indMatrix[i][j]!=4.0)
			{
				indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
			}

		}

	}
	//connections among inter-neurons 

	//for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	//{
	//	for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++) //noOfInputs+1 (select two0.00 columns)
	//	{
	//		if (indMatrix[i][j]!=0)
	//		{
	//			indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
	//		}

	//	}
	//}

}
void Individual::makeIndividualWithFixedInputOutputConnections(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs)
{
	noOfInputs=noInputs; 
	noOfinterNeurons=nointerNeurons;
	noOfOutputNeurons=noOutputs;
	//create Neuron array
	Neuron neuron;
	neuron.cUnit.nModel=ntype;
	inputNeurons.clear();interNeurons.clear();outputNeurons.clear();
	neuron.voltage=0.0;
	for (int i=0; i < noOfInputs; i++)
		inputNeurons.push_back(neuron);
	neuron.voltage=-70.0;
	for (int i=0; i<noOfinterNeurons; i++)
		interNeurons.push_back(neuron);
	for (int i=0; i<noOfOutputNeurons; i++)
		outputNeurons.push_back(neuron);

	noOfNodesInNetwork= noInputs+nointerNeurons+noOutputs;
	initializeMatrix(noOfNodesInNetwork);

	if (params.testIndMode)
	readIndividualMatrix("Topology/Top_3.dat");
	if (!params.testIndMode)
		readIndividualMatrix("Topology/Top_3.dat");
	

}
void Individual::makeRandomIndividual(NeuronType ntype, int noInputs, int nointerNeurons, int noOutputs)
{
	noOfInputs=noInputs; 
	noOfinterNeurons=nointerNeurons;
	noOfOutputNeurons=noOutputs;
	//create Neuron array
	Neuron neuron;
	neuron.cUnit.nModel=ntype;
	inputNeurons.clear();interNeurons.clear();outputNeurons.clear();
	neuron.voltage=0.0;
	for (int i=0; i < noOfInputs; i++)
		inputNeurons.push_back(neuron);
	neuron.voltage=-70.0;
	for (int i=0; i<noOfinterNeurons; i++)
		interNeurons.push_back(neuron);
	for (int i=0; i<noOfOutputNeurons; i++)
		outputNeurons.push_back(neuron);

	noOfNodesInNetwork= noInputs+nointerNeurons+noOutputs;
	initializeMatrix(noOfNodesInNetwork);
	//create weight matrix 
	//srand(time(0));                     
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
		}
	}


}

void Individual::replicateByOnlyReducingWeights()
{
	double randValue=0.0;
	//Mutate Weights
	for (int i = 0; i < indMatrix.size(); i++)
	{
		for (int j = 0; j < indMatrix.size(); j++) // start from noOfInputs
		{

			if (indMatrix[i][j]!=0.0)			
			{
				randValue = getRandomValue(0,1);
				if(params.weightReductionProb>randValue)
				{
					if (indMatrix[i][j]>0.0)
						indMatrix[i][j] += getRandomValue(-1*params.weightReductionStength, 0);
					else
						indMatrix[i][j] += getRandomValue(0,params.weightReductionStength);
					
				}
					
			}

		}
}
}
void Individual::replicateExceptLoops()
{
	double randValue=0.0;
	//Mutate Weights
	for (int i = noOfInputs; i < indMatrix.size(); i++)
	{
		for (int j = noOfInputs; j < indMatrix.size(); j++)
		{
			
			if (indMatrix[i][j]!=0.0 && indMatrix[i][j]!=3.0 && indMatrix[i][j]!=4.0)			
			{
				randValue = getRandomValue(0,1);
				if(params.mutationProb>randValue)
					indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
			}

		}
	}

	//mutate sign 
	for (int i = noOfInputs; i < indMatrix.size(); i++)
	{
		for (int j = noOfInputs; j < indMatrix.size(); j++)
		{
			if (indMatrix[i][j]!=0.0 && indMatrix[i][j]!=3.0 && indMatrix[i][j]!=4.0)
			{
				randValue = getRandomValue(0,1);
				if(params.signChangeProb>randValue)
					indMatrix[i][j] *= -1;
			}
		}
	}

}
void Individual::randomizeinterconnections()
{
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{

					indMatrix[i][j] = getRandomValue(params.minConnectionWeight, params.maxConnectionWeight);
			}

		}
	}
}
void Individual::replicateinterConnections()
{
	//connections among inter-neurons 
	double randValue=0.0;
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{
				randValue = getRandomValue(0,1);
				if(params.mutationProb>randValue)
					indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
			}

		}
	}


	////connections among inter-neurons //mutate sign
	//for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	//{
	//	for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
	//	{
	//		if (indMatrix[i][j]!=0.0)
	//		{
	//			randValue = getRandomValue(0,1);
	//			if(params.signChangeProb>randValue)
	//				indMatrix[i][j] *= -1;
	//		}
	//	}
	//}

}

void Individual::replicate()
{
	//srand(time(0));     
	double randValue=0.0;
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{
			randValue = getRandomValue(0,1);
			//Mutate Weights
			if (params.mutationProb>randValue)
			{
				//if(indMatrix[i][j]>params.maxConnectionWeight||indMatrix[i][j]<params.minConnectionWeight)
					indMatrix[i][j] += getRandomValue(-1.0*params.mutationStength, params.mutationStength);
				//else
				//	indMatrix[i][j]=0.0;
			}
			}
			////Mutate Sign
			//if (params.signChangeProb>randValue)
			//{
			//	indMatrix[i][j] *=-1;
			//}
			////Remove low weights
			//if (indMatrix[i][j]<params.minConnectionWeight||indMatrix[i][j]>params.maxConnectionWeight)
			//{
			//	indMatrix[i][j]=0;
			//}

		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{
			randValue = getRandomValue(0,1);
			//Mutate Weights
			if (params.mutationProb>randValue)
			{
				//if(indMatrix[i][j]>params.maxConnectionWeight||indMatrix[i][j]<params.minConnectionWeight)
					indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
				//else
				//	indMatrix[i][j]=0.0;
			}
			}
			////Mutate Sign
			//if (params.signChangeProb>randValue)
			//{
			//	indMatrix[i][j] *=-1;
			//}
			////Remove low weights
			//if (indMatrix[i][j]<params.minConnectionWeight||indMatrix[i][j]>params.maxConnectionWeight)
			//{
			//	indMatrix[i][j]=0;
			//}
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{
			randValue = getRandomValue(0,1);
			//Mutate Weight
			if (params.mutationProb>randValue)
			{
				//if(indMatrix[i][j]>params.maxConnectionWeight||indMatrix[i][j]<params.minConnectionWeight)
					indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
				//else
					//indMatrix[i][j]=0.0;
			}
			}
			////Mutate Sign 
			//if (params.signChangeProb>randValue)
			//{
			//	indMatrix[i][j] *=-1;
			//}
			////remove low weights 
			//if (indMatrix[i][j]<params.minConnectionWeight||indMatrix[i][j]>params.maxConnectionWeight)
			//{
			//	indMatrix[i][j]=0;
			//}
		}
	}
//	mutateWeight();
//	mutateSign();
//	removeLowWeights();
//	deleteWeight();

}
void Individual::deleteWeight()
{
	//srand(time(0));     
	double randValue=0;
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.weightDeletionProb>randValue)
			{
				indMatrix[i][j] = 0;
			}

		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.weightDeletionProb>randValue)
			{
				indMatrix[i][j] = 0;
			}
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.weightDeletionProb>randValue)
			{
				indMatrix[i][j] = 0;
			}
		}
	}

}
void Individual::mutateWeight()
{
	//srand(time(0));     
	double randValue=0;
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.mutationProb>randValue)
			{
				indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
			}

		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.mutationProb>randValue)
			{
				indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
			}
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.mutationProb>randValue)
			{
				indMatrix[i][j] += getRandomValue(-1*params.mutationStength, params.mutationStength);
			}
		}
	}

}
void Individual::mutateSign()
{
	//srand(time(0));     
	double randValue=0;
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.signChangeProb>randValue)
			{
				indMatrix[i][j] *=-1;
			}

		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.signChangeProb>randValue)
			{
				indMatrix[i][j] *=-1;
			}
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			randValue = getRandomValue(0,1);
			if (params.signChangeProb>randValue)
			{
				indMatrix[i][j] *=-1;
			}
		}
	}

}
void Individual::removeLowWeights()
{
	//srand(time(0));     
	double randValue=0;
	//input connects inter-neurons
	for (int i=0; i<noOfInputs; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
		
			if (indMatrix[i][j]>params.minConnectionWeight&&indMatrix[i][j]<params.maxConnectionWeight)
			{
				indMatrix[i][j]=0;
			}

		}
	}

	//connections among inter-neurons 

	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs; j < noOfInputs+noOfinterNeurons; j++)
		{
			if (indMatrix[i][j]>params.minConnectionWeight&&indMatrix[i][j]<params.maxConnectionWeight)
			{
				indMatrix[i][j]=0;
			}
		}
	}

	//interneurons to output
	for (int i = noOfInputs; i < noOfInputs+noOfinterNeurons; i++)
	{
		for (int j = noOfInputs+noOfinterNeurons; j < noOfNodesInNetwork; j++)
		{
			if (indMatrix[i][j]>params.minConnectionWeight&&indMatrix[i][j]<params.maxConnectionWeight)
			{
				indMatrix[i][j]=0;
			}
		}
	}

}

void Individual::sumOfConnectionWeights()
{
	absWeightSum=0.0;
	noOfNodesInNetwork=noOfInputs+noOfinterNeurons+noOfOutputNeurons;
	for (int i = 0; i < indMatrix.size(); i++)
	{
		for (int j = noOfInputs; j < indMatrix.size(); j++)
		{
			if (indMatrix[i][j]!=0.0)			
			{
				this->absWeightSum+=abs(indMatrix[i][j]);
			}

		}

	}
}