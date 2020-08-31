#ifndef _TURNIP_H_
#define _TURNIP_H_

#include <vector>
#include <string>
#include <utility> // for move
#include <iostream>
#include <climits>
#include "sellprice.h"

class Turnip
{
    static const int MIN_BASE = 90;
    static const int MAX_BASE = 110;
    static inline std::vector<std::string> weekdays = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    int basePrice;
    int lastInputDay; // last idx in sellPrices that has an entered val
    bool firstBuy;
    std::vector<SellPrice *> sellPrices; // declared sell prices from the nooklings

public:
    Turnip(int base, bool buy, std::vector<SellPrice *> sells);
    int getLastInputDay();
    void setLastInputDay(int day);
    void calculateLastInputDay();
    void predict();
    static bool validateBasePrice(int base);
    friend std::ostream &operator<<(std::ostream &out, Turnip *turnip);
};

std::ostream &operator<<(std::ostream &out, Turnip &turnip);

#endif