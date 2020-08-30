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
        MON = 1,
        TUES = 3,
        WED = 5,
        THURS = 7,
        FRI = 9,
        SAT = 11
    }; // col indexes of csv for the sell dates
    int basePrice;
    bool firstBuy; 
    std::vector<SellPrice> sellPrices; // declared sell prices from the nooklings

public:
    Turnip(int base, bool buy, std::vector<SellPrice> sells);
    static bool validateBasePrice(int base);
    // TODO: predict prices...
};

#endif