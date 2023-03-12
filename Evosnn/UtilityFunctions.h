#pragma once
#include <random>
#include <fstream>
#include <streambuf>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Parameters.h"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
using namespace std;
extern Parameters params;
class UtilityFunctions
{

	
public:
	UtilityFunctions(void);
	~UtilityFunctions(void);
};


double getRandomValue(double LO, double HI);
vector<char> randomInputSequence(string signals, int sequenceLength);
vector<int> getGroundtruth(vector<char> &seq, string corSeq);
vector<char> getRandomSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getRandomSequenceABCD(string correctTriplet, int size, int gap, int letterSize);
vector<char> getRandomSequenceABCDEF(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDESequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDEFSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getTestingABCDEFSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getAllPossibleCombinationSequence(int gap, int letterSize);
void allPossibleCombinations(string &seq, const string& v, std::vector<int>& pos, int n);
void getPermutations(string &allPerm, const string str, std::string prefix, const int n, const int lenght);
vector<char> getPermutedSequence(string fileName, string str, int k, int gap, int lettersize);
vector<char> get_abcdXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcXXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcXXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize);

vector<char> getABXXX_XXXDE_Sequence(string correctTriplet, int size, int gap, int letterSize);

vector<char> getUserDefinedSequence(string inputStr, int gap, int letterSize);
vector<char> insertGapsAndSetLetterSize(string* randStr, int gap, int letterSize);
int getUniformVariation(int num);
vector<int> getCorrectPatternsMarkers(vector<char>& patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCD(vector<char>& patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDE(vector<char>& patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEF(vector<char>& patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkers6Letter(vector<char>& patSequence, string corrTrip);
vector<double> getGaussianValueWithGivenMeanAndSD(double mean, double sd, long long int seqSize);
string getPaternBeforeSpikeIndex(vector<char>& signalSiquence, long index, int patlength);
double getGaussianRandomNumber(default_random_engine de, double mean, double stddev);
