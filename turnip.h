#ifndef _TURNIP_H_
#define _TURNIP_H_

#include <iostream>
#include <iomanip>
#include <climits>
#include "turnippatterns.h"
#include "sellprice.h"
#include "matplotlibcpp.h"
#include "typedefs.h"

// forward delc defined in csv.h, to avoid circular includes
void writeCsv(int islandNum, MatchMap& matches, int prevPat, bool firstBuy);

const std::string NO_MATCHES = "Uh oh...no price pattern matches found :(";
const std::vector <std::string> graphLabels = \
{"Mon AM", "Mon PM", "Tue AM", "Tue PM", "Wed AM", "Wed PM", "Thu AM", "Thu PM", "Fri AM", "Fri PM", "Sat AM",
 "Sat PM"};

class Turnip {
    static const int MIN_BASE;
    static const int MAX_BASE;
    static inline std::vector <std::string> weekdays = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    int prevPat; // previous week's pattern type between 0 and 3 inclusive; INT_MIN if unknown
    int basePrice;
    int lastInputDay; // last idx in sellPrices that has an entered val
    bool firstBuy;
    std::vector<int> sellPrices; // declared sell prices from the nooklings

    // check if inputted data matches the given sequence in the param
    bool dataMatchesPriceSequence(const std::vector <std::pair<int, int>> &ps);

    // print out price sequence on one line as:
    // Mon AM (min), Mon AM (max) Tue AM (min), Tue AM (max) ... Sat PM (min), Sat PM (max)
    void printPriceSequence(const std::vector <std::pair<int, int>> &ps);

public:
    Turnip(int prevPat, int base, bool buy, std::vector<int> sells);

    int getLastInputDay();

    void setLastInputDay(int day);

    bool getFirstBuy();

    // last input cell with a price for an island's csv row
    void calculateLastInputDay();

    void predict(AllPrices *a, int islandNum);

    void predictHelper(std::map<int, UniquePriceSeqs> &, MatchMap &, int patType);

    // merges all matched sequences into one sequence with min and max
    OnePriceSeq consolidateMatches(MatchMap &m, int *min, int *max);

    // graphs the consolidated match price sequence
    void graph(int islandNum, OnePriceSeq& consolidatedMatch, int yMin, int yMax);

    static bool validateBasePrice(int base);

    static bool validatePrevPatType(int pat);

    friend std::ostream &operator<<(std::ostream &out, Turnip *turnip);
};

std::ostream &operator<<(std::ostream &out, Turnip &turnip);

#endif