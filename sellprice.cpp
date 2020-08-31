#include "sellprice.h"
#include "turnipexception.h"
#include <climits>

SellPrice::SellPrice(int am, int pm) {
    if (validateSellPrice(am) && validateSellPrice(pm)) {
        amPrice = am;
        pmPrice = pm;
    } else if (!validateSellPrice(am)) {
        throw TurnipException(NOOKLING_PRICE_OUT_OF_RANGE + std::to_string(am));
    } else {
        throw TurnipException(NOOKLING_PRICE_OUT_OF_RANGE + std::to_string(pm));
    }
}

bool SellPrice::validateSellPrice(int p)
{
    // INT_MIN is val for not having a price for that day
    return (SellPrice::MAX_SELL >= p && SellPrice::MIN_SELL <= p) || p == INT_MIN;
}