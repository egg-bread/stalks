#include "turnip.h"
#include "turnipexception.h"

Turnip::Turnip(int base, bool buy, std::vector<SellPrice> sells) {
    if (validateBasePrice(base)) {
        // construct the Turnip obj
        basePrice = base;
        firstBuy = buy;
        sellPrices = sells;
    } else {
        throw TurnipException(BASE_PRICE_OUT_OF_RANGE);
    }
}

bool Turnip::validateBasePrice(int p) {
    return Turnip::MAX_BASE >= p && Turnip::MIN_BASE <= p;
}