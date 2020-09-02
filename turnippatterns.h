#ifndef _T_PAT_H_
#define _T_PAT_H_

#include <map>
#include <set>
#include <vector>
#include <utility>
#include <iostream>

// one price sequence for a pattern, each pair is 1 half day (Mon AM - Sat PM), storing min & max for that half day
typedef std::vector <std::pair<int, int>> OnePriceSeq;
// all possible price sequences for a pattern
typedef std::set <OnePriceSeq> UniquePriceSeqs;
// maps pattern type to a map of pattern type - base price - UniquePriceSeqs
typedef std::map<int, std::map<int, UniquePriceSeqs>> AllPrices;


enum class Patterns {
    RANDOM,
    LARGE,
    DEC,
    SMALL
};

const std::vector <std::string> PatternNames = {"Random", "Large Profit", "Decreasing", "Small Profit"};

int intceil(float val);

class TurnipPattern {
protected:
    UniquePriceSeqs allSeqs; // all pattern price seqs for the given base price
    const int HALF_DAYS = 12;
    const float MIN_DEC_AMT = 0.03;
    const float MAX_DEC_AMT = 0.05;

public:
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