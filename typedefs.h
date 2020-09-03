#ifndef STALK_PREDICTOR_TYPEDEFS_H
#define STALK_PREDICTOR_TYPEDEFS_H

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <set>

// one price sequence for a pattern, each pair is 1 half day (Mon AM - Sat PM), storing min & max for that half day
typedef std::vector <std::pair<int, int>> OnePriceSeq;

// pattern type - vector of price sequences
typedef std::map<int, std::vector<OnePriceSeq>> MatchMap;

// all possible price sequences for a pattern
typedef std::set <OnePriceSeq> UniquePriceSeqs;

// maps pattern type to a map of pattern type - base price - UniquePriceSeqs
typedef std::map<int, std::map<int, UniquePriceSeqs>> AllPrices;

// each pair is the col name and all values falling under the col in Table
typedef std::vector<std::pair<std::string, std::vector<int>>> Table;

typedef std::vector<std::pair<std::string, std::vector<std::string>>> OutputTable;

#endif //STALK_PREDICTOR_TYPEDEFS_H
