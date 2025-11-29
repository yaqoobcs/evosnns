// #include "stdafx.h"
#include "UtilityFunctions.h"
#include <time.h>


UtilityFunctions::UtilityFunctions(void) {}


UtilityFunctions::~UtilityFunctions(void) {}

double getGaussianRandomNumber(default_random_engine de, double mean, double stddev) {
    normal_distribution<double> nd(mean, stddev); // mean followed by stdiv
    return nd(de);
}
vector<double> getGaussianValueWithGivenMeanAndSD(double mean, double sd, long long int seqSize) {
    boost::mt19937 rng;
    rng.seed(time(0));
    boost::normal_distribution<> nd(mean, sd);
    boost::variate_generator<boost::mt19937 &, boost::normal_distribution<>> var_nor(rng, nd);
    vector<double> gaussVector;
    for (long long int i = 0; i < seqSize; i++) {
        gaussVector.push_back(var_nor());
    }
    return gaussVector;
    // return var_nor();
}
double getRandomValue(double LO, double HI)

{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(LO, HI);
    return dist(gen);
    // return LO + static_cast <float> (rand()) /( static_cast <float>
    // (RAND_MAX/(HI-LO)));
}
vector<char> randomInputSequence(string signals, int sequenceLength) {

    vector<char> seq;
    for (int i = 0; i < sequenceLength; i++) {
        seq.push_back(signals[rand() % signals.length()]);
    }
    return seq;
}
vector<int> getGroundtruth(vector<char> &seq, string corSeq) {
    vector<int> correctMarkers;
    for (int i = 0; i < seq.size(); i++) {
        int j = 0, k = i;
        while (j < corSeq.size() && k < seq.size() && seq[k] == corSeq[j]) {
            j++;
            k++;
            if (j == corSeq.size()) {
                correctMarkers.push_back(i + j - 1);
                j = 0, k = 0;
                break;
            }
        }
    }
    return correctMarkers;
}

vector<char> getRandomSequence(string correctTriplet, int size, int gap, int letterSize) {
    string randSequence;
    string chSequence("AAAABBBBCCCC");
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i++) {
        char chosenChar = chSequence[rand() % chSequence.length()];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}


vector<char> getRandomSequenceABCD(string correctTriplet, int size, int gap, int letterSize) {
    string randSequence;
    string chSequence("AAAABBBBCCCCDDDD");
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i++) {
        char chosenChar = chSequence[rand() % chSequence.length()];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}


void insertSequenceIntoLetterChain(const string &phrase, const vector<string> &phrases_with_dobuling_vec,
                                   string &randSequence, const int subSequenceLen) {
    size_t half_subSequenceLen = subSequenceLen / 2;

    size_t phrase_len = phrase.length();
    // TODO
    string phrase_with_dobuling = phrases_with_dobuling_vec[0];
    size_t phrase_with_doubling_len = phrase_with_dobuling.length();
    const size_t total_phrases = phrases_with_dobuling_vec.end() - phrases_with_dobuling_vec.begin();

    int positionInSubSequence = 0;
    int position_in_sub_sequence_for_doubled_letter = 0;

    for (size_t i = 0; i < randSequence.size() - subSequenceLen; i += subSequenceLen) {
        // Where to put correct pattern
        // TODO this seq length should be a single pattern not its length
        positionInSubSequence = rand() % (half_subSequenceLen - phrase_len - 1);

        // Where to put double letter
        position_in_sub_sequence_for_doubled_letter =
                rand() % (half_subSequenceLen - phrase_len - 2) + half_subSequenceLen;

        const string &phrase_with_dobuling = phrases_with_dobuling_vec[rand() % total_phrases];

        for (size_t j = 0; j < phrase_len; j += 1) {
            size_t subSequenceLocation = i + positionInSubSequence + j;
            randSequence[subSequenceLocation] = phrase[j];
        }
        // TODo convert the following to insert pattern with dobule letter
        for (size_t k = 0; k < phrase_with_doubling_len; k += 1) {
            size_t subSequenceLocation2 = i + position_in_sub_sequence_for_doubled_letter + k;
            // inserted
            randSequence[subSequenceLocation2] = phrase_with_dobuling[k];
        }
    }
}

void insertSequenceIntoLetterChain(const string &pattern, string &randSequence, const int insertionWindowSize) {
    size_t seqLength = pattern.length();
    int positionInSubSequence;
    for (size_t i = 0; i < randSequence.size() - insertionWindowSize; i += insertionWindowSize) {
        positionInSubSequence = rand() % (insertionWindowSize - seqLength - 2);

        size_t subSequenceLocation;
        for (size_t j = 0; j < seqLength; j += 1) {
            subSequenceLocation = i + positionInSubSequence + j;
            randSequence[subSequenceLocation] = pattern[j];
        }
    }
}
vector<char> getRandomSequenceGivenCorrSignalUpgraded(const string &chSequence, int size, int gap, int letterSize,
                                                      const std::string &sequence) {
    int total_embedded_sequences = 400;
    srand(time(0));
    // srand(100);
    string randSequence;
    // string chSequence = correctTriplet;
    // double randValue = 0.0;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i++) {
        char chosenChar = chSequence[rand() % chSequence.length()];
        randSequence += chosenChar;
    }

    int subSequenceLen = 100;
    insertSequenceIntoLetterChain(sequence, randSequence, subSequenceLen);

    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
vector<char> getRandomSequenceGivenCorrSignal(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    // srand(100);
    string randSequence;
    string chSequence = correctTriplet;
    // double randValue = 0.0;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i++) {

        char chosenChar = chSequence[rand() % chSequence.length()];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        /*
        randValue = getRandomValue(0, 1);
        if (randValue < 0.02)
        {
            randSequence += correctTriplet;
            i += 5;
        }
        else */
        randSequence += chosenChar;
    }

    // cout <<"\n"<< randSequence << endl;
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> getPermutedSequence(string fileName, string str, int k, int gap, int lettersize) {
    // Create all Permutations
    /*
    string allPerm;
    allPerm.clear();
    int n = str.length(); //where n is "to chose from" is K is number chosen
    getPermutations(allPerm, str, "", n, k);
    //cout << allPerm.length() << "\t" << allPerm << endl;
    */
    // Read from file
    clock_t begin = clock();
    std::ifstream inFile;
    inFile.open(fileName); // open the input file
    std::stringstream strStream;
    strStream << inFile.rdbuf(); // read the file
    std::string allPerm = strStream.str(); // str holds the content of the file
    clock_t end = clock();
    cout << allPerm.length() << endl; //"\t" << double(end - begin) / CLOCKS_PER_SEC << endl;

    // std::ifstream t("6Permutation7.dat");
    // std::string allPerm((std::istreambuf_iterator<char>(t)),
    // std::istreambuf_iterator<char>());

    return insertGapsAndSetLetterSize(&allPerm, gap, lettersize);
}
void getPermutations(string &allPerm, const string str, std::string prefix, const int n, const int lenght)

{

    if (lenght == 1)

    {

        for (int j = 0; j < n; j++) {
            allPerm = allPerm + prefix + str[j];
            // std::cout << prefix + str[j] << std::endl;
        }
    } // Base case: lenght = 1, print the string "lenght" times + the remaining letter

    else

    {


        // One by one add all characters from "str" and recursively call for "lenght"
        // equals to "lenght"-1
        for (int i = 0; i < n; i++)

            // Next character of input added
            getPermutations(allPerm, str, prefix + str[i], n, lenght - 1);
        // "lenght" is decreased, because we have added a new character
    }
}
void allPossibleCombinations(string &seq, const string &v, std::vector<int> &pos, int n) {
    // string seq;


    if (n == v.size()) {
        for (int i = 0; i != n; i++) {
            seq += v[pos[i]];
            cout << v[pos[i]];
        }
        cout << " ";
        return;
    }

    // Loop through the vector and update position to whichever element it is pointing to.
    // Then pass that reference back to our function so we know which letter it is
    // referring to.
    for (int i = 0; i != v.size(); i++) {
        pos[n] = i;
        allPossibleCombinations(seq, v, pos, n + 1);
    }

    // return seq;
}

vector<char> getAllPossibleCombinationSequence(int gap, int letterSize) {
    string allPatterns;
    string signals = "ABCDEF";
    vector<int> pos(signals.size(), 0);
    // allPatterns = allPossibleCombinations(signals, pos, 0);

    return insertGapsAndSetLetterSize(&allPatterns, gap, letterSize);
}
vector<char> get_abcdXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    // string chSequence[]= {"ABCD", "AACD", "BBCD", "BCCD"};

    // string chSequence[] = { "ABCDEE", "ABCDEF", "ABCDFE", "ABCDFF", "AACDEF", "ABCDEF",
    // "BACDEF", "BBCDEF"}; //8
    string chSequence[] = {"ABCDEE", "ABCDFE", "ABCDFF", "AACDEF",
                           "ABCDEF", "BACDEF", "BBCDEF"}; // 1 out of 7 -> 14% approx.

    int arraySize = 7;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {

        string chosenChar = chSequence[rand() % arraySize];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

void generatePermutationsWithReplacement(const std::string &str, const std::string &current, int length,
                                         std::vector<std::string> &permutations, const std::string &prefix,
                                         const std::string &suffix) {
    if (current.length() == length) {

        permutations.push_back(prefix + current + suffix); // Add the complete permutation to the vector

        return;
    }

    for (char c: str) {
        generatePermutationsWithReplacement(str, current + c, length, permutations, prefix, suffix);
    }
}


vector<char> generateSequenceWithPermutation(const int size, const int gap, const int letterSize,
                                             const vector<string> &sequence_heads,
                                             const vector<string> &permutation_bases,
                                             const vector<string> &sequence_tails, const string &sequence) {

    size_t total_sequences = sequence_heads.size();
    vector<vector<string>> all_permutations;

    int length = 3; // Length of permutations
    for (int i = 0; i < total_sequences; i += 1) {
        // vector<string>& permutations=all_permutations[i];
        vector<string> some_vector;
        const string &permutation_base = permutation_bases[i];
        const string &prefix = sequence_heads[i];
        const string &suffix = sequence_tails[i];

        generatePermutationsWithReplacement(permutation_base, "", length, some_vector, prefix, suffix);
        all_permutations.push_back(some_vector);
    }

    // generatePermutationsWithReplacement(str, current + c, length, permutations, prefix,
    // suffix);

    size_t totalSize = 0;
    for (int i = 0; i < total_sequences; i += 1) {
        totalSize += all_permutations[i].size();
    }

    // std::string chSequence[totalSize + 2];
    std::string chSequence[totalSize];

    size_t index = 0;
    for (int i = 0; i < total_sequences; i += 1) {
        vector<string> &permutations = all_permutations[i];
        for (const string &s: permutations) {
            chSequence[index] = s;
            index++;
        }
    }

    // Populate chSequence with elements from vector2
    // for (const auto &s: permutations2) {
    //     chSequence[index] = s;
    //     index++;
    // }

    // chSequence[index] = sequence_head + permutation_base1;
    // index++;
    // chSequence[index] = sequence_head + permutation_base1;


    string randSequence;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenSeq;
    for (int i = 0; i < size; i += letterSize) {
        chosenSeq = chSequence[rand() % totalSize];

        randSequence += chosenSeq;
    }
    int subSequenceLen = 20;
    insertSequenceIntoLetterChain(sequence, randSequence, subSequenceLen);

    // For debuggin- remove once done >>>
    /*
    const std::string pattern = "CABABCDEFC";
    for (size_t i = 0; i < 10; ++i) {
        randSequence[i] = pattern[i];
    }
    */
    // For debuggin- remove once done <<<

    // TO 
    randSequence[0] = 'A';

    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> generateSequenceWithPermutation_with_doubling(const int size, const int gap, const int letterSize,
                                                           const vector<string> &sequence_heads,
                                                           const vector<string> &permutation_bases,
                                                           const vector<string> &sequence_tails,
                                                           const string &sequence) {

    size_t total_sequences = sequence_heads.size();
    vector<vector<string>> all_permutations;

    int length = 3; // Length of permutations
    for (int i = 0; i < total_sequences; i += 1) {
        // vector<string>& permutations=all_permutations[i];
        vector<string> some_vector;
        const string &permutation_base = permutation_bases[i];
        const string &prefix = sequence_heads[i];
        const string &suffix = sequence_tails[i];

        generatePermutationsWithReplacement(permutation_base, "", length, some_vector, prefix, suffix);
        all_permutations.push_back(some_vector);
    }

    // generatePermutationsWithReplacement(str, current + c, length, permutations, prefix,
    // suffix);

    size_t totalSize = 0;
    for (int i = 0; i < total_sequences; i += 1) {
        totalSize += all_permutations[i].size();
    }

    // std::string chSequence[totalSize + 2];
    std::string chSequence[totalSize];

    size_t index = 0;
    for (int i = 0; i < total_sequences; i += 1) {
        vector<string> &permutations = all_permutations[i];
        for (const string &s: permutations) {
            chSequence[index] = s;
            index++;
        }
    }

    // generateDoublings(sequence)
    vector<string> vector_with_sequences_with_doubling;
    vector_with_sequences_with_doubling.clear();
    size_t sequence_size = sequence.length();
    for (int i = 0; i < sequence_size; i += 1) {
        // string extendedSequence =
        // sequence [0:i] + sequence[i] + chSequence [i + 1:end]; // translate to c++
        std::string extendedSequence =
                sequence.substr(0, i + 1) + std::string(1, sequence[i]) + sequence.substr(i + 1, sequence_size);
        vector_with_sequences_with_doubling.push_back(extendedSequence);
    }

    // Populate chSequence with elements from vector2
    // for (const auto &s: permutations2) {
    //     chSequence[index] = s;
    //     index++;
    // }

    // chSequence[index] = sequence_head + permutation_base1;
    // index++;
    // chSequence[index] = sequence_head + permutation_base1;


    string randSequence;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenSeq;
    for (int i = 0; i < size; i += letterSize) {
        chosenSeq = chSequence[rand() % totalSize];

        randSequence += chosenSeq;
    }
    int subSequenceLen = 100;
    // insertSequenceIntoLetterChain(sequence, randSequence, subSequenceLen);
    insertSequenceIntoLetterChain(sequence, vector_with_sequences_with_doubling, randSequence, subSequenceLen);
    // TODO ensure that there are X correct sequences

    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
// vector<char> generateSequenceWithPermutation(const int size, const int gap, const int
// letterSize,
//                                              const std::string &sequence_head, const
//                                              std::string &permutation_base1, const
//                                              std::string &permutation_base2, const
//                                              std::string &sequence_tail)
//                                              {
//
//     string randSequence;
//     int length = 3; // Length of permutations
//     std::vector<std::string> permutations1;
//     std::vector<std::string> permutations2;
//
//     generatePermutationsWithReplacement(permutation_base1, "", length, permutations1,
//     sequence_head, ""); generatePermutationsWithReplacement(permutation_base2, "",
//     length, permutations2, "", sequence_tail);
//
//     // generatePermutationsWithReplacement(str, current + c, length, permutations,
//     prefix, suffix);
//
//     size_t totalSize = permutations1.size() + permutations2.size();
//     std::string chSequence[totalSize + 2];
//
//     size_t index = 0;
//     for (const string &s: permutations1) {
//         chSequence[index] = s;
//         index++;
//     }
//
//     // Populate chSequence with elements from vector2
//     for (const auto &s: permutations2) {
//         chSequence[index] = s;
//         index++;
//     }
//
//     // chSequence[index] = sequence_head + permutation_base1;
//     // index++;
//     // chSequence[index] = sequence_head + permutation_base1;
//
//
//     randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
//     string chosenSeq;
//     for (int i = 0; i < size; i += 6) {
//         chosenSeq = chSequence[rand() % totalSize];
//
//         randSequence += chosenSeq;
//     }
//     // TODO ensure that there are X correct sequences
//     return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
// }

vector<char> get_abcdefgXXX_XXXdefghij_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    const string sequence = "ABCDEFGHIJ";
    std::vector<string> sequence_heads = {"ABCDEFG", "", "ABC", "ABCD"};
    std::vector<string> permutation_bases = {"HIJ", "ABC", "DEF", "EFG"};
    std::vector<string> sequence_tails = {"", "DEFGHIJ", "GHIJ", "HIJ"};

    return generateSequenceWithPermutation_with_doubling(size, gap, letterSize, sequence_heads, permutation_bases,
                                                         sequence_tails, sequence);
}
vector<char> get_abcdefXXX_XXXdefghi_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    const string sequence = "ABCDEFGHI";
    std::vector<string> sequence_heads = {"ABCDEF", "", "ABC"};
    std::vector<string> permutation_bases = {"GHI", "ABC", "DEF"};
    std::vector<string> sequence_tails = {"", "DEFGHI", "GHI"};

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}

vector<char> get_abcdeXXX_XXXfgh_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    const string sequence = "ABCDEFGH";
    std::vector<string> sequence_heads = {"ABCDE", "", "ABC"};
    std::vector<string> permutation_bases = {"FGH", "ABC", "DEF"};
    std::vector<string> sequence_tails = {"", "DEFGH", "GH"};

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}

// 7 signals
vector<char> get_abcdXXX_XXXdefg_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    const string sequence = "ABCDEFG";
    std::vector<string> sequence_heads = {"ABCD", "", "AB", "ABC", "", ""};
    std::vector<string> permutation_bases = {
            "EFG", "ABC", "CDE", "DEF", "ABC"}; // TODO this vecor shorter by 1 element compared to other vectors here
    std::vector<string> sequence_tails = {"", "DEFG", "FG", "G", "EDEF", "CDEF"};

    // CDEF CEDEF

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}
// 6 signals
vector<char> get_abcXXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    string sequence = "ABCDEF";
    std::vector<string> sequence_heads = {"ABC", ""};
    std::vector<string> permutation_bases = {"DEF", "ABC"};
    std::vector<string> sequence_tails = {"", "DEF"};

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}
// 5 signals
vector<char> getABXXX_XXXDE_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    string sequence = "ABCDE";
    std::vector<string> sequence_heads = {"AB", ""};
    std::vector<string> permutation_bases = {"CDE", "ABC"};
    std::vector<string> sequence_tails = {"", "DE"};

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}
// 4 signals
vector<char> getABCDSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    string sequence = "ABCD";
    std::vector<string> sequence_heads = {"A", ""};
    std::vector<string> permutation_bases = {"BCD", "ABC"};
    std::vector<string> sequence_tails = {"", "D"};

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}
// 3 signals
vector<char> getABCSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));

    string sequence = "ABC";
    std::vector<string> sequence_heads = {""};
    std::vector<string> permutation_bases = {"ABC"};
    std::vector<string> sequence_tails = {
            "",
    };

    return generateSequenceWithPermutation(size, gap, letterSize, sequence_heads, permutation_bases, sequence_tails,
                                           sequence);
}
// 2 signals
vector<char> getABSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {"AA", "AB", "BA", "BB", "AA", "AB",
                           "BA", "BB", "AB", "AB"

    };
    int arraySize = 10;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenChar;
    for (int i = 0; i < size; i += 3) {
        chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}


vector<char> getHardABCDEF_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {
            "ABCDEF",
            "ABCDEF",
            "ABCDEF",
            "ABCDEF",
            "ABCDEF",
            "ABCDEF" // 6
            ,
            "ABBCDEF",
            "ABCCDEF",
            "ABCDDEF",
            "ABCDEEF",
            "ABBCDEF",
            "ABCCDEF",
            "ABCDDEF",
            "ABCDEEF" // 8
            ,
            "ACBCDEF",
            "ADBCDEF",
            "AEBCDEF",
            "ABDCDEF",
            "ABECDEF",
            "ABCEDEF" // 6
            ,
            "ACDBCDEF",
            "ACEBCDEF",
            "ADCBCDEF",
            "AECBCDEF" // 4
            ,
            "ABCDCDEF",
            "ABCECDEF",
            "ABDCCDEF",
            "ABECCDEF" // 4
            ,
            "ABCDCEEF",
            "ABCDECEF" // 2
            ,
            "ABCDEEEF",
            "ABCDEECEF",
            "ABCEDEEF",
            "ABECEDEF" // 4

    };
    // 54+6+8+6+12+9+5 = 100

    int arraySize = 34;

    // string chSequence[] = { "BECDEF", "CDDDEF", "DDDBEF", "BCDDEF", "CEDEEF", "CDCDEF",
    // "BEBDEF", "ECCDEF", "ECDEEF", "DBCDEF", "ECDEEF", "DDEEEF", "ABCDEF", "DBCDEF",
    // "BCCDEF", "DCDEEF", "BCDEEF", "DBCDEF", "BCEDEF", "CDCEEF", "EBCDEF", "ECDEEF",
    // "CEBDEF", "CBCDEF", "ABCDEF", "CDDCEF", "ABCDEF", "EEBDEF", "DBCDEF", "EFEDEF",
    // "BDCCEF", "BCEDEF", "EBCDEF", "BCEDEF", "CBDBEF", "ECBDEF", "CFDDEF", "ABCDEF",
    // "BECDEF", "DBCDEF", "ECDDEF", "CCDCEF", "CCDEEF", "BBBDEF", "CCDCEF", "CBCDEF",
    // "CECDEF", "BCDCEF", "CBCDEF", "CBDBEF", "ABCDEF", "BCCEEF", "CDCDEF", "CBDBEF",
    // "DBCDEF", "DDBCEF", "CDCCEF", "CDDEEF", "BDCDEF", "BCDDEF", "BCEDEF", "BCEDEF",
    // "DBCCEF", "ECBDEF", "ECBDEF", "CDCEEF", "CBDEEF", "ABCDEF", "CEDDEF", "EBCDEF",
    // "EECDEF", "ECBDEF", "BCDCEF", "DBCDEF", "BDCDEF", "CBBDEF", "EDDCEF", "DCDCEF",
    // "EDCDEF", "DCDEEF", "BCEDEF", "ECDEEF", "BCBDEF", "CCCDEF", "BBBDEF", "CCDDEF",
    // "DECDEF", "CBCDEF", "CCDBEF", "CCDEEF", "BCBDEF", "BCBDEF", "BECDEF", "CECDEF",
    // "CBDEEF", "BCDCEF", "EEDEEF", "DCCDEF", "BCDCEF", "ECDCEF", "CDBEEF", "ABCDEF",
    // "ABCDEF", "DBBBEF", "DDDEEF", "ECDDEF", "ABCDEF", "DCDBEF", "BDCDEF", "CECDEF",
    // "BECDEF", "EDBDEF", "ECEDEF", "CDDEEF", "CBDDEF", "BCBDEF", "DCDDEF", "CEDCEF",
    // "BECDEF", "CDEEEF", "DDCDEF", "DCDCEF", "CDEEEF", "CBBDEF", "ECDDEF", "BCDCEF",
    // "CDDEEF", "BCEDEF", "BCDBEF", "DDCDEF", "BCDBEF", "BCEDEF", "CBDEEF", "ECBDEF",
    // "DCEDEF", "EDDDEF", "DDEEEF", "ABCDEF", "CDDCEF", "EFCBEF", "CDDEEF", "CCDDEF",
    // "DCBCEF", "EEEDEF", "CDCEEF", "DBCDEF", "EBCDEF", "BCEDEF", "BDDEEF", "CCCDEF",
    // "CDDCEF", "CDDCEF", "BECDEF", "DDBDEF", "ECCDEF", "DCBDEF", "CBCDEF", "CEDCEF",
    // "DDCDEF", "EECDEF", "EDCDEF", "DCDCEF", "ECDEEF", "ABCDEF", "DCDDEF", "CCCDEF",
    // "EBBDEF", "BCDDEF", "CCBDEF", "ABCDEF" }; int arraySize = 170;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {
        string chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> get_abcdXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {"ABCDEE", "ABCDEF", "ABCDFE", "ABCDFF", "AAADEF", "AABDEF", "AACDEF", "ABADEF", "ABBDEF",
                           "ABCDEF", "ACADEF", "ACBDEF", "ACCDEF", "BAADEF", "BABDEF", "BACDEF", "BBADEF", "BBBDEF",
                           "BBCDEF", "BCADEF", "BCBDEF", "BCCDEF", "CAADEF", "CABDEF", "CACDEF", "CBADEF", "CBBDEF",
                           "CBCDEF", "CCADEF", "CCBDEF", "CCCDEF", "ABCDEF", "ABCDEF", "ABCDEF"}; // 5 out of 34 -> 14%
                                                                                                  // approx.
    int arraySize = 34;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {
        string chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
vector<char> get_abcXXX_XXcdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {"ABCDDD", "ABCDDE", "ABCDDF", "ABCDED", "ABCDEE", "ABCDEF", "ABCDFD", "ABCDFE", "ABCDFF",
                           "ABCEDD", "ABCEDE", "ABCEDF", "ABCEED", "ABCEEE", "ABCEEF", "ABCEFD", "ABCEFE", "ABCEFF",
                           "ABCFDD", "ABCFDE", "ABCFDF", "ABCFED", "ABCFEE", "ABCFEF", "ABCFFD", "ABCFFE", "ABCFFF",
                           "AACDEF", "ABCDEF", "BACDEF", "BBCDEF", "ABCDEF", "ABCDEF", "ABCDEF"};
    int arraySize = 34;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {
        string chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> getABCDEFSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    // string chSequence[]= {"ABCD", "AACD", "BBCD", "BCCD"};

    string chSequence[] = {"ABCAAF", "ABCABF", "ABCACF", "ABCADF", "ABCAEF", "ABCBAF", "ABCBBF", "ABCBCF", "ABCBDF",
                           "ABCBEF", "ABCCAF", "ABCCBF", "ABCCCF", "ABCCDF", "ABCCEF", "ABCDAF", "ABCDBF", "ABCDCF",
                           "ABCDDF", "ABCDEF", "ABCEAF", "ABCEBF", "ABCECF", "ABCEDF", "ABCEEF", "AACDEF", "ABCDEF",
                           "ACCDEF", "ADCDEF", "AECDEF", "BACDEF", "BBCDEF", "BCCDEF", "BDCDEF", "BECDEF", "CACDEF",
                           "CBCDEF", "CCCDEF", "CDCDEF", "CECDEF", "DACDEF", "DBCDEF", "DCCDEF", "DDCDEF", "DECDEF",
                           "EACDEF", "EBCDEF", "ECCDEF", "EDCDEF", "EECDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF",
                           "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF",
                           "ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF", "ABADEF", "ABBDEF",
                           "ABCDEF", "ABDDEF", "ABEDEF"};
    int arraySize = 75;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {

        string chosenChar = chSequence[rand() % arraySize];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> getTestingABCDEFSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    // string chSequence[]= {"ABCD", "AACD", "BBCD", "BCCD"};

    // string chSequence[] = { "ABCAAF", "ABCABF", "ABCACF", "ABCADF", "ABCAEF", "ABCBAF",
    // "ABCBBF", "ABCBCF", "ABCBDF", "ABCBEF","ABCCAF", "ABCCBF", "ABCCCF", "ABCCDF",
    // "ABCCEF","ABCDAF", "ABCDBF", "ABCDCF", "ABCDDF", "ABCDEF", "ABCEAF", "ABCEBF",
    // "ABCECF", "ABCEDF", "ABCEEF", 	"AACDEF", "ABCDEF", "ACCDEF", "ADCDEF", "AECDEF",
    // "BACDEF",
    //"BBCDEF", "BCCDEF", "BDCDEF", "BECDEF","CACDEF", "CBCDEF", "CCCDEF", "CDCDEF",
    //"CECDEF","DACDEF", "DBCDEF", "DCCDEF", "DDCDEF", "DECDEF", "EACDEF", "EBCDEF",
    //"ECCDEF", "EDCDEF", "EECDEF", 	"ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF",
    //"ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF",
    //"ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF","ABADEF",
    //"ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF" };

    // string chSequence[] = { "FCBEED",	"FEEDCC",	"FEBDBB",	"FECDCC",	"FBEDBD",
    // "FBEDEB",	"FEDCEB", "FEEEED",	"FDEDCB",	"FCEDCD", "ABCDEF" };

    string chSequence[] = {
            "ABCDEF", "AFEDCB", "FCCEDC", "FEDCDB", "FEDCCE", "FDCBDD", "FEDBCC", "FECDCB", "FECCDC", "FBCECC",
            "FEDDCB", "FDEDCE", "FDEDCB", "FCEDEC", "FEBDCD", "FDBCCB", "FBDDCB", "FECEDC", "FEECDC", "FCCEBE",
            "FDDAEC", "FECEBD", "FEEEBD", "FBBDBB", "FDCBBD", "FDBEBD", "FECEBC", "DFEDCB", "FEEDDC", "FCCCEC",
            "CFEDCB", "FCECEE", "FDDECB", "FECBDD", "FCECEC", "AEEDCB", "FEBDCD", "FDCDBB", "FEEDDC", "FECDBD",
            "FEDDDC", "FEBEDC", "FDBCED", "FDDDBD", "FCEDCB", "FEDCEE", "EFEDCB", "FDEDCB", "FCCEDC", "FFEDCB",
            "FBCCBB", "FCDBDE", "FEDCEB", "FEDDEC", "FEEDBC", "FDECBA", "FEDCBE", "BFEDCB", "CFEDCB", "FECBDC",
            "FEDCDB", "FEDECB", "FECDED", "FCCDEE", "BFEDCB", "FEDCEB", "FCDCED", "FDCBAA", "FEEDCB", "FBBECC",
            "FDEDBC", "FECEBE", "DFEDCB", "FEDCCB", "FEDEBC", "FEBEDC", "FEBBDC", "FBEBDB", "FDEDDD", "FCCDED",
            "AFEDCB", "FECDDB", "FEDEDB", "FEEBDC", "FCEBEB", "FEEEDC", "FEBDBD",
    };

    int arraySize = 80;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 6) {

        string chosenChar = chSequence[rand() % arraySize];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}

vector<char> getABCDESequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    // string chSequence[]= {"ABCD", "AACD", "BBCD", "BCCD"};

    string chSequence[] = {"ABCAA", "ABCAB", "ABCAC", "ABCAD", "ABCAE", "ABCBA", "ABCBB", "ABCBC", "ABCBD", "ABCBE",
                           "ABCCA", "ABCCB", "ABCCC", "ABCCD", "ABCCE", "ABCDA", "ABCDB", "ABCDC", "ABCDD", "ABCDE",
                           "ABCEA", "ABCEB", "ABCEC", "ABCED", "ABCEE", "AACDE", "ABCDE", "ACCDE", "ADCDE", "AECDE",
                           "BACDE", "BBCDE", "BCCDE", "BDCDE", "BECDE", "CACDE", "CBCDE", "CCCDE", "CDCDE", "CECDE",
                           "DACDE", "DBCDE", "DCCDE", "DDCDE", "DECDE", "EACDE", "EBCDE", "ECCDE", "EDCDE", "EECDE",
                           "ABADE", "ABBDE", "ABCDE", "ABDDE", "ABEDE", "ABADE", "ABBDE", "ABCDE", "ABDDE", "ABEDE",
                           "ABADE", "ABBDE", "ABCDE", "ABDDE", "ABEDE", "ABADE", "ABBDE", "ABCDE", "ABDDE", "ABEDE",
                           "ABADE", "ABBDE", "ABCDE", "ABDDE", "ABEDE"};
    int arraySize = 75;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 5) {

        string chosenChar = chSequence[rand() % arraySize];
        /*
        // 25% prob
        if(chosenChar=='C'&& randSequence.back()=='A')
        {
            letters.clear();
            letters="AAAACCCCTTTTTTTTTTTTTTTT"; // or AAAABBBBCCCCCCCCCCCCCCCCCCCCC;
        }
        else
        {
            letters.clear();
            letters="AAAACCCCTTT"; // or AAAABBBBCCCC
        }
        */
        randSequence += chosenChar;
    }


    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}


vector<char> getUserDefinedSequence(string inputStr, int gap, int letterSize) {
    string randSequence = inputStr;
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
vector<char> insertGapsAndSetLetterSize(string *randStr, int gap, int letterSize) {
    vector<char> tempVector;
    int varSignal = 0, varSilence = 0;
    for (long int i = 0; i < randStr->length(); i++) {
        varSignal = getUniformVariation(params.variationOnSignal);
        for (int j = 0; j < letterSize + varSignal; j++)
            tempVector.push_back(randStr->at(i));
        varSilence = getUniformVariation(params.variationOnSilence);
        for (int j = 0; j < gap + varSilence; j++)
            tempVector.push_back('Z');
    }
    return tempVector;
}

int getUniformVariation(int num) { return (rand() % (num + 1)); }

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

vector<int> getCorrectPatternsMarkers6Letter(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    int sizePS = patSequence.size();
    int count = 0;
    int marker = 0;
    int i = 0;

    for (int i = 0; i < sizePS; i++) {
        int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && patSequence[i] != word[0])
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}

vector<int> getCorrectPatternsMarkersABCDEFGHIJ(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    long int sizePS = patSequence.size();
    long int count = 0;
    long int marker = 0;
    long int i = 0;

    for (long int i = 0; i < sizePS; i++) {
        long int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4] || patSequence[i] == word[5] || patSequence[i] == word[6] ||
                              patSequence[i] == word[7] || patSequence[i] == word[8] || patSequence[i] == word[9]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}
vector<int> getCorrectPatternsMarkersABCDEFGHI(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    long int sizePS = patSequence.size();
    long int i = 0;

    bool did_increment = false;
    for (long int i = 0; i < sizePS; i++) {
        long int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4] || patSequence[i] == word[5] || patSequence[i] == word[6] ||
                              patSequence[i] == word[7] || patSequence[i] == word[8])) {
            i++;
            did_increment = true;
        }
        while (i < sizePS && patSequence[i] == 'Z') {
            i++;
            did_increment = true;
        }
        if (did_increment) {
            i--;
            did_increment = false;
        }
    }
    return correctPatternsMarkers;
}
vector<int> getCorrectPatternsMarkersABCDEFGH(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    long int sizePS = patSequence.size();
    long int count = 0;
    long int marker = 0;
    long int i = 0;

    for (long int i = 0; i < sizePS; i++) {
        long int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4] || patSequence[i] == word[5] || patSequence[i] == word[6] ||
                              patSequence[i] == word[7]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}

vector<int> getCorrectPatternsMarkersABCDEFG(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    long int sizePS = patSequence.size();
    long int count = 0;
    long int marker = 0;
    long int i = 0;

    for (long int i = 0; i < sizePS; i++) {
        long int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4] || patSequence[i] == word[5] || patSequence[i] == word[6]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}
// 6 Signals
vector<int> getCorrectPatternsMarkersABCDEF(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    long int sizePS = patSequence.size();
    long int count = 0;
    long int marker = 0;
    long int i = 0;

    for (long int i = 0; i < sizePS; i++) {
        long int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4] || patSequence[i] == word[5]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}
// 5 Signals
vector<int> getCorrectPatternsMarkersABCDE(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    int sizePS = patSequence.size();
    int count = 0;
    int marker = 0;
    int i = 0;

    bool did_increment = false;
    for (int i = 0; i < sizePS; i++) {
        int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3] ||
                              patSequence[i] == word[4])) {
            i++;
            did_increment = true;
        }
        while (i < sizePS && patSequence[i] == 'Z') {
            i++;
            did_increment = true;
        }
        if (did_increment) {
            i--;
            did_increment = false;
        }
    }
    return correctPatternsMarkers;
}

// 4 Signals
vector<int> getCorrectPatternsMarkersABCD(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    int sizePS = patSequence.size();
    int count = 0;
    int marker = 0;
    int i = 0;

    for (int i = 0; i < sizePS; i++) {
        int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2] || patSequence[i] == word[3]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}
// 3 Signals
vector<int> getCorrectPatternsMarkersABC(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    int sizePS = patSequence.size();
    int count = 0;
    int marker = 0;
    //int i = 0;

    for (int i = 0; i < sizePS; i++) {
        int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1] || patSequence[i] == word[2]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}

// 2 Signals
vector<int> getCorrectPatternsMarkersAB(vector<char> &patSequence, string corrTrip) {
    vector<int> correctPatternsMarkers;
    correctPatternsMarkers.clear();
    string word = corrTrip;
    int sizePS = patSequence.size();
    int count = 0;
    int marker = 0;
    int i = 0;

    for (int i = 0; i < sizePS; i++) {
        int j = 0;

        while (i < sizePS && patSequence[i] == word[j] && j < word.size()) {
            j++;
            if (j == word.size())
                correctPatternsMarkers.push_back(i);

            while (i < sizePS && patSequence[i] != 'Z')
                i++;
            while (i < sizePS && patSequence[i] == 'Z')
                i++;
        }

        while (i < sizePS && (patSequence[i] == word[1]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
    }
    return correctPatternsMarkers;
}


namespace fs = std::filesystem;
bool checkOrCreateDirectory(const std::string &path) {
    try {
        if (!fs::exists(path)) {
            fs::create_directories(path); // Creates all parent directories too

            std::cout << "Created directory: " << path << '\n';
            return true; // Directory was created
        } else if (fs::is_directory(path)) {
            std::cout << "Output directory already exists: " << path << '\n';
            return false; // Directory already exists
        }
        throw std::runtime_error("Path exists but is not a directory");
    } catch (const std::exception &e) {
        std::cout << "Output directory not created: " << path << '\n';
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
