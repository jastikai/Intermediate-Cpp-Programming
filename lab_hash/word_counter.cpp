/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */
 
#include "word_counter.h"


using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile) : filename(infile) {
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const {
    TextFile infile(filename);    // Open the input file using TextFile
    Dict<string, int> wordFreqs(100);  // Create a hash table with an initial size of 100

    // Read words from the file and count their frequencies
    while (infile.good()) {
        string word = infile.getNextWord();
        if (!word.empty()) {
            wordFreqs[word]++;
        }
    }

    // Create a vector to store word-frequency pairs with frequencies >= threshold
    vector<pair<string, int>> ret;
    for (const auto& entry : wordFreqs) {
        if (entry.second >= threshold) {
            ret.push_back(entry);
        }
    }

    return ret; // Return the vector of word-frequency pairs
}
