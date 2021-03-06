#ifndef _TURNIP_EXP_H_
#define _TURNIP_EXP_H_

#include <string>

const std::string BASE_PRICE_OUT_OF_RANGE = "Daisy Mae's Sunday price can't be: ";
const std::string NOOKLING_PRICE_OUT_OF_RANGE = "The Nooklings can't be buying your turnips for: ";
const std::string FILE_NOT_FOUND = "Csv file not found!";
const std::string CSV_COL_NUM_INVALID = "Csv file doesn't have 13 columns. Make sure to use the template csv!";
const std::string NOT_ENOUGH_SELL_DATA = "Please provide at least one day's (AM or PM) sell prices for predictions.";
const std::string EMPTY_CSV = "Csv is blank. Please input data!";
const std::string NUM_VAL_REQUIRED = "One or more price fields are not numerical. Make sure no cells have empty spaces inputted!";
const std::string INVALID_PREV_PATTERN = "A previous week pattern is invalid. Pattern types can be 0 - Random, 1 - Large Profit, 2 - Decreasing, 3 - Small Profit. Leave blank if unknown.";

class TurnipException {
    std::string err;

public:
    TurnipException(std::string err);

    const std::string &what() const;
};

#endif