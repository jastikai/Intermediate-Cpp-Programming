/**
 * @file cartalk_puzzle.cpp
 * Declares the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#ifndef CARTALK_PUZZLE_H
#define CARTALK_PUZZLE_H

#include <string>
#include <tuple>

#include "pronounce_dict.h"

typedef std::tuple< std::string, std::string, std::string > StringTriple;
typedef std::tuple< std::string, std::string> StringPair;


std::vector<StringTriple> cartalk_puzzle(const PronounceDict dict, const std::string& filename);

#endif /* CARTALK_PUZZLE_H */
