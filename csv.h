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
typedef std::vector <std::pair<std::string, std::vector < int>>>
Table;

// read in turnips csv
Table readCsv(std::string &file);

// validate daisy mae price and turnip sell prices
bool validateTurnips(Table & t);

// convert read in csv to turnips and the csv MUST BE VALID
// only use this if validateTurnips returns true but this fn is dummy-proofed
// with validation price checks during construction too
// t is guaranteed to have 13 elems in the vector representing the 13 rows in the csv
std::vector<Turnip *> tableToTurnip(Table & t);

bool isUnfilledField(int n);

#endif