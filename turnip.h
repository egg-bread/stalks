#ifndef _TURNIP_H_
#define _TURNIP_H_

#include <vector>
#include <string>
#include <utility> // for move
#include <iostream>
#include <iomanip>
#include <climits>
#include "turnippatterns.h"

typedef std::map<OnePriceSeq, int> MatchMap;

const std::string NO_MATCHES = "Uh oh...no price pattern matches found :(";

class Turnip {
    static const int MIN_BASE = 90;
    static const int MAX_BASE = 110;
    static inline std::vector <std::string> weekdays = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    int basePrice;
    int lastInputDay; // last idx in sellPrices that has an entered val
    bool firstBuy;
    std::vector<int> sellPrices; // declared sell prices from the nooklings

    // check if inputted data matches the given sequence in the param
    bool dataMatchesPriceSequence(const std::vector<std::pair<int, int>> &ps);

    // print out price sequence on one line as:
    // Mon AM (min), Mon AM (max) Tue AM (min), Tue AM (max) ... Sat PM (min), Sat PM (max)
    void printPriceSequence(const std::vector<std::pair<int, int>> &ps);

public:
    Turnip(int base, bool buy, std::vector<int> sells);

    int getLastInputDay();

    void setLastInputDay(int day);

    bool getFirstBuy();

    void calculateLastInputDay();

    void predict(AllPrices *a);

    void predictHelper(std::map<int, UniquePriceSeqs> &, MatchMap &, int patType);

    void graph();

    static bool validateBasePrice(int base);

    friend std::ostream &operator<<(std::ostream &out, Turnip *turnip);
};

std::ostream &operator<<(std::ostream &out, Turnip &turnip);

#endif