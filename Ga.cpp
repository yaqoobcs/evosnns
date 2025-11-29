// #include "stdafx.h"
#include "Ga.h"
#include <algorithm>
#include <cstring>
#include <ctime>
#include <string>
#include "UtilityFunctions.h"

using namespace std;
Ga::Ga(void) {
    history.clear();
    keepGen0Elites.clear();
    signalSiquence.clear();
    correctIndecies.clear();
}

void Ga::run(vector<Individual> &pop, int genNo, vector<char> &hardPatternSeq) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
    string signal = alphabet.substr(0, params.noOfSignals);
    int noOfSeq = 6;
    int step = 0;


    // srand(100);
    // srand(time(0)); // takes inter in convergence, results in perfect ind.
    vector<char> signalSiquence;
    vector<int> correctIndecies;
    // signalSiquence = getRandomSequenceABCDEF(signal, params.noOfLetters,
    // params.silenctinterval, params.letterSize); signalSiquence =
    // getABCDEFSequence(signal, params.noOfLetters, params.silenctinterval,
    // params.letterSize); signalSiquence = getHardABCDEF_Sequence(signal,
    // params.noOfLetters, params.silenctinterval, params.letterSize);
    if (params.noOfSignals == 10) {
        signalSiquence = get_abcdefgXXX_XXXdefghij_Sequence(signal, params.noOfLetters, params.silenctinterval,
                                                            params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDEFGHIJ(signalSiquence, signal);
    }
    if (params.noOfSignals == 9) {
        signalSiquence =
                get_abcdefXXX_XXXdefghi_Sequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDEFGHI(signalSiquence, signal);
    } else if (params.noOfSignals == 8) {
        signalSiquence =
                get_abcdeXXX_XXXfgh_Sequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDEFGH(signalSiquence, signal);
    } else if (params.noOfSignals == 7) {
        signalSiquence =
                get_abcdXXX_XXXdefg_Sequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, signal);
    } else if (params.noOfSignals == 6) {
        // signalSiquence = getHardABCDEF_Sequence(signal, params.noOfLetters,
        // params.silenctinterval, params.letterSize);
        signalSiquence =
                get_abcXXX_XXXdef_Sequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);
    } else if (params.noOfSignals == 5) // 5signals
    {
        signalSiquence = getABXXX_XXXDE_Sequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);
    } else if (params.noOfSignals == 4) // 4signals
    {
        signalSiquence = getABCDSequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);
    } else if (params.noOfSignals == 3) // 3signals
    {
        signalSiquence = getABCSequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        if (!hardPatternSeq.empty())
            signalSiquence.insert(signalSiquence.end(), hardPatternSeq.begin(), hardPatternSeq.end());
        correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);

        if (params.getAlmostCorrectNWs == true)
            correctIndecies = getCorrectPatternsMarkersAB(signalSiquence, "BC");
    }

    else if (params.noOfSignals == 2) // 2signals
    {
        signalSiquence = getABSequence(signal, params.noOfLetters, params.silenctinterval, params.letterSize);
        correctIndecies = getCorrectPatternsMarkersAB(signalSiquence, signal);
    }

    // cout << "Sequence Size: " << signalSiquence.size() << endl;
    for (int i = 0; i < pop.size(); i++) {
        // for (int m=0; m<pop[i].outputNeurons.size(); m++)
        //{

        // for(int noS=0; noS<noOfSeq; noS++)
        //{
        for (long j = 0; j < signalSiquence.size(); j++) {
            step += 1;
            pop[i].setInput(signalSiquence[j], j);
            pop[i].networkStep(step);
        }
        // fitness
        pop[i].fitness = fitness(pop[i], signalSiquence, correctIndecies);

        // Reset
        step = 0;

        pop[i].outputNeurons[0].spikeBitmap.clear();
        pop[i].outputNeurons[0].voltageBuffer.clear();
        for (int p = 0; p < pop[i].inputNeurons.size(); p++)
            pop[i].inputNeurons[p].voltageBuffer.clear();
        for (int q = 0; q < pop[i].interNeurons.size(); q++)
            pop[i].interNeurons[q].voltageBuffer.clear();
    }

    // sort based on fitness function
    sort(pop.begin(), pop.end(),
         [](const Individual &lhs, const Individual &rhs) { return lhs.fitness < rhs.fitness; });

    cout << "=======" << endl;
    cout << "Fitness check" << endl;
    cout << "Fitness i=0:\t" << pop[0].fitness << endl;
    cout << "Fitness i=1:\t" << pop[1].fitness << endl;
    cout << "Fitness i=2:\t" << pop[2].fitness << endl;
    cout << "..." << endl;
    cout << "Fitness i=97:\t" << pop[97].fitness << endl;
    cout << "Fitness i=98:\t" << pop[98].fitness << endl;
    cout << "Fitness i=99:\t" << pop[99].fitness << endl;


    int firstRand = 0, secondRand = 0;

    // tournament selection keep elites
    for (int k = params.eliteCount; k < pop.size(); k++) {

        firstRand = getRandomValue(0, pop.size() - 1);
        secondRand = getRandomValue(0, pop.size() - 1);

        if (pop[firstRand].fitness < pop[secondRand].fitness) {
            pop[k] = pop[firstRand];
        } else {
            pop[k] = pop[secondRand];
        }
    }

    // replicate
    for (int rep = params.eliteCount; rep < pop.size(); rep++) {
        //	pop[rep].printIndividualMatrix(rep);
        // string outputdir = params.outputdir + "/replication_debugging/";
        // pop[rep].printIndividualMatrix(rep, 1, outputdir, "connectivity_matrix_" + to_string(rep) + "before.txt");
        pop[rep].replicate();
        // pop[rep].printIndividualMatrix(rep, 1, outputdir, "connectivity_matrix_" + to_string(rep) + "after.txt");
        // pop[rep].replicateInput_and_Switch_connections();
        // pop[rep].replicateInputconnection_WithGaussianNoise(); //fine tuning
        // pop[rep].replicateWithGaussianNoise();
        // pop[rep].replicateinterConnections();
        // pop[rep].replicateExceptLoops();
        //	pop[rep].printIndividualMatrix(rep);
    }
    // if(genNo%params.randomizeEveryXGen==1)
    //{
    //	for(int rCount=pop.size()-params.randomizeCount; rCount<pop.size(); rCount++)
    //	{
    //		pop[rCount].randomizeinterconnections();
    //	}
    // }

    signalSiquence.clear();
    correctIndecies.clear();
}

bool Ga::runMinimalWeight(vector<Individual> &pop, int genNo) {
    string signal("ABC");
    int letterSize = params.letterSize;
    int gapSize = params.silenctinterval;
    int sequenceLength = params.noOfLetters;
    int noOfSeq = 6;
    int step = 0;
    double reward = 0.0, penalty = 0.0, rewardAll = 0.0, penaltyAll = 0.0;

    // srand(100);
    vector<char> signalSiquence = getRandomSequence(signal, sequenceLength, gapSize, letterSize);
    vector<int> correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);


    for (int i = 0; i < pop.size(); i++) {
        // for (int m=0; m<pop[i].outputNeurons.size(); m++)
        //{
        reward = 0.0, penalty = 0.0;
        rewardAll = 0.0, penaltyAll = 0.0;
        // for(int noS=0; noS<noOfSeq; noS++)
        //{

        for (int j = 0; j < signalSiquence.size(); j++) {
            step += 1;
            pop[i].setInput(signalSiquence[j], j);
            pop[i].networkStep(step);
        }

        double rCountint = 0.0, rCountSig = 0.0, pCountint = 0.0, pCountSig = 0.0;

        // fitness 2 from Greans
        int k = 0;
        int sizeHistory = pop[i].outputNeurons[0].spikeBitmap.size();
        for (int j = 0; j < correctIndecies.size(); j++) {
            while (k < sizeHistory && k != correctIndecies[j]) {
                while (signalSiquence[k] != 'Z' && k != correctIndecies[j]) {
                    if (pop[i].outputNeurons[0].spikeBitmap[k]) {
                        pCountSig += 1.0;
                        k++;
                    } else {
                        k++;
                    }
                }
                while (signalSiquence[k] == 'Z' && k != correctIndecies[j]) {
                    if (pop[i].outputNeurons[0].spikeBitmap[k]) {
                        pCountint += 1.0;
                        k++;
                    } else {
                        k++;
                    }
                }
                if (pCountint + pCountSig > 0.0) {
                    pCountint = 0.0;
                    pCountSig = 0.0;
                    penalty += 1.0;
                }
            }
            while (k < sizeHistory && signalSiquence[k] != 'Z') {
                if (pop[i].outputNeurons[0].spikeBitmap[k]) {
                    rCountSig += 1.0;
                    k++;
                } else {
                    k++;
                }
            }
            while (k < sizeHistory && signalSiquence[k] == 'Z') {
                if (pop[i].outputNeurons[0].spikeBitmap[k]) {
                    rCountint += 1.0;
                    k++;
                } else {
                    k++;
                }
            }
            if (rCountSig + rCountint > 0.0) {
                rCountSig = 0.0;
                rCountint = 0.0;
                reward += 1.0;
            }
        }
        // normalize reward/fitness
        pop[i].rewardn = reward / (double) correctIndecies.size();
        pop[i].penaltyn = penalty / (sequenceLength - correctIndecies.size());

        pop[i].reward = reward;
        pop[i].penalty = penalty;

        pop[i].fitness = 1 - (pop[i].rewardn - 4 * pop[i].penaltyn);

        // Reset
        step = 0;
        pop[i].outputNeurons[0].spikeBitmap.clear();
        pop[i].outputNeurons[0].voltageBuffer.clear();
        for (int p = 0; p < pop[i].inputNeurons.size(); p++)
            pop[i].inputNeurons[p].voltageBuffer.clear();
        for (int q = 0; q < pop[i].interNeurons.size(); q++)
            pop[i].interNeurons[q].voltageBuffer.clear();
    }

    // sort based of fitness function
    sort(pop.begin(), pop.end(),
         [](const Individual &lhs, const Individual &rhs) { return lhs.fitness < rhs.fitness; });

    // keep only perfect
    int wi = 0;
    while (pop[wi].fitness < 0.005) {

        pop[wi].sumOfConnectionWeights();
        wi++;
    }
    pop.resize(wi);


    if (wi != 0) {

        for (int k = wi; k < params.popSize; k++) {
            pop.push_back(pop[getRandomValue(0, wi)]);
        }

        // sort based on weight Sum
        sort(pop.begin(), pop.end(),
             [](const Individual &lhs, const Individual &rhs) { return lhs.absWeightSum < rhs.absWeightSum; });


        // keep gen0 elites in all gen.
        if (genNo == 0) {

            for (int ke = 0; ke < params.eliteCount; ke++) {
                keepGen0Elites.push_back(pop[ke]);
            }
        } else {
            for (int ei = 0; ei < keepGen0Elites.size(); ei++) {
                pop.insert(pop.begin(), keepGen0Elites[ei]);
            }
        }

        // sort based on weight Sum
        sort(pop.begin(), pop.end(),
             [](const Individual &lhs, const Individual &rhs) { return lhs.absWeightSum < rhs.absWeightSum; });
        pop.resize(params.popSize);

        // tournament selection (weight) keep elites
        int firstRand = 0, secondRand = 0;
        for (int k = params.eliteCount; k < pop.size(); k++) {

            firstRand = getRandomValue(0, pop.size() - 1);
            secondRand = getRandomValue(0, pop.size() - 1);

            if (pop[firstRand].absWeightSum < pop[secondRand].absWeightSum) {
                pop[k] = pop[firstRand];
            } else {
                pop[k] = pop[secondRand];
            }
        }

        // replicate
        for (int rep = params.eliteCount; rep < pop.size(); rep++) {
            pop[rep].replicateByOnlyReducingWeights();
            //	pop[rep].printIndividualMatrix(rep);
            // pop[rep].replicate();
            // pop[rep].replicateinterConnections();
            // pop[rep].replicateExceptLoops();
            //	pop[rep].printIndividualMatrix(rep);
        }
    } else {
        cout << "wi == 0" << endl;
        return false;
    }
    // if(genNo%params.randomizeEveryXGen==1)
    //{
    //	for(int rCount=pop.size()-params.randomizeCount; rCount<pop.size(); rCount++)
    //	{
    //		pop[rCount].randomizeinterconnections();
    //	}
    // }

    // signalSiquence.clear();
    // correctIndecies.clear();
    return true;
}

string Ga::reEvaluateUserDefinedSequence(Individual &ind) {
    // string signal("ABCDEF");
    // string signal("ABCDE"); //5signals
    // string signalSequenceUserDefined("ABEABEDABCDEFDDD");
    // string signalSequenceUserDefined("ABCDEFACBCDEFAEBCDEF");
    string signalSequenceUserDefined;
    cout << "enter a user defined string for ploting: ";
    cin >> signalSequenceUserDefined;

    signalSiquence = getUserDefinedSequence(signalSequenceUserDefined, params.silenctinterval, params.letterSize);

    if (params.noOfSignals == 10)
        correctIndecies = getCorrectPatternsMarkersABCDEFGHIJ(signalSiquence, "ABCDEFGHIJ");
    else if (params.noOfSignals == 9)
        correctIndecies = getCorrectPatternsMarkersABCDEFGHI(signalSiquence, "ABCDEFGHI");
    else if (params.noOfSignals == 8)
        correctIndecies = getCorrectPatternsMarkersABCDEFGH(signalSiquence, "ABCDEFGH");
    else if (params.noOfSignals == 7)
        correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, "ABCDEFG");
    else if (params.noOfSignals == 6)
        correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, "ABCDEF");
    else if (params.noOfSignals == 5)
        correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, "ABCDE");
    else if (params.noOfSignals == 4)
        correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, "ABCD");
    else if (params.noOfSignals == 3)
        correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, "ABC");
    else if (params.noOfSignals == 2)
        correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, "AB");
    // correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);

    int step = 0;
    for (int j = 0; j < signalSiquence.size(); j++) {
        ind.setInput(signalSiquence[j], j);
        ind.networkStep(step);
        // check if this resting is required for plotting i dont think so
        /*
        if (step % 180 != 0) //180, 210, 240
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
        */
        step += 1;
    }
    ind.fitness = fitness(ind, signalSiquence, correctIndecies);

    signalSiquence.clear();
    correctIndecies.clear();
    ind.outputNeurons[0].spikeBitmap.clear();
    return signalSequenceUserDefined;
}

void Ga::reEvaluateTop10_onALargeSequence(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCDEF");
    int sequenceLength = 1000000;
    int noOfSeq = 6;

    signalSiquence =
            getRandomSequenceGivenCorrSignal(signal, sequenceLength, params.silenctinterval, params.letterSize);
    correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);

    int step = 0;
    for (int s = 0; s < signalSiquence.size(); s++) {
        ind.setInput(signalSiquence[s], s);
        ind.networkStep(step);
        step += 1;
    }

    ind.fitness = fitness(ind, signalSiquence, correctIndecies);
    cout << "\tFitness:\t" << ind.fitness << "\tTPR:\t" << ind.rewardn << "\tFDR:\t" << ind.fdr << endl;
    ind.outputNeurons[0].spikeBitmap.clear();
}

void Ga::reEvaluateOnLargeSequence(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal;
    if (params.noOfSignals == 10)
        signal = "ABCDEFGHIJ";
    else if (params.noOfSignals == 9)
        signal = "ABCDEFGHI";
    else if (params.noOfSignals == 8)
        signal = "ABCDEFGH";
    else if (params.noOfSignals == 7)
        signal = "ABCDEFG";
    else if (params.noOfSignals == 6)
        signal = "ABCDEF";
    else if (params.noOfSignals == 5)
        signal = "ABCDE";
    else if (params.noOfSignals == 4)
        signal = "ABCD";
    else if (params.noOfSignals == 3)
        signal = "ABC";
    else if (params.noOfSignals == 2)
        signal = "AB";

    int sequenceLength = params.reevaluateSeq;
    signalSiquence = getRandomSequenceGivenCorrSignalUpgraded(signal, sequenceLength, params.silenctinterval,
                                                              params.letterSize, signal);
    if (params.noOfSignals == 10) {
        correctIndecies = getCorrectPatternsMarkersABCDEFGHIJ(signalSiquence, signal);
    } else if (params.noOfSignals == 9) {
        correctIndecies = getCorrectPatternsMarkersABCDEFGHI(signalSiquence, signal);
    } else if (params.noOfSignals == 8) {
        correctIndecies = getCorrectPatternsMarkersABCDEFGH(signalSiquence, signal);
    } else if (params.noOfSignals == 7) {
        correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, signal);
    } else if (params.noOfSignals == 6) {
        correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);
    } else if (params.noOfSignals == 5) {
        correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);
    } else if (params.noOfSignals == 4) {
        correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);
    } else if (params.noOfSignals == 3) {
        signalSiquence =
                getRandomSequenceGivenCorrSignal(signal, sequenceLength, params.silenctinterval, params.letterSize);
        correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);
    }

    int step = 0;
    for (int s = 0; s < signalSiquence.size(); s++) {
        ind.setInput(signalSiquence[s], s);
        ind.networkStep(step);
        step += 1;
    }

    ind.fitness = fitness(ind, signalSiquence, correctIndecies);
    cout << "\tFitness:\t" << ind.fitness << "\tTPR:\t" << ind.rewardn << "\tFDR:\t" << ind.fdr << endl;
    ind.outputNeurons[0].spikeBitmap.clear();
}

void Ga::reEvaluateTop10ind(vector<Individual> &top10ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCDEF");
    // string signalSequenceUserDefined("ABABEDABCDEFDEFEEF");
    // int letterSize = 6;
    // int gapSize = 16;
    int sequenceLength = 500000;
    int noOfSeq = 6;
    // long long int step=0;
    // double reward=0.0, penalty=0.0, rewardAll=0.0, penaltyAll=0.0;
    // srand(100);
    // signalSiquence = getRandomSequenceABCDEF(signal, sequenceLength,
    // params.silenctinterval, params.letterSize);
    //	if(signalSiquence.size()==0)

    PatternFrequencyPair tempPair;

    string pattern = "";

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 6; l++)
                    for (int m = 0; m < 6; m++)
                        for (int n = 0; n < 6; n++)
                            for (int o = 0; o < 6; o++)
                            // for (int p = 0; p < 6; p++)
                            // for (int q = 0; q < 6; q++) //9

                            {
                                pattern.push_back('F');
                                pattern.push_back(signal[i]);
                                pattern.push_back(signal[j]);
                                pattern.push_back(signal[k]);
                                pattern.push_back(signal[l]);
                                pattern.push_back(signal[m]);
                                pattern.push_back(signal[n]);
                                pattern.push_back(signal[o]);
                                // pattern.push_back(signal[p]);
                                // pattern.push_back(signal[q]); //9
                                // cout << pattern << endl;
                                tempPair.clear();
                                // pattern.clear();
                                // pattern = "FFFABCDEF";

                                signalSiquence =
                                        insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                                correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);


                                int patternReconizedCount = 0;
                                // vector<string> patternVec;
                                // vector<int> patternCount;
                                for (int nw = 0; nw < top10ind.size(); nw++) {
                                    int step = 0;
                                    for (int s = 0; s < signalSiquence.size(); s++) {
                                        top10ind[nw].setInput(signalSiquence[s], s);
                                        top10ind[nw].networkStep(step);
                                        step += 1;
                                    }
                                    //	ind.gaussNoiseVector.clear();
                                    // d
                                    //	ind.gaussNoiseVector.resize(0);

                                    int bitmapSize = top10ind[nw].outputNeurons[0].spikeBitmap.size();

                                    for (int sbp = bitmapSize - 30; sbp < bitmapSize; sbp++) {
                                        if (top10ind[nw].outputNeurons[0].spikeBitmap[sbp] == true) {
                                            patternReconizedCount++;
                                            // cout << pattern << endl;
                                            // Sleep(1000);
                                            break;
                                        }
                                    }

                                    // ind.fitness = fitness(ind, signalSiquence,
                                    // correctIndecies);
                                    top10ind[nw].outputNeurons[0].spikeBitmap.clear();
                                }

                                if (patternReconizedCount > 0) {
                                    tempPair.pattern = pattern;
                                    tempPair.freq = patternReconizedCount;
                                    pattFrqStructList.push_back(tempPair);
                                    // cout << pattern << "\t" << patternReconizedCount <<
                                    // "\t";
                                }

                                signalSiquence.clear();
                                correctIndecies.clear();
                                pattern.clear();
                            }
}

void Ga::run_pattern_through_network(const string &signal, const string &pattern, Individual &ind,
                                     PatternFrequencyPair &tempPair, vector<PatternFrequencyPair> &pattFrqStructList) {
    int patternReconizedCount = 0;
    // vector<string> patternVec;
    // vector<int> patternCount;
    int max_reps = 1;
    for (int rep = 0; rep < max_reps; rep++) {
        int step = 0;
        for (int s = 0; s < signalSiquence.size(); s++) {
            ind.setInput(signalSiquence[s], s);
            ind.networkStep(step);
            step += 1;
        }
        int bitmapSize = ind.outputNeurons[0].spikeBitmap.size();

        for (int sbp = 30; sbp < bitmapSize; sbp++) {
            if (ind.outputNeurons[0].spikeBitmap[sbp] == true) {
                patternReconizedCount++;
                // cout << pattern << endl;
                // Sleep(1000);
                break;
            }
        }

        // ind.fitness = fitness(ind, signalSiquence, correctIndecies);
        ind.outputNeurons[0].spikeBitmap.clear();
    }
    if (patternReconizedCount > 0) {
        tempPair.pattern = pattern;
        tempPair.freq = patternReconizedCount;
        pattFrqStructList.push_back(tempPair);
        // cout << pattern << "\t" << patternReconizedCount << "\t";
        if (strstr(pattern.c_str(), signal.c_str())) {
            ind.reward += patternReconizedCount;

        } else
            ind.penalty += patternReconizedCount;
    }
}

// Pattern length 7, all perm 9
void Ga::reEvaluateAllPerm9_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEFG");
    const size_t signal_len = signal.length();
    // string signalSequenceUserDefined("ABABEDABCDEFDEFEEF");
    // int letterSize = 6;
    // int gapSize = 16;
    int sequenceLength = 500000;
    int noOfSeq = 6;
    // long long int step=0;
    // double reward=0.0, penalty=0.0, rewardAll=0.0, penaltyAll=0.0;
    // srand(100);
    // signalSiquence = getRandomSequenceABCDEF(signal, sequenceLength,
    // params.silenctinterval, params.letterSize);
    //	if(signalSiquence.size()==0)

    PatternFrequencyPair tempPair;

    string pattern = "";

    for (int i = 0; i < signal_len; i++) {
        cout << "\t\tFirst loop at i: " << i << endl;
        for (int j = 0; j < signal_len; j++) {
            cout << "\t\t\tSecond  loop at j: " << j << endl;
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++)
                                for (int p = 0; p < signal_len; p++)
                                    for (int q = 0; q < signal_len; q++) // 9
                                    {
                                        pattern.push_back('G');
                                        pattern.push_back(signal[i]);
                                        pattern.push_back(signal[j]);
                                        pattern.push_back(signal[k]);
                                        pattern.push_back(signal[l]);
                                        pattern.push_back(signal[m]);
                                        pattern.push_back(signal[n]);
                                        pattern.push_back(signal[o]);
                                        pattern.push_back(signal[p]);
                                        pattern.push_back(signal[q]); // 9
                                        // cout << pattern << endl;
                                        tempPair.clear();
                                        // pattern.clear();
                                        // pattern = "FFFABCDEF";
                                        signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval,
                                                                                    params.letterSize);
                                        correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, signal);

                                        run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                                        signalSiquence.clear();
                                        correctIndecies.clear();
                                        pattern.clear();
                                    }
        }
    }
}

// Pattern length 7, all perm 8
void Ga::reEvaluateAllPerm8_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEFG");
    const size_t signal_len = signal.length();
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < signal_len; i++) {
        cout << "\t\tFirst loop at i: " << i << endl;
        for (int j = 0; j < signal_len; j++) {
            cout << "\t\t\tSecond  loop at j: " << j << endl;
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++)
                                for (int p = 0; p < signal_len; p++) {
                                    pattern.push_back('G');
                                    pattern.push_back(signal[i]);
                                    pattern.push_back(signal[j]);
                                    pattern.push_back(signal[k]);
                                    pattern.push_back(signal[l]);
                                    pattern.push_back(signal[m]);
                                    pattern.push_back(signal[n]);
                                    pattern.push_back(signal[o]);
                                    pattern.push_back(signal[p]);
                                    // cout << pattern << endl;
                                    tempPair.clear();
                                    // pattern.clear();
                                    // pattern = "FFFABCDEF";
                                    signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval,
                                                                                params.letterSize);
                                    correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, signal);

                                    run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);
                                    signalSiquence.clear();
                                    correctIndecies.clear();
                                    pattern.clear();
                                }
        }
    }
}

// Pattern length 7, all perm 7
void Ga::reEvaluateAllPerm7_7sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEFG");
    const size_t signal_len = signal.length();
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < signal_len; i++)
        for (int j = 0; j < signal_len; j++)
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++) {
                                pattern.push_back('G');
                                pattern.push_back(signal[i]);
                                pattern.push_back(signal[j]);
                                pattern.push_back(signal[k]);
                                pattern.push_back(signal[l]);
                                pattern.push_back(signal[m]);
                                pattern.push_back(signal[n]);
                                pattern.push_back(signal[o]);
                                // pattern = "GDAGFCAA";

                                tempPair.clear();
                                signalSiquence =
                                        insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                                correctIndecies = getCorrectPatternsMarkersABCDEFG(signalSiquence, signal);
                                run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                                signalSiquence.clear();
                                correctIndecies.clear();
                                pattern.clear();
                            }
}

// Pattern length 6, all perm 8
void Ga::reEvaluateAllPerm8_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEF");
    const size_t signal_len = signal.length();
    // int sequenceLength = 500000;
    // int noOfSeq = 6;

    PatternFrequencyPair tempPair;

    string pattern = "";

    for (int i = 0; i < signal_len; i++)
        for (int j = 0; j < signal_len; j++)
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++)
                                for (int p = 0; p < signal_len; p++)
                                // for (int q = 0; q < signal_len; q++) //9

                                {
                                    pattern.push_back('F');
                                    pattern.push_back(signal[i]);
                                    pattern.push_back(signal[j]);
                                    pattern.push_back(signal[k]);
                                    pattern.push_back(signal[l]);
                                    pattern.push_back(signal[m]);
                                    pattern.push_back(signal[n]);
                                    pattern.push_back(signal[o]);
                                    pattern.push_back(signal[p]);
                                    // pattern.push_back(signal[q]); //9
                                    // cout << pattern << endl;
                                    tempPair.clear();
                                    // pattern.clear();
                                    // pattern = "FFFABCDEF";
                                    signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval,
                                                                                params.letterSize);
                                    correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);
                                    run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                                    signalSiquence.clear();
                                    correctIndecies.clear();
                                    pattern.clear();
                                }


    // clear
    /*	ind.outputNeurons[0].spikeBitmap.clear();
        ind.outputNeurons[0].spikeBitmap.resize(0);
        ind.outputNeurons[0].voltage = -70;
        ind.outputNeurons[0].adaptation = 0;
        ind.outputNeurons[0].exConductance = 0;
        ind.outputNeurons[0].inConductance = 0;

        for (int p = 0; p < ind.inputNeurons.size(); p++)
        {
            ind.inputNeurons[p].voltageBuffer.clear();
            ind.inputNeurons[p].voltage = -70;
            ind.inputNeurons[p].adaptation = 0;
            ind.inputNeurons[p].exConductance = 0;
            ind.inputNeurons[p].inConductance = 0;
        }
        for (int q = 0; q < ind.interNeurons.size(); q++)
        {
            ind.interNeurons[q].voltageBuffer.clear();
            ind.interNeurons[q].voltage = -70;
            ind.interNeurons[q].adaptation = 0;
            ind.interNeurons[q].exConductance = 0;
            ind.interNeurons[q].inConductance = 0;
        }
        cout << eachPattCountInTen.size() << endl;
    }
    for (int ep = 0; ep < eachPattCountInTen.size(); ep++)
    {
        if(eachPattCountInTen[ep]>0)
            cout << eachPattCountInTen[ep] << "\t";

    }
    */

    /*
    double rCountint=0.0, rCountSig=0.0, pCountint=0.0, pCountSig=0.0;

    //fitness function from Greans
    int k=0;
    int sizeHistory =ind.outputNeurons[0].spikeBitmap.size();
    for(int j = 0; j < correctIndecies.size(); j++)
    {
        while( k<sizeHistory && k != correctIndecies[j] )
        {
            while(signalSiquence[k]!='Z' && k != correctIndecies[j])
            {
                if(ind.outputNeurons[0].spikeBitmap[k])
                {
                    pCountSig+=1.0; k++;
                }
                else
                {
                    k++;
                }
            }
            while(signalSiquence[k]=='Z'&& k != correctIndecies[j])
            {
                if(ind.outputNeurons[0].spikeBitmap[k])
                {
                    pCountint+=1.0; k++;
                }
                else
                {
                    k++;
                }
            }
            if(pCountint+pCountSig>0.0)
            {pCountint=0.0; pCountSig=0.0; penalty+=1.0;}
        }
        while(k<sizeHistory && signalSiquence[k]!='Z')
        {
            if(ind.outputNeurons[0].spikeBitmap[k])
            {
                rCountSig+=1.0; k++;
            }
            else
            {
                k++;
            }
        }
        while(k<sizeHistory && signalSiquence[k]=='Z')
        {
            if(ind.outputNeurons[0].spikeBitmap[k])
            {
                rCountint+=1.0; k++;
            }
            else
            {
                k++;
            }
        }
        if(rCountSig+rCountint>0.0)
        {rCountSig=0.0; rCountint=0.0;reward+=1.0;}
    }
    //normalize reward/fitness
    ind.rewardn = reward/(double)correctIndecies.size();
    ind.penaltyn = penalty/(sequenceLength-correctIndecies.size());

    ind.reward=reward;
    ind.penalty=penalty;

    ind.fitness = 1-(ind.rewardn - 4*ind.penaltyn);
    ind.outputNeurons[0].spikeBitmap.clear();
    */
}

// Pattern length 6, all perm 7
void Ga::reEvaluateAllPerm7_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEF");
    const size_t signal_len = signal.length();
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < signal_len; i++)
        for (int j = 0; j < signal_len; j++)
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++) {
                                pattern.push_back('F');
                                pattern.push_back(signal[i]);
                                pattern.push_back(signal[j]);
                                pattern.push_back(signal[k]);
                                pattern.push_back(signal[l]);
                                pattern.push_back(signal[m]);
                                pattern.push_back(signal[n]);
                                pattern.push_back(signal[o]);
                                // cout << pattern << endl;
                                tempPair.clear();
                                // pattern.clear();
                                // pattern = "FFFABCDEF";
                                signalSiquence =
                                        insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                                correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);
                                run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                                signalSiquence.clear();
                                correctIndecies.clear();
                                pattern.clear();
                            }
}

// Pattern length 6, all perm 6
void Ga::reEvaluateAllPerm6_6sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDEF");
    const size_t signal_len = signal.length();
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < signal_len; i++)
        for (int j = 0; j < signal_len; j++)
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++) {
                            pattern.push_back('F');
                            pattern.push_back(signal[i]);
                            pattern.push_back(signal[j]);
                            pattern.push_back(signal[k]);
                            pattern.push_back(signal[l]);
                            pattern.push_back(signal[m]);
                            pattern.push_back(signal[n]);

                            // cout << pattern << endl;
                            tempPair.clear();
                            // pattern.clear();
                            // pattern = "FFFABCDEF";
                            signalSiquence =
                                    insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                            correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);
                            run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                            signalSiquence.clear();
                            correctIndecies.clear();
                            pattern.clear();
                        }
}

// Pattern length 5, all perm 7
void Ga::reEvaluateAllPerm7_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    const string signal("ABCDE");
    const size_t signal_len = signal.length();
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < signal_len; i++)
        for (int j = 0; j < signal_len; j++)
            for (int k = 0; k < signal_len; k++)
                for (int l = 0; l < signal_len; l++)
                    for (int m = 0; m < signal_len; m++)
                        for (int n = 0; n < signal_len; n++)
                            for (int o = 0; o < signal_len; o++) {
                                pattern.push_back('E');
                                pattern.push_back(signal[i]);
                                pattern.push_back(signal[j]);
                                pattern.push_back(signal[k]);
                                pattern.push_back(signal[l]);
                                pattern.push_back(signal[m]);
                                pattern.push_back(signal[n]);
                                pattern.push_back(signal[o]);
                                // cout << pattern << endl;
                                tempPair.clear();
                                // pattern.clear();
                                // pattern = "FFFABCDEF";
                                signalSiquence =
                                        insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                                correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);


                                run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                                signalSiquence.clear();
                                correctIndecies.clear();
                                pattern.clear();
                            }
}

// Pattern length 5, all perm 6
void Ga::reEvaluateAllPerm6_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCDE");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                for (int l = 0; l < 5; l++)
                    for (int m = 0; m < 5; m++)
                        for (int n = 0; n < 5; n++) {
                            pattern.push_back('E');
                            pattern.push_back(signal[i]);
                            pattern.push_back(signal[j]);
                            pattern.push_back(signal[k]);
                            pattern.push_back(signal[l]);
                            pattern.push_back(signal[m]);
                            pattern.push_back(signal[n]);

                            // cout << pattern << endl;
                            tempPair.clear();
                            // pattern.clear();
                            // pattern = "FFFABCDEF";
                            signalSiquence =
                                    insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                            correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);


                            run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                            signalSiquence.clear();
                            correctIndecies.clear();
                            pattern.clear();
                        }
}

// Pattern length 5, all perm 5
void Ga::reEvaluateAllPerm5_5sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCDE");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                for (int l = 0; l < 5; l++)
                    for (int m = 0; m < 5; m++) {
                        pattern.push_back('E');
                        pattern.push_back(signal[i]);
                        pattern.push_back(signal[j]);
                        pattern.push_back(signal[k]);
                        pattern.push_back(signal[l]);
                        pattern.push_back(signal[m]);

                        // cout << pattern << endl;
                        tempPair.clear();
                        // pattern.clear();
                        // pattern = "FFFABCDEF";
                        signalSiquence =
                                insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                        correctIndecies = getCorrectPatternsMarkersABCDE(signalSiquence, signal);


                        run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                        signalSiquence.clear();
                        correctIndecies.clear();
                        pattern.clear();
                    }
}

// Pattern length 4, all perm 6
void Ga::reEvaluateAllPerm6_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCD");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int l = 0; l < 4; l++)
                    for (int m = 0; m < 4; m++)
                        for (int n = 0; n < 4; n++) {
                            pattern.push_back('D');
                            pattern.push_back(signal[i]);
                            pattern.push_back(signal[j]);
                            pattern.push_back(signal[k]);
                            pattern.push_back(signal[l]);
                            pattern.push_back(signal[m]);
                            pattern.push_back(signal[n]);

                            // cout << pattern << endl;
                            tempPair.clear();
                            // pattern.clear();
                            // pattern = "FFFABCDEF";
                            signalSiquence =
                                    insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                            correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);


                            run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                            signalSiquence.clear();
                            correctIndecies.clear();
                            pattern.clear();
                        }
}

// Pattern length 4, all perm 5
void Ga::reEvaluateAllPerm5_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCD");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int l = 0; l < 4; l++)
                    for (int m = 0; m < 4; m++) {
                        pattern.push_back('D');
                        pattern.push_back(signal[i]);
                        pattern.push_back(signal[j]);
                        pattern.push_back(signal[k]);
                        pattern.push_back(signal[l]);
                        pattern.push_back(signal[m]);

                        // cout << pattern << endl;
                        tempPair.clear();
                        // pattern.clear();
                        // pattern = "FFFABCDEF";
                        signalSiquence =
                                insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                        correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);


                        run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                        signalSiquence.clear();
                        correctIndecies.clear();
                        pattern.clear();
                    }
}

// Pattern length 4, all perm 4
void Ga::reEvaluateAllPerm4_4sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABCD");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int l = 0; l < 4; l++) {
                    pattern.push_back('D');
                    pattern.push_back(signal[i]);
                    pattern.push_back(signal[j]);
                    pattern.push_back(signal[k]);
                    pattern.push_back(signal[l]);

                    // cout << pattern << endl;
                    tempPair.clear();
                    // pattern.clear();
                    // pattern = "FFFABCDEF";
                    signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                    correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);


                    run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                    signalSiquence.clear();
                    correctIndecies.clear();
                    pattern.clear();
                }
}


// Pattern length 3, all perm 5
void Ga::reEvaluateAllPerm5_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABC");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    for (int m = 0; m < 3; m++) {
                        pattern.push_back('C');
                        pattern.push_back(signal[i]);
                        pattern.push_back(signal[j]);
                        pattern.push_back(signal[k]);
                        pattern.push_back(signal[l]);
                        pattern.push_back(signal[m]);

                        // cout << pattern << endl;
                        tempPair.clear();
                        // pattern.clear();
                        // pattern = "FFFABCDEF";
                        signalSiquence =
                                insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                        correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);

                        run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                        signalSiquence.clear();
                        correctIndecies.clear();
                        pattern.clear();
                    }
}

// Pattern length 3, all perm 4
void Ga::reEvaluateAllPerm4_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABC");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++) {
                    pattern.push_back('C');
                    pattern.push_back(signal[i]);
                    pattern.push_back(signal[j]);
                    pattern.push_back(signal[k]);
                    pattern.push_back(signal[l]);

                    // cout << pattern << endl;
                    tempPair.clear();
                    // pattern.clear();
                    // pattern = "FFFABCDEF";
                    signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                    correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);


                    run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                    signalSiquence.clear();
                    correctIndecies.clear();
                    pattern.clear();
                }
}

// Pattern length 3, all perm 3
void Ga::reEvaluateAllPerm3_3sig(Individual &ind, vector<PatternFrequencyPair> &pattFrqStructList) {
    string signal("ABC");
    PatternFrequencyPair tempPair;
    string pattern = "";

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++) {
                pattern.push_back('C');
                pattern.push_back(signal[i]);
                pattern.push_back(signal[j]);
                pattern.push_back(signal[k]);

                // cout << pattern << endl;
                tempPair.clear();
                // pattern.clear();
                // pattern = "FFFABCDEF";
                signalSiquence = insertGapsAndSetLetterSize(&pattern, params.silenctinterval, params.letterSize);
                correctIndecies = getCorrectPatternsMarkersABC(signalSiquence, signal);


                run_pattern_through_network(signal, pattern, ind, tempPair, pattFrqStructList);

                signalSiquence.clear();
                correctIndecies.clear();
                pattern.clear();
            }
}

void Ga::reEvaluateOnProblamaticPatternsFound(Individual &ind, string probSignalSequence) {
    string signal("ABCDEF");
    // string signalSequenceUserDefined("ACCDABCDBBCDDBBCCAA");
    // int letterSize = 6;
    // int gapSize = 16;
    int sequenceLength = 500000;
    int noOfSeq = 6;
    int step = 0;
    // double reward=0.0, penalty=0.0, rewardAll=0.0, penaltyAll=0.0;
    // srand(100);
    vector<char> signalSiquence = getUserDefinedSequence(probSignalSequence, params.silenctinterval, params.letterSize);
    // vector<char> signalSiquence = getRandomSequenceABCDEF(signal, sequenceLength,
    // params.silenctinterval, params.letterSize); vector<char> signalSiquence =
    // getTestingABCDEFSequence(signal, sequenceLength, params.silenctinterval,
    // params.letterSize); vector<char> signalSiquence =
    // getUserDefinedSequence(signalSequenceUserDefined, params.silenctinterval,
    // params.letterSize);
    vector<int> correctIndecies = getCorrectPatternsMarkersABCDEF(signalSiquence, signal);


    // reward=0.0, penalty=0.0;rewardAll=0.0, penaltyAll=0.0;


    for (int j = 0; j < signalSiquence.size(); j++) {
        step += 1;
        ind.setInput(signalSiquence[j], j);
        ind.networkStep(step);
    }
    //	ind.fitness = fitness(ind, signalSiquence, correctIndecies);
    /*
    double rCountint=0.0, rCountSig=0.0, pCountint=0.0, pCountSig=0.0;

    //fitness function from Greans
    int k=0;
    int sizeHistory =ind.outputNeurons[0].spikeBitmap.size();
    for(int j = 0; j < correctIndecies.size(); j++)
    {
        while( k<sizeHistory && k != correctIndecies[j] )
        {
            while(signalSiquence[k]!='Z' && k != correctIndecies[j])
            {
                if(ind.outputNeurons[0].spikeBitmap[k])
                {
                    pCountSig+=1.0; k++;
                }
                else
                {
                    k++;
                }
            }
            while(signalSiquence[k]=='Z'&& k != correctIndecies[j])
            {
                if(ind.outputNeurons[0].spikeBitmap[k])
                {
                    pCountint+=1.0; k++;
                }
                else
                {
                    k++;
                }
            }
            if(pCountint+pCountSig>0.0)
            {pCountint=0.0; pCountSig=0.0; penalty+=1.0;}
        }
        while(k<sizeHistory && signalSiquence[k]!='Z')
        {
            if(ind.outputNeurons[0].spikeBitmap[k])
            {
                rCountSig+=1.0; k++;
            }
            else
            {
                k++;
            }
        }
        while(k<sizeHistory && signalSiquence[k]=='Z')
        {
            if(ind.outputNeurons[0].spikeBitmap[k])
            {
                rCountint+=1.0; k++;
            }
            else
            {
                k++;
            }
        }
        if(rCountSig+rCountint>0.0)
        {rCountSig=0.0; rCountint=0.0;reward+=1.0;}
    }
    //normalize reward/fitness
    ind.rewardn = reward/(double)correctIndecies.size();
    ind.penaltyn = penalty/(sequenceLength-correctIndecies.size());

    ind.reward=reward;
    ind.penalty=penalty;

    ind.fitness = 1-(ind.rewardn - 4*ind.penaltyn);
    ind.outputNeurons[0].spikeBitmap.clear();
    */
}

void Ga::reEvaluateABCD(Individual &ind) {
    string signal("ABCD");
    // int letterSize = 6;
    // int gapSize = 16;
    int sequenceLength = 500000;
    int noOfSeq = 6;
    int step = 0;
    double reward = 0.0, penalty = 0.0, rewardAll = 0.0, penaltyAll = 0.0;
    // srand(100);
    vector<char> signalSiquence =
            getRandomSequenceABCD(signal, sequenceLength, params.silenctinterval, params.letterSize);
    // vector<char> signalSiquence = getUserDefinedSequence("BBABCBBCCCAACABCA",
    // params.silenctinterval, params.letterSize);
    vector<int> correctIndecies = getCorrectPatternsMarkersABCD(signalSiquence, signal);


    reward = 0.0, penalty = 0.0;
    rewardAll = 0.0, penaltyAll = 0.0;


    for (int j = 0; j < signalSiquence.size(); j++) {
        step += 1;
        ind.setInput(signalSiquence[j], j);
        ind.networkStep(step);
    }

    double rCountint = 0.0, rCountSig = 0.0, pCountint = 0.0, pCountSig = 0.0;

    // fitness function from Greans
    int k = 0;
    int sizeHistory = ind.outputNeurons[0].spikeBitmap.size();
    for (int j = 0; j < correctIndecies.size(); j++) {
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
            if (pCountint + pCountSig > 0.0) {
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
        if (rCountSig + rCountint > 0.0) {
            rCountSig = 0.0;
            rCountint = 0.0;
            reward += 1.0;
        }
    }
    // normalize reward/fitness
    ind.rewardn = reward / (double) correctIndecies.size();
    ind.penaltyn = penalty / (sequenceLength - correctIndecies.size());

    ind.reward = reward;
    ind.penalty = penalty;

    ind.fitness = 1 - (ind.rewardn - 4 * ind.penaltyn);
    ind.outputNeurons[0].spikeBitmap.clear();
}
Ga::~Ga(void) {}
