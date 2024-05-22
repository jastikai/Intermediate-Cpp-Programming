/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
std::vector<StringTriple> cartalk_puzzle(const PronounceDict dict, const std::string& filename) {
    std::ifstream file(filename);
    std::vector<StringTriple> result;
    if (file.is_open()) {
        std::string word;
        while (getline(file, word)) {
            if (word.size() >= 5) {
                std::string word1 = word.substr(1);
                std::string word2 = word.substr(0, 1) + word.substr(2);
                if (dict.homophones(word, word1) && dict.homophones(word, word2)) {
                    result.push_back(std::make_tuple(word, word1, word2));
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
    return result;
}


