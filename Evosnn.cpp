// Evosnn.cpp : Defines the entry point for the console application.
// limit top sign

/*#include "stdafx.h"*/
#include <random>
// #include <time.h>
#include "Ga.h"
#include "Individual.h"

void testIndividuals_sig(const std::string &file_name, const std::string &file_path,
                         const std::string &additional_path_dirs);
void testIndividual_2sig();
void testTop10Individual();
void testAllSequences(const std::string &file_name, const std::string &file_path, const string &additional_path_dirs);
void evolve(const std::string &file_name, const std::string &file_path, const string &additional_path_dirs);

void reportEvaluationResults(const string &output_file, const string &test_header, const string &correct_pattern,
                             Individual &ind, vector<PatternFrequencyPair> pattFrqStructList);
string resolve_arguments(int argc, const char &argv);

using namespace std;

void countFreq(const vector<string> &arr, int n);
vector<PatternFrequencyPair> countFreqWriteToFile(vector<string> arr, int n);

string resolve_arguments(int argc, char *argv[]) {
    string file_name = "";
    if (argc == 2) {
        file_name = argv[1];
        cout << "Setting file_name to one given by user: " << file_name << endl;
    } else if (argc == 3) {
        file_name = argv[1];
        params.noOfSignals = atoi(argv[2]);
        params.noOfInputs = params.noOfSignals;
        //params.noOfinterNeurons = params.noOfSignals;
        cout << "Setting file_name to one given by user: " << file_name << endl;
        cout << "Changed parameters for network size to " << params.noOfSignals << endl;
    } else if (argc == 4) {
        file_name = argv[1];
        params.noOfSignals = atoi(argv[2]);
        params.noOfInputs = params.noOfSignals;
        //params.noOfinterNeurons = params.noOfSignals;
        cout << "Setting file_name to one given by user: " << file_name << endl;
        cout << "Changed parameters for network size to " << params.noOfSignals << endl;

        string option = argv[3];
        if (option == "doEvolution") {
            params.doEvolution = true;
        } else if (option == "writeNetworkActivity") {
            params.writeNetworkActivity = true;
        } else if (option == "doAllSequencesTest") {
            params.doAllSequencesTest = true;
        } else {
            cout << "3 arguments were provided, but the last one was not recognised" << endl;
            cout << "Possible options are: " << endl;
            cout << "\t- doEvolution: runs evolution of the network specified in "
                    "argument 1"
                 << endl;
            cout << "\t- writeNetworkActivity: asks for a pattern for which network "
                    "activity is produced"
                 << endl;
            cout << "\t- doAllSequencesTest: tests network against all possible sequences" << endl;
            cout << "Argument could be left unspecified, then the network is tested "
                    "against long random sequence."
                 << endl;
            cout << "The program will terminate" << endl;
            return "";
        }
    } else
        cout << "Proceeding with default file_name: " << file_name << endl;
    return file_name;
}
int main(int argc, char *argv[]) {

    // write params
    ofstream ofs;
    ofs.open("outputs3/params.dat", ofstream::out | ofstream::trunc);
    ofs << "No. of signals:\t" << params.noOfSignals << "\n"
        << "Pop Size:\t" << params.popSize << "\n"
        << "No. of signals:\t" << params.noOfSignals << "\n"
        << "Elite count:\t" << params.eliteCount << "\n"
        << "Mutation prob:\t" << params.mutationProb << "\n"
        << "Mutation strength:\t" << params.mutationStength << "\n"
        << "Max Gen:\t" << params.maxGen << "\n"
        << "Noise on Voltage:\t" << params.gaussianNoiseOnVoltage << "\n"
        << "Noise mean:\t" << params.gMean << "\n"
        << "Std Dev.:\t" << params.gStdDev << "\n"
        << "Signal length:\t" << params.letterSize << "\n"
        << "Silent length:\t" << params.silenctinterval << "\n"
        << "No. of signals:\t" << params.noOfLetters << "\n";

    ofs.close();

    // std::string file_name = "Top_3_5_s_28";
    // std::string file_name = "Top_3_5_swap_with_sum_N2_N3";
    // std::string file_name = "Top_3_5_swap_with_sum_N3_N2";
    // std::string file_name = "Top_3_5_swap_1_9";
    // std::string file_name = "Top_3_5";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt1";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt2";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt3";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt4";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt5";
    // std::string file_name = "Top_3_5_converging_3_to_4_pt6";
    // std::string file_name = "Top_3_5_int_rounding";
    // std::string file_name = "Top_6_5_int_rounding";
    // std::string file_name = "Top_5_5";
    // std::string file_name = "Top_6_5_int_rounding_pt2";
    // std::string file_name = "Top_7_1";
    //std::string file_path = "Topology/performing_nws_ED/Top_5_5/";
    std::string file_path = "";
    // std::string file_name = "Top_7_s7_run0";
    //   std::string file_name = "Top_7_3";
    //  std::string file_name = "Top_7_3_run1_fixed_learning";
    // std::string file_name = "Top_6_5_clipped_2pos_2neg";
    //std::string file_name = "matrix10_Top10_fitting_polynomial";
     std::string file_name = "Top_3_5";
    //std::string file_name = "";
    //         "matrix9_Top_9_1_ordering_size9_fitting_polynomial_N2_branch_zeroed";

    // std::string file_name = "Top_7_3_reevolved_8";

    if (argc > 1) {
        file_name = resolve_arguments(argc, argv);
        if (file_name == "")
            return -1;
    }

    if (params.noOfSignals == 10) {
        file_path = "Topology/performing_nws_ED/Top_10_1/";
    } else if (params.noOfSignals == 9) {
        file_path = "Topology/performing_nws_ED/Top_9_1/";
    } else if (params.noOfSignals == 8) {
        file_path = "Topology/performing_nws_ED/Top_8_1/";
    } else if (params.noOfSignals == 7) {
        file_path = "Topology/performing_nws_ED/Top_7_1/";
    } else if (params.noOfSignals == 6) {
        file_path = "6_loops_test/";
    } else if (params.noOfSignals == 5) {
        // file_path = "Topology/performing_nws_clipped/Top_5_5/";
        file_path = "Topology/performing_nws_ED/Top_5_5/";
    } else if (params.noOfSignals == 4) {
        file_path = "Topology/performing_nws_ED/Top_4_5/";
    } else if (params.noOfSignals == 3) {
        file_path = "3_loops_test/";
    }

    cout << "File name: " << file_name << endl;
    cout << "File path: " << file_path << endl;

    std::string final_fname = file_path + file_name + ".txt";
    if (!std::filesystem::exists(final_fname)) {
        throw std::runtime_error("Requested file with matrix weights does not exist, terminating\nFile:" + final_fname);
    }

    std::string output_dir = params.outputdir;
    if (params.doEvolution) {
        cout << "Running evolution" << endl;

        output_dir += "evolution/" + file_name + "/";
        checkOrCreateDirectory(output_dir);

        evolve(file_name, file_path, output_dir);
    } else if (params.doAllSequencesTest) {
        cout << "Running all sequence test" << endl;

        output_dir += "test_all_sequences/";
        checkOrCreateDirectory(output_dir);
        testAllSequences(file_name, file_path, output_dir);

    } else {
        cout << "Running long sequence test" << endl;
        if (params.noOfSignals == 2)
            testIndividual_2sig();
        checkOrCreateDirectory(output_dir);
        testIndividuals_sig(file_name, file_path, output_dir);
    }
    // testTop10Individual();
    getchar();

    return 0;
}
void reportEvaluationResults(const string &output_file, const string &test_header, const string &correct_pattern,
                             Individual &ind, vector<PatternFrequencyPair> pattFrqStructList) {
    ofstream ofs;
    // write all identified patterns to file

    ofs.open(output_file, ofstream::out | ofstream::app);
    ofs << "===-===-===-" << endl << test_header << endl;
    // ofs << "5 Signal test" << endl;
    ofs << "Max. total corr for each pattern = " << 10 << endl;
    ofs << "Identified corr. pattern = " << ind.reward << endl;
    ofs << "Incorrectly identified  = " << ind.penalty << endl;
    ofs << "FDR = " << ind.penalty / (ind.penalty + ind.reward) << endl;
    ofs << "Precision = " << ind.reward / (ind.penalty + ind.reward) << endl << endl;

    sort(pattFrqStructList.begin(), pattFrqStructList.end(),
         [](const PatternFrequencyPair &lhs, const PatternFrequencyPair &rhs) { return lhs.freq > rhs.freq; });
    // TODO add printing of TP and FP in separate loops

    vector<int> tp_indices;
    vector<int> fp_indices;
    tp_indices.clear();
    fp_indices.clear();

    for (int pf = 0; pf < pattFrqStructList.size(); pf++) {
        string str = pattFrqStructList[pf].pattern;
        if (str.find(correct_pattern) != std::string::npos)
            // .contains(correct_pattern)
            tp_indices.push_back(pf);
        else
            fp_indices.push_back(pf);
    }

    ofs << "TP:" << endl;
    for (int i: tp_indices) {
        ofs << pattFrqStructList[i].pattern << " " << pattFrqStructList[i].freq << "\t";
    }
    ofs << endl;
    ofs << "FP:" << endl;
    for (int i: fp_indices) {
        ofs << pattFrqStructList[i].pattern << " " << pattFrqStructList[i].freq << "\t";
    }
    ofs << endl;

    ofs << "Total correct patterns in the sequence:" << ind.totalCorrPatterns << endl;

    // ofs << endl << "Confusion matrix:" << endl;
    // const double TP = ind.reward;
    // const double TN = (params.reevaluateSeq - ind.totalCorrPatterns) - ind.penalty;
    // const double FP = ind.penalty;
    // const double FN = ind.totalCorrPatterns - ind.reward;
    // ofs << "True positives:" << TP << endl;
    // ofs << "True negatives:" << TN << endl;
    // ofs << "False positives:" << FP << endl;
    // ofs << "False negatives:" << FN << endl;
    // ofs << "Sum of all:" << TP + TN + FP + FN << endl;

    ofs << endl;
    ofs.close();
}
void testAllSequences(const std::string &file_name, const std::string &file_path,
                      const std::string &additional_path_dirs) {

    // vector<int> eachPattCountInTen;
    // eachPattCountInTen.resize(500000);

    // vector<string> eachPattStringInTen;
    // eachPattStringInTen.resize(500000);
    Individual ind;

    vector<PatternFrequencyPair> pattFrqStructList;


    for (int itr = 0; itr < 1; itr++) {
        std::string file_to_load = file_path + file_name + ".txt";
        ind.makeIndividualWithFixedInputOutputConnections(ADX, params.noOfInputs, params.noOfinterNeurons,
                                                          params.noOfOutputs, file_to_load);
        Ga ga;

        if (params.noOfSignals == 7) {
            cout << "Network of size 7" << endl;
            string correct_pattern = "ABCDEFG";
            cout << "\tRunning all sequence test for size 7" << endl;
            string output_file = additional_path_dirs + "Top_" + to_string(params.noOfSignals) + "_" + file_name +
                                 "_with_final_fixes2.txt";

            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 7" << endl;
            ga.reEvaluateAllPerm7_7sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "7 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 8
            cout << "\tRunning evaluation for sequence of 8" << endl;
            pattFrqStructList.clear();
            ga.reEvaluateAllPerm8_7sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "8 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 9
            cout << "\tRunning evaluation for sequence of 9" << endl;
            pattFrqStructList.clear();
            ga.reEvaluateAllPerm9_7sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "9 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next
        } else if (params.noOfSignals == 6) {
            cout << "\tRunning all sequence test for size 6" << endl;
            string correct_pattern = "ABCDEF";
            string output_file =
                    additional_path_dirs + "Top_" + to_string(params.noOfSignals) + "_" + file_name + ".txt";

            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 6" << endl;
            ga.reEvaluateAllPerm6_6sig(ind, pattFrqStructList);
            cout << "File: " << output_file << endl;
            reportEvaluationResults(output_file, "6 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 9
            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 7" << endl;
            ga.reEvaluateAllPerm7_6sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "7 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 8
            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 8" << endl;
            ga.reEvaluateAllPerm8_6sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "8 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next
        } else if (params.noOfSignals == 5) {
            cout << "\tRunning all sequence test for size 5" << endl;
            string correct_pattern = "ABCDEF";
            string output_file =
                    additional_path_dirs + "Top_" + to_string(params.noOfSignals) + "_" + file_name + ".txt";

            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 5" << endl;
            ga.reEvaluateAllPerm5_5sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "5 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 6
            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 6" << endl;
            ga.reEvaluateAllPerm6_5sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "6 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next

            // all permutations 7
            pattFrqStructList.clear();
            cout << "\tRunning evaluation for sequence of 7" << endl;
            ga.reEvaluateAllPerm7_5sig(ind, pattFrqStructList);
            reportEvaluationResults(output_file, "7 Signal test", correct_pattern, ind, pattFrqStructList);
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next
        } else {
            cout << "Option for size " + to_string(params.noOfSignals) + " was not implemented.";
        }
    }

    cout << "\nDone!" << endl;


    // check other occurrances of hard patterns
    // string signal("ABCDEF");
    // int sequenceLength = 500000;
    // vector<int> spikingIndeces;
    //
    // vector<char> signalSiquence =
    //         getRandomSequenceABCDEF(signal, sequenceLength, params.silenctinterval,
    //         params.letterSize);
    // for (int ep = 0; ep < eachPattCountInTen.size(); ep++) {
    //     spikingIndeces.clear();
    //     if (eachPattCountInTen[ep] == 10) {
    //         string inCoPat = eachPattStringInTen[ep];
    //         // insertGapsAndSetLetterSize(&inCoPat, params.silenctinterval,
    //         params.letterSize);
    //
    //         spikingIndeces = getCorrectPatternsMarkers6Letter(signalSiquence,
    //         inCoPat);
    //         // break;
    //         cout << "\n Pattern count : " << spikingIndeces.size() << endl;
    //
    //         long sizeHistory = ind.outputNeurons[0].spikeBitmap.size();
    //         bool spiking = false;
    //         // cout << "spike bitmap Size: " << sizeHistory << endl;
    //         for (int si = 0; si < spikingIndeces.size(); si++) {
    //             spiking = false;
    //             for (long rw = spikingIndeces[si]; rw < (spikingIndeces[si] + 30);
    //             rw++) {
    //                 if (ind.outputNeurons[0].spikeBitmap[rw]) {
    //                     spiking = true;
    //                 }
    //             }
    //
    //             if (spiking)
    //                 cout << getPaternBeforeSpikeIndex(signalSiquence,
    //                 spikingIndeces[si] + 30, 8) << "\tYes\t";
    //             else
    //                 cout << getPaternBeforeSpikeIndex(signalSiquence,
    //                 spikingIndeces[si] + 30, 8) << "\tNo\t";
    //         }
    //         cout << endl;
    //     }
    // }
    // cout << "\nfirst pattern total count : " << spikingIndeces.size() << endl;
    //
    // long sizeHistory = ind.outputNeurons[0].spikeBitmap.size();
    // bool spiking = false;
    // cout << "spike bitmap Size: " << sizeHistory << endl;
    // for (int si = 0; si < spikingIndeces.size(); si++) {
    //     spiking = false;
    //     for (long rw = spikingIndeces[si]; rw < (spikingIndeces[si] + 30); rw++) {
    //         if (ind.outputNeurons[0].spikeBitmap[rw]) {
    //             spiking = true;
    //         }
    //     }
    //
    //     if (spiking)
    //         cout << getPaternBeforeSpikeIndex(signalSiquence, spikingIndeces[si] +
    //         30, 8) << "  spikes  " << endl;
    //     else
    //         cout << getPaternBeforeSpikeIndex(signalSiquence, spikingIndeces[si] +
    //         30, 8) << "    " << endl;
    // }


    // cout << "fitness = " << ind.fitness << "\tReward = " << ind.rewardn <<
    // "\tPenalty = " << ind.penaltyn
    //      << "\tTrue Positive = " << ind.reward << "\tFalse Positive = " <<
    //      ind.penalty
    //      << endl;
    // for (int mip = 0; mip < ind.missIdentifiedPatterns.size(); mip++) {
    //     // cout << "\""<<ind.missIdentifiedPatterns[mip]<<"\"," << "\t";
    //     probPatternsSequence += ind.missIdentifiedPatterns[mip];
    // }
    // cout << endl;


    // cout << ind.missIdentifiedPatterns.size() << endl;
    // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // probPatternsSequence += probPatternsSequence;
    // // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // probPatternsSequence += probPatternsSequence;
    // // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // probPatternsSequence += probPatternsSequence;
    // // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // probPatternsSequence += probPatternsSequence;
    // // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // probPatternsSequence += probPatternsSequence;
    // // probPatternsSequence += "ABCDEF";
    // cout << probPatternsSequence.size() << endl;
    // cout << endl;
    // countFreq(ind.missIdentifiedPatterns, ind.missIdentifiedPatterns.size());


    // ind.printIndividualMatrix(0, 0);
    // countFreqWriteToFile(ind.missIdentifiedPatterns,
    // ind.missIdentifiedPatterns.size());
    // // ind.outputNetworkActivity();
    // ind.missIdentifiedPatterns.clear();
    // ga.reEvaluateOnProblamaticPatternsFound(ind, probPatternsSequence);
    // cout << "fitness = " << ind.fitness << "\tReward = " << ind.rewardn <<
    // "\tPenalty = " << ind.penaltyn
    //      << "\tTrue Positive = " << ind.reward << "\tFalse Positive = " <<
    //      ind.penalty
    //      << endl;
    // countFreq(ind.missIdentifiedPatterns, ind.missIdentifiedPatterns.size());
    // countFreqWriteToFile(ind.missIdentifiedPatterns,
    // ind.missIdentifiedPatterns.size());
}
void evolve(const std::string &file_name, const std::string &file_path, const string &additional_path_dirs) {
    int noOfGen = params.maxGen;
    double mutProb = params.mutationProb;
    double mutStr = params.mutationStength;

    for (int indRun = 0; indRun < params.maxRuns; indRun++) {
        cout << "===-===-===-" << endl << "Run: " << indRun << endl;
        vector<Individual> individuals;
        // create population of Ind
        for (int i = 0; i < params.popSize; i++) {
            Individual ind;

            // ind.makeRandomIndividual(ADX,3,3,1); //type, input, inter-neurons,
            // outputs
            std::string file_to_load = file_path + file_name + ".txt";
            ind.makeIndividualWithFixedInputOutputConnections(ADX, params.noOfInputs, params.noOfinterNeurons,
                                                              params.noOfOutputs, file_to_load);
            individuals.push_back(ind);
            // ind.printIndividualMatrix(i);
            // ind.deleteIndMatrix();
        }
        Ga ga;
        bool converged = false;
        int indNo = 0;

        params.mutationProb = mutProb;
        params.mutationStength = mutStr;
        // params.noOfLetters=1000;
        vector<char> hardPattern;
        for (int i = 0; i < noOfGen; i++) {

            ga.run(individuals, i, hardPattern);
            cout << "Generation " << i << endl
                 << "fitness = " << individuals[indNo].fitness << "\tRewardn = " << individuals[indNo].rewardn
                 << "\tPenaltyn = " << individuals[indNo].penaltyn << "\tTrue Positive = " << individuals[indNo].reward
                 << "\tFalse Positive = " << individuals[indNo].penalty << endl;
            // TODO move this into a function, so that print is done the same way in
            // both cases where it is used
            cout << "Confusion matrix:" << endl;
            const double TP = individuals[indNo].reward;
            const double TN =
                    (params.reevaluateSeq - individuals[indNo].totalCorrPatterns) - individuals[indNo].penalty;
            const double FP = individuals[indNo].penalty;
            const double FN = individuals[indNo].totalCorrPatterns - individuals[indNo].reward;
            cout << "True positives:" << TP << endl;
            cout << "True negatives:" << TN << endl;
            cout << "False positives:" << FP << endl;
            cout << "False negatives:" << FN << endl;
            // cout << "Sum of all:" << TP + TN + FP + FN << endl;
            cout << endl;

            individuals[indNo].missIdentifiedPatterns.clear();
            if (individuals[indNo].fitness < 0.053 && !converged) {
                std::string output_dir = additional_path_dirs + "individuals/run" + "_low_fitness/";
                checkOrCreateDirectory(output_dir);

                std::string file_name_in_run =
                        "run" + std::to_string(indRun) + "_" + "gen" + std::to_string(i) + "_low_fitness_" + file_name;

                if (params.gaussianNoiseOnVoltage)
                    file_name_in_run += "_withGaussianNoiseOnVoltage";

                individuals[indNo].printIndividualMatrix(i + 1, indRun, output_dir, file_name_in_run);
            }

            if (individuals[indNo].fitness < 0.01 && !converged) {
                // params.noOfLetters=3000;
                cout << "converged" << endl;
                converged = true;
                noOfGen = i + 4.0;
                std::string output_dir = additional_path_dirs + "individuals/run" + "_converged/";
                checkOrCreateDirectory(output_dir);

                std::string file_name_in_run =
                        "run" + std::to_string(indRun) + "_" + "gen" + std::to_string(i) + "_converged_" + file_name;

                if (params.gaussianNoiseOnVoltage)
                    file_name_in_run += "_withGaussianNoiseOnVoltage";

                individuals[indNo].printIndividualMatrix(i + 1, indRun, output_dir, file_name_in_run);
            }
            // cout<<i<<"-fitness = "<<individuals[0].fitness<<endl;
            if (i % 100 == 0) {
                std::string output_dir = additional_path_dirs;
                // checkOrCreateDirectory(output_dir);

                std::string file_name_in_run =
                        "run" + std::to_string(indRun) + "_" + "gen" + std::to_string(i) + "_" + file_name;

                if (params.gaussianNoiseOnVoltage)
                    file_name_in_run += "_withGaussianNoiseOnVoltage";
                individuals[indNo].printIndividualMatrix(i + 1, indRun, output_dir, file_name_in_run);
            }
        }
        // print network AdjMatrix
        std::string file_name_in_run = "run" + std::to_string(indRun) + "_" + file_name;

        if (params.gaussianNoiseOnVoltage)
            file_name_in_run += "_withGaussianNoiseOnVoltage";
        individuals[indNo].printIndividualMatrix(noOfGen, indRun, additional_path_dirs, file_name_in_run);

        individuals.clear();
        converged = false;
        noOfGen = params.maxGen;
    }
}

void testIndividuals_sig(const std::string &file_name, const std::string &file_path,
                         const std::string &additional_path_dirs) {

    Individual ind;

    vector<PatternFrequencyPair> pattFrqStructList;
    pattFrqStructList.clear();
    std::string file_to_load = file_path + file_name + ".txt";

    string user_sequence = "";
    for (int itr = 0; itr < 1; itr++) {
        ind.makeIndividualWithFixedInputOutputConnections(ADX, params.noOfInputs, params.noOfinterNeurons,
                                                          params.noOfOutputs, file_to_load);

        Ga ga;
        // userdefined sequence
        if (params.writeNetworkActivity) {
            user_sequence = ga.reEvaluateUserDefinedSequence(ind);

        } else {

            // random sequence
            ga.reEvaluateOnLargeSequence(ind, pattFrqStructList);
            // countFreq(ind.missIdentifiedPatterns,
            // ind.missIdentifiedPatterns.size());

            ind.printIndividualMatrix(0, 0, additional_path_dirs, file_name);
            countFreqWriteToFile(ind.missIdentifiedPatterns, ind.missIdentifiedPatterns.size());
            ind.missIdentifiedPatterns.clear();
            ind.reward = 0.0, ind.penalty = 0.0; // reset for next test
        }
    }

    if (params.writeNetworkActivity) {
        std::string activity_output_file =
                params.outputdir + "network_activity_" + file_name + "_" + user_sequence + ".txt";
        ind.outputNetworkActivity(activity_output_file);
    }
    cout << "\nDone!" << endl;
}

void testIndividual_2sig() {
    Individual ind;

    vector<PatternFrequencyPair> pattFrqStructList;
    pattFrqStructList.clear();

    for (int itr = 0; itr < 1; itr++) {
        ind.makeIndividualWithFixedInputOutputConnections(ADX, 2, 2, 1);

        Ga ga;
        // userdefined sequence
        if (params.writeNetworkActivity) {
            ga.reEvaluateUserDefinedSequence(ind);
            std::string file_name = "individual_2sig";
            std::string activity_output_file = params.outputdir + "network_activity_" + file_name + ".txt";
            ind.outputNetworkActivity(activity_output_file);
        }
        cout << "\nDone!" << endl;
    }
}
void testTop10Individual() {

    vector<int> eachPattCountInTen;
    eachPattCountInTen.resize(500000);

    vector<string> eachPattStringInTen;
    eachPattStringInTen.resize(500000);
    Individual ind;

    vector<PatternFrequencyPair> pattFrqStructList;
    pattFrqStructList.clear();

    std::vector<string> top10nwNames;
    std::string names[] = {"Top_1.dat", "Top_2.dat", "Top_3.dat", "Top_4.dat", "Top_5.dat",
                           "Top_6.dat", "Top_7.dat", "Top_8.dat", "Top_9.dat", "Top_10.dat"};
    top10nwNames.assign(names, names + 10);
    vector<Individual> top10Ind;

    for (int i = 0; i < top10nwNames.size(); i++) {
        ind.loadIndividualNetwork(ADX, 6, 6, 1, top10nwNames[i]);
        top10Ind.push_back(ind);
    }
    Ga ga;
    // for (int nw = 0; nw < top10nwNames.size();nw++)
    {
        // string probPatternsSequence;
        // ga.reEvaluateUserDefinedSequence(ind, eachPattStringInTen,
        // eachPattCountInTen); ga.reEvaluateTop10_onALargeSequence(top10Ind[nw],
        // pattFrqStructList); // random sequence
        ga.reEvaluateTop10ind(top10Ind, pattFrqStructList); // all permutations
        // countFreq(ind.missIdentifiedPatterns, ind.missIdentifiedPatterns.size());
        // top10Ind[nw].printIndividualMatrix(0, 0);
        // countFreqWriteToFile(ind.missIdentifiedPatterns,
        // ind.missIdentifiedPatterns.size()); ind.missIdentifiedPatterns.clear();

        // write all identified patterns to file
        ofstream ofs;
        ofs.open("indMatrixTop10.dat", ofstream::out | ofstream::app);
        sort(pattFrqStructList.begin(), pattFrqStructList.end(),
             [](const PatternFrequencyPair &lhs, const PatternFrequencyPair &rhs) { return lhs.freq > rhs.freq; });
        for (int pf = 0; pf < pattFrqStructList.size(); pf++) {
            ofs << pattFrqStructList[pf].pattern << " " << pattFrqStructList[pf].freq << "\t";
        }

        // ofs << "\n False pattern count: " << arr.size() << "  Unique patterns: "
        // << arr.size() - singleOccurence << " Single Occurence: " <<
        // singleOccurence << endl;
        ofs << "---------X---------X---------X---------X---------X---------X" << endl << endl;
        ofs.close();
    }

    if (params.writeNetworkActivity) {
        std::string file_name = "testTop10Individual";
        std::string activity_output_file = params.outputdir + "network_activity_" + file_name + ".txt";
        ind.outputNetworkActivity(activity_output_file);
    }
    cout << "\nDone!" << endl;
}

void countFreq(const vector<string> &arr, int n) {
    // Mark all array elements as not visited
    vector<bool> visited(n, false);
    int uniquePatternCount = 0;
    int singleOccurence = 0, multipleOccurences = 0;
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
        // uniquePatternCount++;
        //	if(arr[i].length() == 6)
        //	{
        cout << arr[i] << " " << count << "\t";

        if (count == 1)
            singleOccurence++;
        else if (count > 1) {
            multipleOccurences++;
        }

        //	}
    }
    cout << "\n False Positives: " << arr.size() << " no. of Patterns: " << multipleOccurences + singleOccurence
         << "  Patterns recognized more than once: " << multipleOccurences
         << " Patterns recognised once: " << singleOccurence << endl;
}
vector<PatternFrequencyPair> countFreqWriteToFile(vector<string> arr, int n) {
    vector<PatternFrequencyPair> patFreqList;
    PatternFrequencyPair patFreq;
    ofstream ofs;
    ofs.open("Top_" + to_string(params.noOfSignals) + ".dat", ofstream::out | ofstream::app);
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
        // uniquePatternCount++;
        // ofs << arr[i] << " " << count << "\t";
        if (count == 1)
            singleOccurence++;
    }

    sort(patFreqList.begin(), patFreqList.end(),
         [](const PatternFrequencyPair &lhs, const PatternFrequencyPair &rhs) { return lhs.freq > rhs.freq; });
    for (int pf = 0; pf < patFreqList.size(); pf++) {
        ofs << patFreqList[pf].pattern << " " << patFreqList[pf].freq << "\t";
    }

    // ofs << "\n False pattern count: " << arr.size()<< " Single Occurence: " <<
    // singleOccurence << endl;
    ofs << endl << endl;
    ofs.close();
    return patFreqList;
}

void evaluate() {}
