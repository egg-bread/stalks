#ifndef _SELL_PRICE_H_
#define _SELL_PRICE_H_

class SellPrice {
    static const int MIN_SELL = 9;
    static const int MAX_SELL = 660;

public:
    static bool validateSellPrice(int p); // validate selling price
};

#endif