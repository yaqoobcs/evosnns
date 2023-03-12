#include "stdafx.h"
#include "Ga.h"
#include "UtilityFunctions.h"
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;
Ga::Ga(void)
{
	history.clear();
	keepGen0Elites.clear();
	signalSiquence.clear();
	correctIndecies.clear();

}

void Ga::run(vector<Individual>& pop, int genNo)
{
	string signal("ABC");
	int noOfSeq = 6;
	int step = 0;

	vector<char> signalSiquence;
	vector<int> correctIndecies;

	signalSiquence = getRandomSequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
	correctIndecies = getCorrectPatternsMarkers(signalSiquence, signal);


	for (int i = 0; i < pop.size(); i++)
	{

		for (long j = 0; j < signalSiquence.size(); j++)
		{
			step += 1;
			pop[i].setInput(signalSiquence[j], j);
			pop[i].networkStep(step);
		}
		//fitness 
		pop[i].fitness = fitness(pop[i], signalSiquence, correctIndecies);

		//Reset
		step = 0;

		pop[i].outputNeurons[0].spikeBitmap.clear();
		pop[i].outputNeurons[0].voltageBuffer.clear();
		for (int p = 0; p < pop[i].inputNeurons.size(); p++)
			pop[i].inputNeurons[p].voltageBuffer.clear();
		for (int q = 0; q < pop[i].interNeurons.size(); q++)
			pop[i].interNeurons[q].voltageBuffer.clear();



	}

	// sort based on fitness function
	sort(pop.begin(), pop.end(), [](const Individual& lhs, const Individual& rhs)
		{
			return lhs.fitness < rhs.fitness;
		});

	int firstRand = 0, secondRand = 0;

	//tournament selection keep elites
	for (int k = params.eliteCount; k < pop.size(); k++)
	{

		firstRand = getRandomValue(0, pop.size() - 1);
		secondRand = getRandomValue(0, pop.size() - 1);

		if (pop[firstRand].fitness < pop[secondRand].fitness)
		{
			pop[k] = pop[firstRand];
		}
		else
		{
			pop[k] = pop[secondRand];
		}
	}

	//replicate
	for (int rep = params.eliteCount; rep < pop.size(); rep++)
	{
		//	pop[rep].printIndividualMatrix(rep);
		pop[rep].replicate();
		//pop[rep].replicateinterConnections();
		//pop[rep].replicateExceptLoops();
		//	pop[rep].printIndividualMatrix(rep);
	}
	//if(genNo%params.randomizeEveryXGen==1)
	//{
	//	for(int rCount=pop.size()-params.randomizeCount; rCount<pop.size(); rCount++)
	//	{
	//		pop[rCount].randomizeinterconnections();
	//	}
	//}

	signalSiquence.clear();
	correctIndecies.clear();
}

bool Ga::runMinimalWeight(vector<Individual>& pop, int genNo)
{
	string signal("ABC");
	int letterSize = params.letterSize;
	int gapSize = params.silenctinterval;
	int sequenceLength = params.noOfLetters;
	int noOfSeq = 6;
	int step = 0;
	double reward = 0.0, penalty = 0.0, rewardAll = 0.0, penaltyAll = 0.0;

	//srand(100);
	vector<char> signalSiquence = getRandomSequence(signal, sequenceLength, gapSize, letterSize);
	vector<int> correctIndecies = getCorrectPatternsMarkers(signalSiquence, signal);


	for (int i = 0; i < pop.size(); i++)
	{
		//for (int m=0; m<pop[i].outputNeurons.size(); m++)
		//{
		reward = 0.0, penalty = 0.0;rewardAll = 0.0, penaltyAll = 0.0;
		//for(int noS=0; noS<noOfSeq; noS++)
		//{

		for (int j = 0; j < signalSiquence.size(); j++)
		{
			step += 1;
			pop[i].setInput(signalSiquence[j], j);
			pop[i].networkStep(step);
		}

		double rCountint = 0.0, rCountSig = 0.0, pCountint = 0.0, pCountSig = 0.0;

		//fitness 2 from Greans
		int k = 0;
		int sizeHistory = pop[i].outputNeurons[0].spikeBitmap.size();
		for (int j = 0; j < correctIndecies.size(); j++)
		{
			while (k < sizeHistory && k != correctIndecies[j])
			{
				while (signalSiquence[k] != 'Z' && k != correctIndecies[j])
				{
					if (pop[i].outputNeurons[0].spikeBitmap[k])
					{
						pCountSig += 1.0; k++;
					}
					else
					{
						k++;
					}
				}
				while (signalSiquence[k] == 'Z' && k != correctIndecies[j])
				{
					if (pop[i].outputNeurons[0].spikeBitmap[k])
					{
						pCountint += 1.0; k++;
					}
					else
					{
						k++;
					}
				}
				if (pCountint + pCountSig > 0.0)
				{
					pCountint = 0.0; pCountSig = 0.0; penalty += 1.0;
				}
			}
			while (k < sizeHistory && signalSiquence[k] != 'Z')
			{
				if (pop[i].outputNeurons[0].spikeBitmap[k])
				{
					rCountSig += 1.0; k++;
				}
				else
				{
					k++;
				}
			}
			while (k < sizeHistory && signalSiquence[k] == 'Z')
			{
				if (pop[i].outputNeurons[0].spikeBitmap[k])
				{
					rCountint += 1.0; k++;
				}
				else
				{
					k++;
				}
			}
			if (rCountSig + rCountint > 0.0)
			{
				rCountSig = 0.0; rCountint = 0.0;reward += 1.0;
			}
		}
		//normalize reward/fitness 
		pop[i].rewardn = reward / (double)correctIndecies.size();
		pop[i].penaltyn = penalty / (sequenceLength - correctIndecies.size());

		pop[i].reward = reward;
		pop[i].penalty = penalty;

		pop[i].fitness = 1 - (pop[i].rewardn - 4 * pop[i].penaltyn);

		//Reset
		step = 0;
		pop[i].outputNeurons[0].spikeBitmap.clear();
		pop[i].outputNeurons[0].voltageBuffer.clear();
		for (int p = 0; p < pop[i].inputNeurons.size(); p++)
			pop[i].inputNeurons[p].voltageBuffer.clear();
		for (int q = 0; q < pop[i].interNeurons.size(); q++)
			pop[i].interNeurons[q].voltageBuffer.clear();


	}

	// sort based of fitness function
	sort(pop.begin(), pop.end(), [](const Individual& lhs, const Individual& rhs)
		{
			return lhs.fitness < rhs.fitness;
		});

	//keep only perfect
	int wi = 0;
	while (pop[wi].fitness < 0.005)
	{

		pop[wi].sumOfConnectionWeights();
		wi++;

	}
	pop.resize(wi);


	if (wi != 0)
	{

		for (int k = wi; k < params.popSize;k++)
		{
			pop.push_back(pop[getRandomValue(0, wi)]);
		}

		// sort based on weight Sum
		sort(pop.begin(), pop.end(), [](const Individual& lhs, const Individual& rhs)
			{
				return lhs.absWeightSum < rhs.absWeightSum;
			});


		// keep gen0 elites in all gen.
		if (genNo == 0)
		{

			for (int ke = 0; ke < params.eliteCount; ke++)
			{
				keepGen0Elites.push_back(pop[ke]);
			}
		}
		else
		{
			for (int ei = 0; ei < keepGen0Elites.size(); ei++)
			{
				pop.insert(pop.begin(), keepGen0Elites[ei]);
			}
		}

		// sort based on weight Sum
		sort(pop.begin(), pop.end(), [](const Individual& lhs, const Individual& rhs)
			{
				return lhs.absWeightSum < rhs.absWeightSum;
			});
		pop.resize(params.popSize);

		//tournament selection (weight) keep elites
		int firstRand = 0, secondRand = 0;
		for (int k = params.eliteCount; k < pop.size(); k++)
		{

			firstRand = getRandomValue(0, pop.size() - 1);
			secondRand = getRandomValue(0, pop.size() - 1);

			if (pop[firstRand].absWeightSum < pop[secondRand].absWeightSum)
			{
				pop[k] = pop[firstRand];
			}
			else
			{
				pop[k] = pop[secondRand];
			}
		}

		//replicate
		for (int rep = params.eliteCount; rep < pop.size(); rep++)
		{
			pop[rep].replicateByOnlyReducingWeights();
			//	pop[rep].printIndividualMatrix(rep);
			//pop[rep].replicate();
			//pop[rep].replicateinterConnections();
			//pop[rep].replicateExceptLoops();
			//	pop[rep].printIndividualMatrix(rep);
		}
	}
	else
	{
		cout << "wi == 0" << endl;
		return false;
	}
	//if(genNo%params.randomizeEveryXGen==1)
	//{
	//	for(int rCount=pop.size()-params.randomizeCount; rCount<pop.size(); rCount++)
	//	{
	//		pop[rCount].randomizeinterconnections();
	//	}
	//}

	//signalSiquence.clear();
	//correctIndecies.clear();
	return true;
}

void Ga::reEvaluateUserDefinedSequence(Individual& ind)
{
	string signal("ABC");
	string signalSequenceUserDefined("ABACABCBABBCAB");

	signalSiquence = getUserDefinedSequence(signalSequenceUserDefined, params.silenctinterval, params.letterSize);
	correctIndecies = getCorrectPatternsMarkers(signalSiquence, signal);


	long long int step = 0;
	for (long long int j = 0; j < signalSiquence.size(); j++)
	{

		if (step % 90 != 0) //180, 210, 240
		{
			ind.setInput(signalSiquence[j], j);
			ind.networkStep(step);
		}
		else
		{
			ind.resetIndividual();

			ind.setInput(signalSiquence[j], j);
			ind.networkStep(step);
			//ind.outputNeurons[0].spikeBitmap.push_back(false);
			//ind.outputNeurons[0].voltageBuffer.push_back(-58.0);
			//cout << step << endl;
			//Sleep(1000);
		}
		step += 1;
	}
	//	ind.gaussNoiseVector.clear();
	//	ind.gaussNoiseVector.resize(0);
	ind.fitness = fitness(ind, signalSiquence, correctIndecies);

	signalSiquence.clear();
	correctIndecies.clear();
	ind.outputNeurons[0].spikeBitmap.clear();


}

void Ga::reEvaluateOnProblamaticPatternsFound(Individual& ind, string probSignalSequence)
{
	string signal("ABCDEF");

	int sequenceLength = 500000;
	int noOfSeq = 6;
	int step = 0;
	vector<char> signalSiquence = getUserDefinedSequence(probSignalSequence, params.silenctinterval, params.letterSize);
	vector<int> correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);


	//reward=0.0, penalty=0.0;rewardAll=0.0, penaltyAll=0.0;


	for (int j = 0; j < signalSiquence.size(); j++)
	{
		step += 1;
		ind.setInput(signalSiquence[j], j);
		ind.networkStep(step);
	}

}

void Ga::reEvaluateABCD(Individual& ind)
{
	string signal("ABCD");
	//int letterSize = 6; 
	//int gapSize = 16;
	int sequenceLength = 500000;
	int noOfSeq = 6;
	int step = 0;
	double reward = 0.0, penalty = 0.0, rewardAll = 0.0, penaltyAll = 0.0;
	//srand(100);
	vector<char> signalSiquence = getRandomSequenceABCD(signal, sequenceLength, params.silenctinterval, params.letterSize);
	//vector<char> signalSiquence = getUserDefinedSequence("BBABCBBCCCAACABCA", params.silenctinterval, params.letterSize);
	vector<int> correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);


	reward = 0.0, penalty = 0.0;rewardAll = 0.0, penaltyAll = 0.0;


	for (int j = 0; j < signalSiquence.size(); j++)
	{
		step += 1;
		ind.setInput(signalSiquence[j], j);
		ind.networkStep(step);
	}

	double rCountint = 0.0, rCountSig = 0.0, pCountint = 0.0, pCountSig = 0.0;

	//fitness function from Greans
	int k = 0;
	int sizeHistory = ind.outputNeurons[0].spikeBitmap.size();
	for (int j = 0; j < correctIndecies.size(); j++)
	{
		while (k < sizeHistory && k != correctIndecies[j])
		{
			while (signalSiquence[k] != 'Z' && k != correctIndecies[j])
			{
				if (ind.outputNeurons[0].spikeBitmap[k])
				{
					pCountSig += 1.0; k++;
				}
				else
				{
					k++;
				}
			}
			while (signalSiquence[k] == 'Z' && k != correctIndecies[j])
			{
				if (ind.outputNeurons[0].spikeBitmap[k])
				{
					pCountint += 1.0; k++;
				}
				else
				{
					k++;
				}
			}
			if (pCountint + pCountSig > 0.0)
			{
				pCountint = 0.0; pCountSig = 0.0; penalty += 1.0;
			}
		}
		while (k < sizeHistory && signalSiquence[k] != 'Z')
		{
			if (ind.outputNeurons[0].spikeBitmap[k])
			{
				rCountSig += 1.0; k++;
			}
			else
			{
				k++;
			}
		}
		while (k < sizeHistory && signalSiquence[k] == 'Z')
		{
			if (ind.outputNeurons[0].spikeBitmap[k])
			{
				rCountint += 1.0; k++;
			}
			else
			{
				k++;
			}
		}
		if (rCountSig + rCountint > 0.0)
		{
			rCountSig = 0.0; rCountint = 0.0;reward += 1.0;
		}
	}
	//normalize reward/fitness 
	ind.rewardn = reward / (double)correctIndecies.size();
	ind.penaltyn = penalty / (sequenceLength - correctIndecies.size());

	ind.reward = reward;
	ind.penalty = penalty;

	ind.fitness = 1 - (ind.rewardn - 4 * ind.penaltyn);
	ind.outputNeurons[0].spikeBitmap.clear();
}
Ga::~Ga(void)
{
}
