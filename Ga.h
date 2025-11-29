#pragma once
#include "Individual.h"
// #include <bits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Evosnn.cpp"

struct PatternFrequencyPair {
    string pattern;
    int freq;
    void clear() {
        pattern = "";
        freq = 0;
    }
};

class Ga {
public:
    Ga(void);
    vector<vector<Individual>> history;
    vector<char> signalSiquence;
    vector<int> correctIndecies;


    vector<Individual> keepGen0Elites;
    void run(vector<Individual> &pop, int genNo, vector<char> &hardPatternSeq);
    bool runMinimalWeight(vector<Individual> &pop, int genNo);
    string reEvaluateUserDefinedSequence(Individual &ind);
    // void reEvaluate(Individual &ind, vector<PatternFrequencyPair> pattFrqStructList);
    void reEvaluateABCD(Individual &ind);

    // Heavy lifting in the funcitons that follow
    void run_pattern_through_network(const string &signal, const string &pattern, Individual &ind,
                                     PatternFrequencyPair &tempPair, vector<PatternFrequencyPair> &pattFrqStructList);
    // 7
    void reEvaluateAllPerm9_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm8_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm7_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    // 6
    void reEvaluateAllPerm8_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm7_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm6_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    // 5
    void reEvaluateAllPerm7_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm6_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm5_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    // 4
    void reEvaluateAllPerm6_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm5_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm4_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    // 3
    void reEvaluateAllPerm5_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm4_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateAllPerm3_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);

    void reEvaluateOnLargeSequence(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateTop10_onALargeSequence(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateTop10ind(vector<Individual> &top10ind, vector<PatternFrequencyPair> &pattFrqStructList);
    void reEvaluateOnProblamaticPatternsFound(Individual &ind, string signalSequence);
    string getPaternBeforeSpikeIndex(vector<char> &signalSiquence, long index, int patlength) {
        string patt = "";
        for (int ii = 0; ii < patlength; ii++) {
            index = index - 30;
            if (index < 0)
                break;
            else
                patt += signalSiquence[index];
        }
        std::reverse(patt.begin(), patt.end());
        return patt;
    }
    double long fitness(Individual &ind, vector<char> &signalSiquence, vector<int> &correctIndecies) {
        ind.rewardn = 0;
        ind.reward = 0;
        ind.penaltyn = 0;
        ind.penalty = 0;

        long patCount = -1;
        long double reward = 0.0, penalty = 0.0, rewardAll = 0.0, penaltyAll = 0.0;

        long double rCountint = 0.0, rCountSig = 0.0, pCountint = 0.0, pCountSig = 0.0;
        // ind.missIdentifiedPatterns.clear();
        // fitness 2 from Greans
        long long int k = 0;
        vector<int> inCorrPattIndex;
        long long int sizeHistory = ind.outputNeurons[0].spikeBitmap.size();
        for (long long int j = 0; j < correctIndecies.size(); j++) {
            while (k < sizeHistory && k != correctIndecies[j]) {
                while (signalSiquence[k] != 'Z' && k != correctIndecies[j]) {
                    if (ind.outputNeurons[0].spikeBitmap[k]) {
                        pCountSig += 1.0;
                        k++;
                    } else {
                        k++;
                    }
                }
                while (signalSiquence[k] == 'Z' && k != correctIndecies[j]) {
                    if (ind.outputNeurons[0].spikeBitmap[k]) {
                        pCountint += 1.0;
                        k++;
                    } else {
                        k++;
                    }
                }
                // penalty
                patCount++;
                if (pCountint + pCountSig > 0.0) {

                    // eachPattCountInTen[patCount]++;
                    // eachPattStringInTen[patCount] =
                    // getPaternBeforeSpikeIndex(signalSiquence, k, 8);
                    inCorrPattIndex.push_back(k);
                    pCountint = 0.0;
                    pCountSig = 0.0;
                    penalty += 1.0;
                }
            }
            while (k < sizeHistory && signalSiquence[k] != 'Z') {
                if (ind.outputNeurons[0].spikeBitmap[k]) {
                    rCountSig += 1.0;
                    k++;
                } else {
                    k++;
                }
            }
            while (k < sizeHistory && signalSiquence[k] == 'Z') {
                if (ind.outputNeurons[0].spikeBitmap[k]) {
                    rCountint += 1.0;
                    k++;
                } else {
                    k++;
                }
            }
            // reward
            patCount++;
            if (rCountSig + rCountint > 0.0) {

                // eachPattCountInTen[patCount]++;
                // eachPattStringInTen[patCount] =
                // getPaternBeforeSpikeIndex(signalSiquence, k, 8);

                rCountSig = 0.0;
                rCountint = 0.0;
                reward += 1.0;
            }
        }
        // inCorrect Patterns if no of signals is 4 or above
        if (params.noOfSignals >= 4) {

            long long int signalIndex;
            string incPatt = "";
            for (int icp = 0; icp < inCorrPattIndex.size(); icp++) {
                signalIndex = inCorrPattIndex[icp];
                if (signalIndex >= 180) // 150, 180, 210
                {
                    for (int ii = 0; ii < 7; ii++) // 6, 7, 8
                    {
                        signalIndex = signalIndex - 30;
                        incPatt += signalSiquence[signalIndex];
                    }
                }
                std::reverse(incPatt.begin(), incPatt.end());
                ind.missIdentifiedPatterns.push_back(incPatt);
                incPatt.clear();
            }
            inCorrPattIndex.clear();
            incPatt.clear();
        }
        // normalize reward/fitness
        ind.totalCorrPatterns = correctIndecies.size();
        ind.rewardn = reward / (long double) correctIndecies.size();
        ind.penaltyn = penalty / (params.noOfLetters - (long double) correctIndecies.size());
        ind.fdr = penalty / (penalty + reward);
        ind.precision = reward / (penalty + reward);
        ind.reward = reward;
        ind.penalty = penalty;
        //}

        // ind.fitness = 1-(ind.rewardn - 4*ind.penaltyn);

        float final_reward = 1 - (ind.rewardn - 25 * ind.penaltyn);
        return final_reward;
    }

    bool compareByFitness(const Individual &a, const Individual &b) { return a.fitness < b.fitness; }


    ~Ga(void);
};
