#include "sellprice.h"
#include <climits>

const int SellPrice::MIN_SELL = 9;
const int SellPrice::MAX_SELL = 660;

bool SellPrice::validateSellPrice(int p)
{
    // INT_MIN is val for not having a price for that day
    return (SellPrice::MAX_SELL >= p && SellPrice::MIN_SELL <= p) || p == INT_MIN;
}