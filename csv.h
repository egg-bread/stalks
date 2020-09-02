#ifndef _CSV_H_
#define _CSV_H_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <climits>
#include "turnipexception.h"
#include "turnip.h"
#include "sellprice.h"

// each pair is the col name and all values falling under the col in Table
typedef std::vector <std::pair<std::string, std::vector<int>>> Table;

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

#endif