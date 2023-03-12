// Evosnn.cpp : Defines the entry point for the console application.
//ABC 3 signals 

#include "stdafx.h"
#include "Individual.h"
#include "Ga.h"
#include <time.h>
#include <random>
struct PatternFrequencyPair
{
	string pattern;
	int freq;
	void clear()
	{
		pattern = "";
		freq = 0;
	}
};

void testIndividual();
void evolve();
using namespace std;

void countFreq(vector<string> arr, int n);
vector<PatternFrequencyPair> countFreqWriteToFile(vector<string> arr, int n);

int _tmain(int argc, _TCHAR* argv[])
{
	if (params.testIndMode)
		testIndividual();
	if (!params.testIndMode)
		evolve();

	getchar();
	return 0;
}
void evolve()
{
	int noOfGen = params.maxGen;
	double mutProb = params.mutationProb;
	double mutStr = params.mutationStength;

	for (int indRun = 0; indRun < 100; indRun++)
	{
		cout << "run: " << indRun << endl;
		vector<Individual> individuals;
		// create population of Ind
		for (int i = 0; i < params.popSize; i++)
		{
			Individual ind;
			ind.makeIndividualWithFixedInputOutputConnections(ADX, 3, 3, 1);

			individuals.push_back(ind);
			//ind.printIndividualMatrix(i);
			//ind.deleteIndMatrix();
		}
		Ga ga; bool converged = false;
		int indNo = 0;

		params.mutationProb = mutProb;
		params.mutationStength = mutStr;
		//params.noOfLetters=1000;

		for (int i = 0; i < noOfGen; i++)
		{

			ga.run(individuals, i);
			cout << i << "-fitness = " << individuals[indNo].fitness << "\tRewardn = " << individuals[indNo].rewardn << "\tPenaltyn = " << individuals[indNo].penaltyn << "\tTrue Positive = " << individuals[indNo].reward << "\tFalse Positive = " << individuals[indNo].penalty << endl;

			cout << endl;
			individuals[indNo].missIdentifiedPatterns.clear();

			if (individuals[indNo].fitness < 0.0001 && !converged)
			{
				//params.noOfLetters=3000;
				cout << "converged" << endl;
				converged = true;
				noOfGen = i + 30.0;
			}
			//cout<<i<<"-fitness = "<<individuals[0].fitness<<endl;
		}
		//print network AdjMatrix
		individuals[indNo].printIndividualMatrix(noOfGen, indRun);



		individuals.clear();
		converged = false;
		noOfGen = params.maxGen;
	}

}

void testIndividual()
{
	Individual ind;
	for (int itr = 0; itr < 1; itr++)
	{

		ind.makeIndividualWithFixedInputOutputConnections(ADX, 3, 3, 1);

		Ga ga;

		//string probPatternsSequence;
		ga.reEvaluateUserDefinedSequence(ind);
		countFreq(ind.missIdentifiedPatterns, ind.missIdentifiedPatterns.size());
		ind.missIdentifiedPatterns.clear();
	}

	if (params.testIndMode)
		ind.outputNetworkActivity();
	cout << "\nDone!" << endl;
}

void countFreq(vector<string> arr, int n)
{
	// Mark all array elements as not visited 
	vector<bool> visited(n, false);
	int uniquePatternCount = 0;
	int singleOccurence = 0, multipleOccurences = 0;
	// Traverse through array elements and count frequencies 
	for (int i = 0; i < n; i++) {

		// Skip this element if already processed 
		if (visited[i] == true)
			continue;

		// Count frequency 
		int count = 1;
		for (int j = i + 1; j < n; j++) {
			if (arr[i] == arr[j]) {
				visited[j] = true;
				count++;
			}
		}
		//uniquePatternCount++;
	//	if(arr[i].length() == 6)
	//	{
		cout << arr[i] << " " << count << "\t";

		if (count == 1)
			singleOccurence++;
		else if (count > 1)
		{
			multipleOccurences++;
		}

		//	}


	}
	cout << "\n False Positives: " << arr.size() << " no. of Patterns: " << multipleOccurences + singleOccurence << "  Patterns recognized more than once: " << multipleOccurences << " Patterns recognised once: " << singleOccurence << endl;

}

vector<PatternFrequencyPair> countFreqWriteToFile(vector<string> arr, int n)
{
	vector<PatternFrequencyPair> patFreqList;
	PatternFrequencyPair patFreq;
	ofstream ofs;
	ofs.open("indMatrix.dat", ofstream::out | ofstream::app);
	ofs << "Problematic patterns" << endl;
	// Mark all array elements as not visited 
	vector<bool> visited(n, false);
	int uniquePatternCount = 0;
	int singleOccurence = 0;
	// Traverse through array elements and 
	// count frequencies 
	for (int i = 0; i < n; i++) {

		// Skip this element if already processed 
		if (visited[i] == true)
			continue;

		// Count frequency 
		int count = 1;
		for (int j = i + 1; j < n; j++) {
			if (arr[i] == arr[j]) {
				visited[j] = true;
				count++;
			}
		}

		patFreq.pattern = arr[i];
		patFreq.freq = count;
		patFreqList.push_back(patFreq);
		patFreq.clear();
		//uniquePatternCount++;
		//ofs << arr[i] << " " << count << "\t";
		if (count == 1)
			singleOccurence++;

	}

	sort(patFreqList.begin(), patFreqList.end(), [](const PatternFrequencyPair& lhs, const PatternFrequencyPair& rhs)
		{
			return lhs.freq > rhs.freq;
		});
	for (int pf = 0; pf < patFreqList.size(); pf++)
	{
		ofs << patFreqList[pf].pattern << " " << patFreqList[pf].freq << "\t";
	}

	ofs << "\n False pattern count: " << arr.size() << "  Unique patterns: " << arr.size() - singleOccurence << " Single Occurence: " << singleOccurence << endl;
	ofs << "---------X---------X---------X---------X---------X---------X" << endl << endl;
	ofs.close();
	return patFreqList;
}


void evaluate()
{

}
