#ifndef _SELL_PRICE_H_
#define _SELL_PRICE_H_

class SellPrice
{
    static const int MIN_SELL = 9;
    static const int MAX_SELL = 660;
    int amPrice;
    int pmPrice;

public:
    SellPrice(int am, int pm);
    
    int getAmPrice() {
        return amPrice;
    }

    int getPmPrice() {
        return pmPrice;
    }

    void setAmPrice(int a) {
        amPrice = a;
    }

    void setPmPrice(int p) {
        pmPrice = p;
    }

    static bool validateSellPrice(int p); // validate selling price
};

#endif