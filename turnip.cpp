#include "turnip.h"
#include "turnipexception.h"
#include <iomanip>

Turnip::Turnip(int base, bool buy, std::vector<int> sells) : basePrice{base}, firstBuy{buy}, sellPrices{std::move(sells)} {}

int Turnip::getLastInputDay()
{
    return lastInputDay;
}

void Turnip::setLastInputDay(int day)
{
    lastInputDay = day;
}

bool Turnip::getFirstBuy()
{
    return firstBuy;
}

void Turnip::calculateLastInputDay()
{
    if (sellPrices.back() != INT_MIN)
    {
        setLastInputDay(-1); // Sat PM filled, nothing to predict
        return;
    }

    // iterate backwards to find first non INT_MIN price
    for (int i = sellPrices.size() - 1; i > 0; i -= 2)
    {
        int pm = i;
        int am = i - 1;

        if (sellPrices[i] != INT_MIN)
        {
            setLastInputDay(pm);
            break;
        }

        if (sellPrices[i - 1] != INT_MIN)
        {
            setLastInputDay(am);
            break;
        }
    }
}

void Turnip::predict(AllPrices *a)
{
    if (getFirstBuy())
    {
        // turnip pattern 3 (SmallPat) guaranteed
        
    } else {

    }
}

std::ostream &operator<<(std::ostream &out, Turnip *turnip)
{
    std::string buyer = turnip->firstBuy ? "Yes" : "No";

    out << "======================" << std::endl;
    out << "Base price: " << turnip->basePrice << std::endl;
    out << "First time buyer? " << buyer << std::endl;
    out << "======================" << std::endl;
    out << std::left << std::setw(5) << std::setfill(' ') << "";
    out << std::left << std::setw(5) << std::setfill(' ') << "AM";
    out << std::left << std::setw(5) << std::setfill(' ') << "PM" << std::endl;

    int day = 0;
    std::vector<int> prices = turnip->sellPrices;
    for (int p = 0; p < prices.size(); p += 2)
    {
        std::string am = prices[p] == INT_MIN ? "N/A" : std::to_string(prices[p]);
        std::string pm = prices[p + 1] == INT_MIN ? "N/A" : std::to_string(prices[p + 1]);
        out << std::left << std::setw(5) << std::setfill(' ') << Turnip::weekdays[day];
        out << std::left << std::setw(5) << std::setfill(' ') << am;
        out << std::left << std::setw(5) << std::setfill(' ') << pm << std::endl;
        ++day;
    }

    out << "======================" << std::endl;
    return out;
}

bool Turnip::validateBasePrice(int p)
{
    return (Turnip::MAX_BASE >= p && Turnip::MIN_BASE <= p) || p == INT_MIN;
}