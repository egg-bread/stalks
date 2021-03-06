#ifndef _T_PAT_H_
#define _T_PAT_H_

#include <iostream>
#include "typedefs.h"

enum class Patterns {
    RANDOM,
    LARGE,
    DEC,
    SMALL
};

const std::vector <std::string> PATTERN_NAMES = {"Random", "Large Profit", "Decreasing", "Small Profit"};

// PATTERN_RATES[i], where i = previous week's pattern, stores probability (already a percentage) of getting
// pattern 0, 1, 2, 3 (in that order) for this week
const std::vector<std::vector<int>> PATTERN_RATES = {{20, 30, 15, 35}, {50, 5, 20, 25}, {25, 45, 5, 25}, {45, 25, 15, 15}};

int intceil(float val);

class TurnipPattern {
protected:
    UniquePriceSeqs allSeqs; // all pattern price seqs for the given base price
    const float MIN_DEC_AMT = 0.03;
    const float MAX_DEC_AMT = 0.05;

public:
    static const int HALF_DAYS = 12;

    TurnipPattern() {}

    virtual ~TurnipPattern() {}

    TurnipPattern(float minDecAmt, float maxDecAmt);

    UniquePriceSeqs getAllSeqs();

    virtual void calculate(int base) = 0;

    void
    price(int base, OnePriceSeq &p, int halfs, float lowBaseRate, float hiBaseRate, float minDecAmt, float maxDecAmt);
};

class RandomPat final : public TurnipPattern {
    const float INC_MIN = 0.9;
    const float INC_MAX = 1.4;
    const float DEC_MIN = 0.6;
    const float DEC_MAX = 0.8;

public:
    RandomPat() : TurnipPattern(0.04, 0.1) {}

    void calculate(int base) override;
};

class LargePat final : public TurnipPattern {
    // simmering decrease
    const float SIMMER_DEC_MIN = 0.85;
    const float SIMMER_DEC_MAX = 0.9;

    // boiling increase
    const std::vector <std::pair<float, float>> BOIL_INC_MIN_MAX = {{0.9, 1.4},
                                                                    {1.4, 2},
                                                                    {2,   6}};

    // boiling decrease
    const std::vector <std::pair<float, float>> BOIL_DEC_MIN_MAX = {{1.4, 2},
                                                                    {0.9, 1.4}};

    // rand decrease
    const float RAND_DEC_MIN = 0.4;
    const float RAND_DEC_MAX = 0.9;

public:
    LargePat() : TurnipPattern() {}

    void calculate(int base) override;
};

class DecPat final : public TurnipPattern {
    const float DEC_MIN = 0.85;
    const float DEC_MAX = 0.9;

public:
    DecPat() : TurnipPattern() {}

    void calculate(int base) override;
};

class SmallPat final : public TurnipPattern {
    const float DEC_MIN = 0.4;
    const float DEC_MAX = 0.9;
    const float INC_MIN = 0.9;
    const float INC_MAX = 1.4;
    const std::vector<float> INC_BOUNDS = {1.4, 2};

public:
    SmallPat() : TurnipPattern() {}

    void calculate(int base) override;
};

// class that calcs ALL the price sequences for all 4 patterns!
class AllPricePatterns {
    const int MIN_BASE = 90;
    const int MAX_BASE = 110;
    std::vector<TurnipPattern *> patterns;
    AllPrices *allPrices;

public:
    AllPricePatterns();

    AllPrices *getAllPrices() {
        return allPrices;
    }

    void print();

    ~AllPricePatterns() {
        for (auto &p : patterns) {
            delete p;
        }

        delete allPrices;
    }
};

#endif