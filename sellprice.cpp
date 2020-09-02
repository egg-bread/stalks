#include "sellprice.h"
#include "turnipexception.h"
#include <climits>

bool SellPrice::validateSellPrice(int p)
{
    // INT_MIN is val for not having a price for that day
    return (SellPrice::MAX_SELL >= p && SellPrice::MIN_SELL <= p) || p == INT_MIN;
}