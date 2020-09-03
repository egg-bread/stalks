#ifndef _CSV_H_
#define _CSV_H_

#include <sstream>
#include <fstream>
#include <climits>
#include <iostream>
#include "turnipexception.h"
#include "sellprice.h"
#include "turnip.h"
#include "typedefs.h"

const int PREVIOUS_WEEK_PATTERN_COL_IDX = 0;
const int FIRST_TIME_BUY_COL_IDX = 1;
const int DAISY_MAE_BASE_PRICE_COL_IDX = 2;
const int SELL_PRICE_START_COL_IDX = 3;
const int SELL_PRICE_LAST_COL_IDX = 12 + SELL_PRICE_START_COL_IDX - 1;

// read in turnips csv
Table readCsv(std::string &file);

// validate daisy mae price and turnip sell prices
bool validateTurnips(Table & t);

// convert read in csv to turnips and the csv MUST BE VALID
// only use this if validateTurnips returns true
std::vector<Turnip *> tableToTurnip(Table & t);

bool isUnfilledField(int n);

// checks if only one pattern type is among all matched price sequences
bool onlyOnePatternTypeInMatch(MatchMap &m);

std::string percentStr(int n);

std::string minMaxStr(int min, int max);

OutputTable matchMapToTable(MatchMap &m, int prevPat, bool firstBuy);

void writeCsv(int islandNum, MatchMap &matches, int prevPat, bool firstBuy);



#endif