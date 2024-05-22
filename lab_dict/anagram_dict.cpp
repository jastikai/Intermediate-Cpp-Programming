/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <algorithm>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    ifstream file(filename);
    string word;
    if (file.is_open()) {
        while (getline(file, word)) {
            string key = word;
            sort(key.begin(), key.end());
            dict[key].push_back(word);
        }
        file.close();

        // Remove words that are their own anagrams
        for (auto it = dict.begin(); it != dict.end();) {
            if (it->second.size() == 1 && it->first == it->second[0]) {
                it = dict.erase(it);
            } else {
                // Sort and remove duplicates
                sort(it->second.begin(), it->second.end());
                it->second.erase(unique(it->second.begin(), it->second.end()), it->second.end());
                ++it;
            }
        }
    }
}



/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    for (const auto& word : words) {
        string key = word;
        sort(key.begin(), key.end());
        dict[key].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    string key = word;
    sort(key.begin(), key.end());
    auto it = dict.find(key);
    if (it != dict.end()) {
        // Filter out the word itself from the anagrams
        vector<string> anagrams = it->second;
        anagrams.erase(remove(anagrams.begin(), anagrams.end(), word), anagrams.end());
        return anagrams;
    }
    return {};
}
    

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    vector< vector< string > > result;
    for (const auto& pair : dict) {
        if (pair.second.size() > 1) {
            result.push_back(pair.second);
        }
    }
    return result;
}
