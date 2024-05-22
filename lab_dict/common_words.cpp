#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

string remove_punct(const string& str) 
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), 
                        std::back_inserter(ret),
                        std::ptr_fun< int, int >(&std::ispunct));
    return ret;
}

/**
 * Constructs a CommonWords object from a vector of filenames. 
 * Initializes file_word_maps and common based on the given filenames.
 * @param filenames The vector of strings where the strings are the filenames to read in.
 */
CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes common, mapping a word to the number of documents it shows up in.
 */
void CommonWords::init_common() 
{
    for (const auto& file_map : file_word_maps) {
        for (const auto& pair : file_map) {
            // Increment the count of the word in common map
            common[pair.first]++;
        }
    }
}

/**
 * Initializes file_word_maps, having each index hold a map going from the word 
 * seen in that file to the number of times the word has been seen
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames) 
{
    // Resize the vector of maps
    file_word_maps.resize(filenames.size());

    // Iterate over each file
    for(size_t i = 0; i < filenames.size(); i++) {
        // Get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);

        // Count the frequency of each word and store it in the map
        for (const auto& word : words) {
            file_word_maps[i][word]++;
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. Vector contains all words that appear in all
 * files >= n times. I.e. the word must appear in all files more than 
 * n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    
    // Iterate over the common map
    for (const auto& pair : common) {
        bool is_common = true;
        // Check if the word appears in each file at least n times
        for (const auto& file_map : file_word_maps) {
            // Check if the word exists in the file map and its count is at least n
            if (file_map.find(pair.first) == file_map.end() || file_map.at(pair.first) < n) {
                is_common = false;
                break; // No need to check other files if the word is not common in this file
            }
        }
        // If the word is common in all files, add it to the output vector
        if (is_common) {
            out.push_back(pair.first);
        }
    }
    
    return out;
}


/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector< string > CommonWords::file_to_vector(const string& filename) const {
    ifstream words(filename);
    vector<string> out;

    if(words.is_open()) {
        std::istream_iterator<std::string> word_iter(words);
        while(word_iter != std::istream_iterator<string>()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
