#include "turnippatterns.h"
#include <iostream>

// from https://gist.github.com/Treeki/85be14d297c80c8b3c0a76375743325b
int intceil(float val)
{
    return (int)(val + 0.99999f);
}

/* TURNIP PATTERN METHODS */

TurnipPattern::TurnipPattern(float minDecAmt, float maxDecAmt) : MIN_DEC_AMT{minDecAmt}, MAX_DEC_AMT{maxDecAmt} {}

UniquePriceSeqs TurnipPattern::getAllSeqs()
{
    return allSeqs;
}

void TurnipPattern::price(int base, OnePriceSeq &p, int halfs, float lowBaseRate, float hiBaseRate, float minDecAmt, float maxDecAmt)
{
    while (halfs > 0)
    {
        int minHalf = intceil(base * lowBaseRate);
        int maxHalf = intceil(base * hiBaseRate);

        p.push_back(std::make_pair(minHalf, maxHalf));

        lowBaseRate -= maxDecAmt; // lowest base rate possible
        hiBaseRate -= minDecAmt;  // highest base rate possible

        --halfs;
    }
}

/* RANDOM PATTERN METHODS */

void RandomPat::calculate(int base)
{

    for (int incOne = 0; incOne <= 6; ++incOne)
    {
        int temp = 7 - incOne;
        for (int incThree = 0; incThree <= temp - 1; ++incThree)
        {
            int incTwo = temp - incThree;
            for (int decOne = 2; decOne <= 3; ++decOne)
            {
                int decTwo = 5 - decOne;

                OnePriceSeq seq; // one price seq, 6 pairs

                // inc phase 1
                price(base, seq, incOne, INC_MIN, INC_MAX, 0, 0);

                // dec phase 1
                price(base, seq, decOne, DEC_MIN, DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);

                // inc phase 2
                price(base, seq, incTwo, INC_MIN, INC_MAX, 0, 0);

                // dec phase 2
                price(base, seq, decTwo, DEC_MIN, DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);

                // inc phase 3
                price(base, seq, incThree, INC_MIN, INC_MAX, 0, 0);

                // add to set
                allSeqs.insert(seq);
            }
        }
    }
}

/* LARGE PATTERN METHODS */

void LargePat::calculate(int base)
{

    for (int simmerDec = 1; simmerDec <= 7; ++simmerDec)
    {
        int decPhase = HALF_DAYS - simmerDec - 5;

        OnePriceSeq seq;

        // simmering decrease
        price(base, seq, simmerDec, SIMMER_DEC_MIN, SIMMER_DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);

        // boiling increase: 3 halves
        for (auto &rate : BOIL_INC_MIN_MAX)
        {
            price(base, seq, 1, rate.first, rate.second, 0, 0);
        }

        // boiling decrease: 2 halves
        for (auto &rate : BOIL_DEC_MIN_MAX)
        {
            price(base, seq, 1, rate.first, rate.second, 0, 0);
        }

        // rand decrease
        price(base, seq, decPhase, RAND_DEC_MIN, RAND_DEC_MAX, 0, 0);

        // add to set
        allSeqs.insert(seq);
    }
}

/* DEC PATTERN METHODS */
void DecPat::calculate(int base)
{
    OnePriceSeq seq;
    price(base, seq, HALF_DAYS, DEC_MIN, DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);
}

/* SMALL PATTERN METHODS */
void SmallPat::calculate(int base)
{
    for (int decOne = 0; decOne <= 7; ++decOne)
    {
        for (float maxRate : INC_BOUNDS)
        {
            OnePriceSeq seq;

            // dec phase 1
            price(base, seq, decOne, DEC_MIN, DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);

            // inc phase: 5 halves
            price(base, seq, 2, INC_MIN, INC_MAX, 0, 0);
            seq.push_back(std::make_pair(intceil(INC_MAX * base) - 1, intceil(maxRate * base) - 1)); // half 3
            price(base, seq, 1, maxRate, maxRate, 0, 0);                                             // half 4
            seq.push_back(std::make_pair(intceil(INC_MAX * base) - 1, intceil(maxRate * base) - 1)); // half 5

            // dec phase 2
            price(base, seq, HALF_DAYS - decOne - 5, DEC_MIN, DEC_MAX, MIN_DEC_AMT, MAX_DEC_AMT);

            for (auto &p : seq)
            {
                std::cout << p.first << "," << p.second << " ";
            }
            std::cout << std::endl;
        }
    }
}

AllPricePatterns::AllPricePatterns()
{
    for (int base = MIN_BASE; base <= MAX_BASE; ++base)
    {
        for (int i = 0; i < 4; ++i)
        {
            TurnipPattern * turnipPat = patterns[i];
            turnipPat->calculate(base);
            allPrices->at(i)[base] = turnipPat->getAllSeqs();
        }
    } 
}