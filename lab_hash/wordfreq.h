#ifndef WORDFREQ_H
#define WORDFREQ_H

#include <string>
#include <vector>
#include <utility>

class WordFreq {
public:
    WordFreq(const std::string& filename);

    std::vector<std::pair<std::string, int>> getWords(int threshold);

private:
    std::string filename;
};

#endif // WORDFREQ_H
