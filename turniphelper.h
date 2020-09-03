#ifndef _TURNIP_HELPER_H_
#define _TURNIP_HELPER_H_

#include <vector>
#include <string>
#include <iostream>
#include "turnip.h"
#include "turnippatterns.h"
#include "csv.h"
#include "turnipart.h"

const std::string INVALID_ARG_NUM = "You've entered an invalid number of arguments!";
const std::string HELP_MSG = "Usage: ./stalks turnip_prices.csv";
const std::string NO_ISLANDS = "There are no islands to predict turnip prices for!";
const std::string CANT_PREDICT = "Nothing to predict for this island. Last possible price on Sat PM already provided. Given island's turnip data:";
const std::string PREDICTING = "Predicting turnip prices for this island's turnip data:";

// prints out turnips in islandTurnips vector
void printReadTurnips(std::vector<Turnip *> &islandTurnips);

// get turnip(s) from csv
std::vector<Turnip *> getTurnips(std::string &csv);

// predicting turnip pattern sequences
void predictTurnips(std::vector<Turnip *> &islandTurnips, AllPrices *allPrices);

// free heap memory; called after done predicting
void cleanupTurnips(std::vector<Turnip *> &islandTurnips);

#endif