#ifndef _SELL_PRICE_H_
#define _SELL_PRICE_H_

struct SellPrice {
    static const int MIN_SELL;
    static const int MAX_SELL;

    static bool validateSellPrice(int p); // validate selling price
};

#endif