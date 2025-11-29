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
    // return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
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

vector<char> getRandomSequenceGivenCorrSignalUpgraded(string correctTriplet, int size, int gap, int letterSize,
                                                      std::string sequence) {
    int total_embedded_sequences = 400;
    srand(time(0));
    // srand(100);
    string randSequence;
    string chSequence = correctTriplet;
    double randValue = 0.0;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i++) {
        char chosenChar = chSequence[rand() % chSequence.length()];
        randSequence += chosenChar;
    }

    size_t seqLength = sequence.length();
    int positionInSubSequence;
    for (size_t i = 0; i < randSequence.size() - 100; i += 100) {
        positionInSubSequence = rand() % (100 - seqLength - 1);

        size_t subSequenceLocation;
        for (size_t j = 0; j < seqLength; j += 1) {
            subSequenceLocation = i + positionInSubSequence + j;
            randSequence[subSequenceLocation] = sequence[j];
        }
    }

    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
vector<char> getRandomSequenceGivenCorrSignal(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    // srand(100);
    string randSequence;
    string chSequence = correctTriplet;
    double randValue = 0.0;
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
    // std::string allPerm((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

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


        // One by one add all characters from "str" and recursively call for "lenght" equals to "lenght"-1
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

    // Loop through the vector and update position to whichever element it is pointing to. Then pass that reference back
    // to our function so we know which letter it is referring to.
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

    // string chSequence[] = { "ABCDEE", "ABCDEF", "ABCDFE", "ABCDFF", "AACDEF", "ABCDEF", "BACDEF", "BBCDEF"}; //8
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

void generatePermutationsWithReplacement(const std::string& str, std::string current, int length, std::vector<std::string>& permutations, bool appendHead, const std::string& addedPiece) {
    if (current.length() == length) {

        if (appendHead)
        permutations.push_back(addedPiece + current);  // Add the complete permutation to the vector
        else
        permutations.push_back(current + addedPiece);  // Add the complete permutation to the vector

        return;
    }

    for (char c : str) {
        generatePermutationsWithReplacement(str, current + c, length, permutations, appendHead, addedPiece);
    }
}

// 7 signals
vector<char> get_abcdXXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;

    std::string sequence_head= "ABCD";
    std::string permutation_base1= "EFG";
    std::string permutation_base2= "ABC";
    std::string sequece_tail= "DEFG";

    int length = 3; // Length of permutations
    std::vector<std::string> permutations1;
    std::vector<std::string> permutations2;

    generatePermutationsWithReplacement(permutation_base1, "", length, permutations1, true, sequence_head);
    generatePermutationsWithReplacement(permutation_base2, "", length, permutations2, false, sequece_tail);

    size_t totalSize = permutations1.size() + permutations2.size();
    std::string chSequence[totalSize];

    size_t index = 0;
    for (const auto& s : permutations1) {
        chSequence[index] = s;
        index++;
    }

    // Populate chSequence with elements from vector2
    for (const auto& s : permutations2) {
        chSequence[index] = s;
        index++;
    }

    // string chSequence[] = permutations1 + permutations2{
    //         "ABCDDDG",   "ABCDDEG",   "ABCDDFG",   "ABCDEDG",   "ABCDEEG",   "ABCDEFG",   "ABCDFDG",
    //         "ABCDFEG",   "ABCDFFG",   "ABCEDDG",   "ABCEDEG",   "ABCEFDG",   "ABCEEDG",   "ABCEEEG",
    //         "ABCEEFG",   "ABCEFDDG",  "ABCEFEG",   "ABCEFFG",   "ABCFDDG",   "ABCFDEG",   "ABCFDFG",
    //         "ABCFEDG",   "ABCFEEG",   "ABCFEFG",   "ABCFFDG",   "ABCFFEG",   "ABCFFFG",   "AAADEFG",
    //         "AABDEFG",   "AACDEFG",   "ABADEFG",   "ABBDEFG",   "ABCDEFG",   "ACADEFG",   "ACBDEFG",
    //         "ACCDEFG",   "BAADEFG",   "BABDEFG",   "BACDEFG",   "BBADEFG",   "BBBDEFG",   "BBCDEFG",
    //         "BCADEFG",   "BCBDEFG",   "BCCDEFG",   "CAADEFG",   "CABDEFG",   "CACDEFG",   "CBADEFG",
    //         "CBBDEFG",   "CBCDEFG",   "CCADEFG",   "CCBDEFG",   "CCCDEFG",   "ABCDEFG",   "ABCDEFG",
    //         "ABCDEFG",   "ABCDEFG",   "ABCDEFG",   "ABCDEFG", // 6 repeats
    //         "AEABCDEFG", "AEABCDEFG", "AEABCDEFG", "ACABCDEFG", "ACABCDEFG", "ACABCDEFG", // 6 repeats
    //         "ABBCDEFG",  "ABCCDEFG",  "ABCDDEFG",  "ABCDEEFG",  "ABBCDEFG",  "ABCCDEFG",  "ABCDDEFG",
    //         "ABCDEEFG", // 8
    //         "ABBCDEFG",  "ABCCDEFG",  "ABCDDEFG",  "ABCDEEFG",  "ABBCDEFG",  "ABCCDEFG",  "ABCDDEFG",
    //         "ABCDEEFG", // 8 repeats
    //         "ABCEDEFG",  "ABDCDEFG",  "ABECDEFG",  "ACBCDEFG",  "ADBCDEFG",  "AEBCDEFG",  "AFBCDEFG", // 7
    //         "ABCEDEFG",  "ABDCDEFG",  "ABECDEFG",  "ACBCDEFG",  "ADBCDEFG",  "AEBCDEFG",  "AFBCDEFG", // 7 repeats
    //         "ABDDEFG",   "ABEDEFG",   "ACDDEFG",   "ACEDEFG",   "ADBDEFG",   "ADCDEFG",   "ADDDEFG",
    //         "ADEDEFG",   "AEBDEFG",   "AECDEFG",   "AEDDEFG",   "AEEDEFG", // 12
    //         "ABFDEFG",   "ACFDEFG",   "ADFDEFG",   "AEFDEFG",   "AFBDEFG",   "AFCDEFG",   "AFDDEFG",
    //         "AFEDEFG",   "AFFDEFG", // 9
    //         "ABDDCDEFG", "ACDBCDEFG", "ABEBCDEFG", "AEEBCDEFG", "ACBBCDEFG", /*5*/
    //         "AEDBCDEFG", "EABEDDEFG", "ADCBCDEFG", "EABDDDEFG", "ABDDDDEFG", /*5*/
    //         "ADDBCDEFG", "ADDBCDEFG", "AEDBCDEFG", "AEDBCDEFG"};
    // 54+6+8+7+12+9+5 = 101

    //int arraySize = 131;
    int arraySize = totalSize;

    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenSeq;
    for (int i = 0; i < size; i += 6) {
        chosenSeq = chSequence[rand() % arraySize];

        randSequence += chosenSeq;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
// 6 signals
vector<char> get_abcXXX_XXXdef_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {"ABCDDD",
                           "ABCDDE",
                           "ABCDDF",
                           "ABCDED",
                           "ABCDEE",
                           "ABCDEF",
                           "ABCDFD",
                           "ABCDFE",
                           "ABCDFF",
                           "ABCEDD",
                           "ABCEDE",
                           "ABCEDF",
                           "ABCEED",
                           "ABCEEE",
                           "ABCEEF",
                           "ABCEFD",
                           "ABCEFE",
                           "ABCEFF",
                           "ABCFDD",
                           "ABCFDE",
                           "ABCFDF",
                           "ABCFED",
                           "ABCFEE",
                           "ABCFEF",
                           "ABCFFD",
                           "ABCFFE",
                           "ABCFFF",
                           "AAADEF",
                           "AABDEF",
                           "AACDEF",
                           "ABADEF",
                           "ABBDEF",
                           "ABCDEF",
                           "ACADEF",
                           "ACBDEF",
                           "ACCDEF",
                           "BAADEF",
                           "BABDEF",
                           "BACDEF",
                           "BBADEF",
                           "BBBDEF",
                           "BBCDEF",
                           "BCADEF",
                           "BCBDEF",
                           "BCCDEF",
                           "CAADEF",
                           "CABDEF",
                           "CACDEF",
                           "CBADEF",
                           "CBBDEF",
                           "CBCDEF",
                           "CCADEF",
                           "CCBDEF",
                           "CCCDEF",
                           "ABCDEF",
                           "ABCDEF",
                           "ABCDEF",
                           "ABCDEF",
                           "ABCDEF",
                           "ABCDEF" // 6
                           ,
                           "AEABCDEF",
                           "AEABCDEF",
                           "AEABCDEF",
                           "ACABCDEF",
                           "ACABCDEF",
                           "ACABCDEF" // 6 repeat
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
                           "ABBCDEF",
                           "ABCCDEF",
                           "ABCDDEF",
                           "ABCDEEF",
                           "ABBCDEF",
                           "ABCCDEF",
                           "ABCDDEF",
                           "ABCDEEF" // 8 repeat
                           ,
                           "ABCEDEF",
                           "ABDCDEF",
                           "ABECDEF",
                           "ACBCDEF",
                           "ADBCDEF",
                           "AEBCDEF",
                           "AFBCDEF" // 7
                           ,
                           "ABCEDEF",
                           "ABDCDEF",
                           "ABECDEF",
                           "ACBCDEF",
                           "ADBCDEF",
                           "AEBCDEF",
                           "AFBCDEF" // 7 repeat
                           ,
                           "ABDDEF",
                           "ABEDEF",
                           "ACDDEF",
                           "ACEDEF",
                           "ADBDEF",
                           "ADCDEF",
                           "ADDDEF",
                           "ADEDEF",
                           "AEBDEF",
                           "AECDEF",
                           "AEDDEF",
                           "AEEDEF" // 12
                           ,
                           "ABFDEF",
                           "ACFDEF",
                           "ADFDEF",
                           "AEFDEF",
                           "AFBDEF",
                           "AFCDEF",
                           "AFDDEF",
                           "AFEDEF",
                           "AFFDEF" // 9
                           ,
                           "ABDDCDEF",
                           "ACDBCDEF",
                           "ABEBCDEF",
                           "AEEBCDEF",
                           "ACBBCDEF" /*5*/
                           ,
                           "AEDBCDEF",
                           "EABEDDEF",
                           "ADCBCDEF",
                           "EABDDDEF",
                           "ABDDDDEF" /*5*/
                           ,
                           "ADDBCDEF",
                           "ADDBCDEF",
                           "AEDBCDEF",
                           "AEDBCDEF"};
    // 54+6+8+7+12+9+5 = 101

    int arraySize = 131;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenChar;
    for (int i = 0; i < size; i += 6) {
        chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
// 5 signals
vector<char> getABXXX_XXXDE_Sequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {
            "ABCCC",
            "ABCCD",
            "ABCCE",
            "ABCDC",
            "ABCDD",
            "ABCDE",
            "ABCEC",
            "ABCED",
            "ABCEE",
            "ABDCC",
            "ABDCD",
            "ABDCE",
            "ABDDC",
            "ABDDD",
            "ABDDE",
            "ABDEC",
            "ABDED",
            "ABDEE",
            "ABECC",
            "ABECD",
            "ABECE",
            "ABEDC",
            "ABEDD",
            "ABEDE",
            "ABEEC",
            "ABEED",
            "ABEEE",
            "AAADE",
            "AABDE",
            "AACDE",
            "ABADE",
            "ABBDE",
            "ABCDE",
            "ACADE",
            "ACBDE",
            "ACCDE",
            "BAADE",
            "BABDE",
            "BACDE",
            "BBADE",
            "BBBDE",
            "BBCDE",
            "BCADE",
            "BCBDE",
            "BCCDE",
            "CAADE",
            "CABDE",
            "CACDE",
            "CBADE",
            "CBBDE",
            "CBCDE",
            "CCADE",
            "CCBDE",
            "CCCDE",
            "ABCDE",
            "ABCDE",
            "ABCDE",
            "ABCDE",
            "ABCDE",
            "ABCDE" // 6
            ,
            "ADABCDE",
            "ADABCDE",
            "ADABCDE",
            "ABABCDE",
            "ABABCDE",
            "ABABCDE" // 6 repeat
            ,
            "ABBCDE",
            "ABCCDE",
            "ABCDDE",
            "ABBCDE",
            "ABCCDE",
            "ABCDDE" // 6
            ,
            "ABDCDE",
            "ADBCDE",
            "ACBCDE",
            "ABDCDE",
            "ADBCDE",
            "ACBCDE" // 6
            ,
            "ABDDCDE",
            "ACDBCDE",
            "ABEBCDE",
            "AEEBCDE",
            "ACBBCDE" /*5*/
            ,
            "AEDBCDE",
            "EABEDDE",
            "ADCBCDE",
            "EABDDDE",
            "ABDDDDE" /*5*/
            ,
            "ABDDE",
            "ABDDE",
            "ABDDDE",
            "ABCCE",
            "ABCCE",
            "ABCCCE" // 6
            ,
            "ACCBCDE",
            "ADDBCDE",
            "ABBCDE",
            "ACCBCDE",
            "ADDBCDE",
            "ABBCDE" // 6
            ,
            "DACCDE",
            "AACCDE",
            "EACCDE",
            "BACCDE",
            "CACCDE",
            "ACCCDE",
            "ADCCDE",
            "EADCDE",
            "DADCDE",
            "BADCDE" // 10
    };
    int arraySize = 110;
    string chosenChar;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    for (int i = 0; i < size; i += 5) {
        chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
// 4 signals
vector<char> getABCDSequence(string correctTriplet, int size1, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {
            "ABCD",
            "ABCD",
            "ABCD",
            "ABCD",
            "ABCD",
            "BACD",
            "ACCD",
            "CACD",
            "ADCD",
            "DACD",
            "BCCD",
            "CBCD",
            "CDCD",
            "DCCD",
            "BDCD",
            "DBCD",
            "AACD",
            "BBCD",
            "CCCD",
            "DDCD" // 20
            ,
            "ABAB",
            "ABBA",
            "ABAC",
            "ABCA",
            "ABAD",
            "ABDA",
            "ABBC",
            "ABCB",
            "ABCD",
            "ABDC",
            "ABBD",
            "ABDB",
            "ABAA",
            "ABBB",
            "ABCC",
            "ABDD",
            "BBCD",
            "BBCD",
            "CBCD",
            "DBCD" // 20
            ,
            "ADABCD",
            "ADABCD",
            "ADABCD",
            "ABABCD",
            "ABABCD",
            "ABABCD" // 6
            ,
            "ABBCD",
            "ABCCD",
            "ABCDD",
            "ABBCD",
            "ABCCD",
            "ABCDD" // 6
            ,
            "ABDCD",
            "ADBCD",
            "ACBCD",
            "ABDCD",
            "ADBCD",
            "ACBCD" // 6
            ,
            "ABDDCD",
            "ACDBCD",
            "ABBCD",
            "ACDBCD",
            "ACBBCD" /*5*/
            ,
            "ACDBCD",
            "ABDD",
            "ADCBCD",
            "ABDDD",
            "ABDDDD" /*5*/
            ,
            "ABBCCD",
            "ABCCD",
            "ABCCCD",
            "ABCCD",
            "ABCCD",
            "ABCCCD" // 6
            ,
            "ACCBCD",
            "ACCBCD",
            "ABBCD",
            "ABCCBCCD",
            "ACBCD",
            "ABCBCD" // 6
    }; // 80
    int arraySize = 80; // size(chSequence); chSequence->size()
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenChar;
    for (int i = 0; i < size1; i += 4) {
        chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
}
// 3 signals
vector<char> getABCSequence(string correctTriplet, int size, int gap, int letterSize) {
    srand(time(0));
    string randSequence;
    string chSequence[] = {"AAA",    "AAB",    "AAC",    "ABA",     "ABB",    "ABC",    "ACA",    "ACB",    "ACC",
                           "BAA",    "BAB",    "BAC",    "BBA",     "BBB",    "BBC",    "BCA",    "BCB",    "BCC",
                           "CAA",    "CAB",    "CAC",    "CBA",     "CBB",    "CBC",    "CCA",    "CCB",    "CCC",
                           "ABC",    "ABC",    "ABC",    "ABC",     "ABC",    "ABC",    "ABBC",   "ABBBC",  "ABBBBC",
                           "AAC",    "AAAC",   "AABAC",  "ABAAAAC", "BBABBC", "BCABBC", "CCABBC", "CBABBC", "ABABBC",
                           "ACABBC", "BAABBC", "AAABBC", "CAABBC",  "ACCBBC"


    };
    int arraySize = 50;
    randSequence.clear(); // randSequence= 'C';//letters[rand()%letters.length()];
    string chosenChar;
    for (int i = 0; i < size; i += 3) {
        chosenChar = chSequence[rand() % arraySize];
        randSequence += chosenChar;
    }
    return insertGapsAndSetLetterSize(&randSequence, gap, letterSize);
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

    // string chSequence[] = { "BECDEF", "CDDDEF", "DDDBEF", "BCDDEF", "CEDEEF", "CDCDEF", "BEBDEF", "ECCDEF", "ECDEEF",
    // "DBCDEF", "ECDEEF", "DDEEEF", "ABCDEF", "DBCDEF", "BCCDEF", "DCDEEF", "BCDEEF", "DBCDEF", "BCEDEF", "CDCEEF",
    // "EBCDEF", "ECDEEF", "CEBDEF", "CBCDEF", "ABCDEF", "CDDCEF", "ABCDEF", "EEBDEF", "DBCDEF", "EFEDEF", "BDCCEF",
    // "BCEDEF", "EBCDEF", "BCEDEF", "CBDBEF", "ECBDEF", "CFDDEF", "ABCDEF", "BECDEF", "DBCDEF", "ECDDEF", "CCDCEF",
    // "CCDEEF", "BBBDEF", "CCDCEF", "CBCDEF", "CECDEF", "BCDCEF", "CBCDEF", "CBDBEF", "ABCDEF", "BCCEEF", "CDCDEF",
    // "CBDBEF", "DBCDEF", "DDBCEF", "CDCCEF", "CDDEEF", "BDCDEF", "BCDDEF", "BCEDEF", "BCEDEF", "DBCCEF", "ECBDEF",
    // "ECBDEF", "CDCEEF", "CBDEEF", "ABCDEF", "CEDDEF", "EBCDEF", "EECDEF", "ECBDEF", "BCDCEF", "DBCDEF", "BDCDEF",
    // "CBBDEF", "EDDCEF", "DCDCEF", "EDCDEF", "DCDEEF", "BCEDEF", "ECDEEF", "BCBDEF", "CCCDEF", "BBBDEF", "CCDDEF",
    // "DECDEF", "CBCDEF", "CCDBEF", "CCDEEF", "BCBDEF", "BCBDEF", "BECDEF", "CECDEF", "CBDEEF", "BCDCEF", "EEDEEF",
    // "DCCDEF", "BCDCEF", "ECDCEF", "CDBEEF", "ABCDEF", "ABCDEF", "DBBBEF", "DDDEEF", "ECDDEF", "ABCDEF", "DCDBEF",
    // "BDCDEF", "CECDEF", "BECDEF", "EDBDEF", "ECEDEF", "CDDEEF", "CBDDEF", "BCBDEF", "DCDDEF", "CEDCEF", "BECDEF",
    // "CDEEEF", "DDCDEF", "DCDCEF", "CDEEEF", "CBBDEF", "ECDDEF", "BCDCEF", "CDDEEF", "BCEDEF", "BCDBEF", "DDCDEF",
    // "BCDBEF", "BCEDEF", "CBDEEF", "ECBDEF", "DCEDEF", "EDDDEF", "DDEEEF", "ABCDEF", "CDDCEF", "EFCBEF", "CDDEEF",
    // "CCDDEF", "DCBCEF", "EEEDEF", "CDCEEF", "DBCDEF", "EBCDEF", "BCEDEF", "BDDEEF", "CCCDEF", "CDDCEF", "CDDCEF",
    // "BECDEF", "DDBDEF", "ECCDEF", "DCBDEF", "CBCDEF", "CEDCEF", "DDCDEF", "EECDEF", "EDCDEF", "DCDCEF", "ECDEEF",
    // "ABCDEF", "DCDDEF", "CCCDEF", "EBBDEF", "BCDDEF", "CCBDEF", "ABCDEF" }; int arraySize = 170;
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
    string chSequence[] = {
            "ABCDEE", "ABCDEF", "ABCDFE", "ABCDFF", "AAADEF", "AABDEF", "AACDEF", "ABADEF", "ABBDEF",
            "ABCDEF", "ACADEF", "ACBDEF", "ACCDEF", "BAADEF", "BABDEF", "BACDEF", "BBADEF", "BBBDEF",
            "BBCDEF", "BCADEF", "BCBDEF", "BCCDEF", "CAADEF", "CABDEF", "CACDEF", "CBADEF", "CBBDEF",
            "CBCDEF", "CCADEF", "CCBDEF", "CCCDEF", "ABCDEF", "ABCDEF", "ABCDEF"}; // 5 out of 34 -> 14% approx.
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

    // string chSequence[] = { "ABCAAF", "ABCABF", "ABCACF", "ABCADF", "ABCAEF", "ABCBAF", "ABCBBF", "ABCBCF", "ABCBDF",
    // "ABCBEF","ABCCAF", "ABCCBF", "ABCCCF", "ABCCDF", "ABCCEF","ABCDAF", "ABCDBF", "ABCDCF", "ABCDDF", "ABCDEF",
    // "ABCEAF", "ABCEBF", "ABCECF", "ABCEDF", "ABCEEF", 	"AACDEF", "ABCDEF", "ACCDEF", "ADCDEF", "AECDEF", "BACDEF",
    //"BBCDEF", "BCCDEF", "BDCDEF", "BECDEF","CACDEF", "CBCDEF", "CCCDEF", "CDCDEF", "CECDEF","DACDEF", "DBCDEF",
    //"DCCDEF", "DDCDEF", "DECDEF", "EACDEF", "EBCDEF", "ECCDEF", "EDCDEF", "EECDEF", 	"ABADEF", "ABBDEF", "ABCDEF",
    //"ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF",
    //"ABEDEF", "ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF","ABADEF", "ABBDEF", "ABCDEF", "ABDDEF", "ABEDEF" };

    // string chSequence[] = { "FCBEED",	"FEEDCC",	"FEBDBB",	"FECDCC",	"FBEDBD", "FBEDEB",	"FEDCEB",
    // "FEEEED",	"FDEDCB",	"FCEDCD", "ABCDEF" };

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
                              patSequence[i] == word[4]))
            i++;
        while (i < sizePS && patSequence[i] == 'Z')
            i++;
        i--;
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
