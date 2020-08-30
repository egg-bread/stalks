#ifndef _TURNIP_H_
#define _TURNIP_H_

#include <vector>
#include <string>
#include "sellprice.h"

class Turnip
{
    static const int MIN_BASE = 90;
    static const int MAX_BASE = 110;
    enum
    {
        MON,
        TUES,
        WED,
        THURS,
        FRI,
        SAT
    };
    int basePrice;
    bool firstBuy; 
    std::vector<SellPrice> sellPrices; // declared sell prices from the nooklings

public:
    Turnip(int base, bool buy, std::vector<SellPrice> sells);
    static bool validateBasePrice(int base);
    // TODO: predict prices...
};

#endif