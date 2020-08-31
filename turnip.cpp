#include "turnip.h"
#include "turnipexception.h"
#include <iomanip>

Turnip::Turnip(int base, bool buy, std::vector<SellPrice *> sells) : lastInputDay{0}
{
    if (validateBasePrice(base))
    {
        // construct the Turnip obj
        basePrice = base;
        firstBuy = buy;
        sellPrices = std::move(sells);
    }
    else
    {
        throw TurnipException(BASE_PRICE_OUT_OF_RANGE + std::to_string(base));
    }
}

int Turnip::getLastInputDay()
{
    return lastInputDay;
}

void Turnip::setLastInputDay(int day)
{
    lastInputDay = day;
}

void Turnip::calculateLastInputDay()
{
    if (sellPrices.back()->getPmPrice() != INT_MIN)
    {
        setLastInputDay(-1); // Sat PM filled, nothing to predict
        return;
    }

    // iterate backwards to find first non INT_MIN price
    for (int i = sellPrices.size() - 1; i >= 0; --i)
    {
        int am = i * 2;
        int pm = i * 2 + 1;

        SellPrice *price = sellPrices[i];

        if (price->getPmPrice() != INT_MIN)
        {
            setLastInputDay(pm);
            break;
        }

        if (price->getAmPrice() != INT_MIN)
        {
            setLastInputDay(am);
            break;
        }
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
    for (SellPrice *s : turnip->sellPrices)
    {
        std::string am = s->getAmPrice() == INT_MIN ? "N/A" : std::to_string(s->getAmPrice());
        std::string pm = s->getPmPrice() == INT_MIN ? "N/A" : std::to_string(s->getPmPrice());
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