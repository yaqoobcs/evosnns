#pragma once
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <streambuf>
#include <vector>
#include "Parameters.h"

using namespace std;
extern Parameters params;
class UtilityFunctions {


public:
    UtilityFunctions(void);
    ~UtilityFunctions(void);
};

double getRandomValue(double LO, double HI);
vector<char> randomInputSequence(string signals, int sequenceLength);
vector<int> getGroundtruth(vector<char> &seq, string corSeq);


void insertSequenceIntoLetterChain(const string &sequence, string &randSequence, int insertionWindowSize);
void insertSequenceIntoLetterChain(const string &phrase, const vector<string> &phrases_with_dobuling_vec, string &randSequence, int subSequenceLen);

vector<char> getRandomSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getRandomSequenceABCD(string correctTriplet, int size, int gap, int letterSize);
vector<char> getRandomSequenceGivenCorrSignal(string correctTriplet, int size, int gap, int letterSize);
vector<char> getRandomSequenceGivenCorrSignalUpgraded(const string &chSequence, int size, int gap, int letterSize, const std::string &sequence);
vector<char> getABSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDESequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getABCDEFSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getTestingABCDEFSequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getAllPossibleCombinationSequence(int gap, int letterSize);
void allPossibleCombinations(string &seq, const string &v, std::vector<int> &pos, int n);
void getPermutations(string &allPerm, const string str, std::string prefix, const int n, const int lenght);
vector<char> getPermutedSequence(string fileName, string str, int k, int gap, int lettersize);


void generatePermutationsWithReplacement(const std::string &str, const std::string &current, int length, std::vector<std::string> &permutations,
                                         const std::string &prefix, const std::string &suffix);

vector<char> generateSequenceWithPermutation(const int size, const int gap, const int letterSize, const vector<string> &sequence_heads,
                                             const vector<string> &permutation_bases, const vector<string> &sequence_tails, const string &sequence);

vector<char> generateSequenceWithPermutation_with_doubling(const int size, const int gap, const int letterSize, const vector<string> &sequence_heads,
                                                           const vector<string> &permutation_bases, const vector<string> &sequence_tails,
                                                           const string &sequence);

vector<char> get_abcdXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcXXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdXXX_XXXdefg_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdeXXX_XXXfgh_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdefXXX_XXXdefghi_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdefgXXX_XXXdefghij_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcdXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> get_abcXXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize);
vector<char> getHardABCDEF_Sequence(string correctTriplet, int size, int gap, int letterSize);

// 5signals
vector<char> getABXXX_XXXDE_Sequence(string correctTriplet, int size, int gap, int letterSize);

vector<char> getUserDefinedSequence(string inputStr, int gap, int letterSize);
vector<char> insertGapsAndSetLetterSize(string *randStr, int gap, int letterSize);
int getUniformVariation(int num);
vector<int> getCorrectPatternsMarkersAB(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABC(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCD(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDE(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEF(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEFG(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEFGH(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEFGHI(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkersABCDEFGHIJ(vector<char> &patSequence, string corrTrip);
vector<int> getCorrectPatternsMarkers6Letter(vector<char> &patSequence, string corrTrip);
vector<double> getGaussianValueWithGivenMeanAndSD(double mean, double sd, long long int seqSize);
string getPaternBeforeSpikeIndex(vector<char> &signalSiquence, long index, int patlength);
double getGaussianRandomNumber(default_random_engine de, double mean, double stddev);

bool checkOrCreateDirectory(const std::string &path);
