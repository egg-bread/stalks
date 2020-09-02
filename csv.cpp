#include "csv.h"


Table readCsv(std::string &file)
{
    Table contents;
    std::ifstream csv(file);

    if (!csv.is_open())
    {
        throw TurnipException(FILE_NOT_FOUND);
    }

    std::string line;

    // read header col
    if (csv.good())
    {
        std::string col;

        // first line in csv
        std::getline(csv, line);

        std::istringstream ss(line);

        while (std::getline(ss, col, ','))
        {
            contents.push_back({col, std::vector<int>{}});
        }
    }

    int idx = 0;
    // get first buy, daisy mae price & turnip sell prices
    while (std::getline(csv, line))
    {
        std::istringstream ss(line);

        std::string price;

        while (std::getline(ss, price, ','))
        {
            if (price == "\r")
            { // cursed carriage return on csv
                ss.ignore();
                contents[idx++].second.push_back(INT_MIN); // edge case where 2 or more rows of data but first row's last one is unfilled
            }
            else if (price.empty())
            {
                // no price entered on csv, use holder INT_MIN
                contents[idx++].second.push_back(INT_MIN);
            }
            else
            {
                try
                {
                    contents[idx++].second.push_back(std::stoi(price));
                }
                catch (...)
                {
                    throw TurnipException(NUM_VAL_REQUIRED);
                }
            }
        }

        if (idx == 13)
        { // edge case for when csv has only one row but last cell is unfilled
            contents[idx].second.push_back(INT_MIN);
        }

        idx = 0;
    }

    csv.close();

    return contents;
}

bool validateTurnips(Table &t)
{
    if (t.empty())
    {
        throw TurnipException(EMPTY_CSV);
    }

    if (t.size() != 14)
    {
        // 12 cols for mon-sat am & pm, plus 1 more for daisy mae's price col and 1 for first time buy col
        throw TurnipException(CSV_COL_NUM_INVALID);
    }

    // validate daisy mae's sunday price
    for (int daisymae : t[1].second)
    {
        if (!Turnip::validateBasePrice(daisymae))
        {
            throw TurnipException(BASE_PRICE_OUT_OF_RANGE + std::to_string(daisymae));
        }
    }

    // validate selling price at nooklings
    for (int day = 2; day < t.size(); ++day)
    {
        for (int sell : t[day].second)
        {
            if (!SellPrice::validateSellPrice(sell))
            {
                throw TurnipException(NOOKLING_PRICE_OUT_OF_RANGE + std::to_string(sell));
            }
        }
    }

    return true;
}

std::vector<Turnip *> tableToTurnip(Table &t)
{
    std::vector<Turnip *> islandTurnips;

    for (int island = 0; island < t[0].second.size(); ++island)
    { // iterate over rows
        int unfilledDays = 0;
        std::vector<int> islandPrice;

        for (int day = 2; day < t.size(); day += 2)
        { // get that row's vals (an island's prices)

            int amPrice = t[day].second[island];
            int pmPrice = t[day + 1].second[island];

            if (isUnfilledField(amPrice))
            {
                ++unfilledDays;
            }
            if (isUnfilledField(pmPrice))
            {
                ++unfilledDays;
            }

            islandPrice.emplace_back(amPrice);
            islandPrice.emplace_back(pmPrice);
        } // done one island's prices

        if (unfilledDays == 12)
        {
            // no data filled in for any day, not even one, how do we predict?
            throw TurnipException(NOT_ENOUGH_SELL_DATA);
        }
        unfilledDays = 0;

        // create turnip obj
        bool firstTimeBuyer = t[0].second[island];
        int basePrice = t[1].second[island];

        islandTurnips.emplace_back(new Turnip(basePrice, firstTimeBuyer, islandPrice));
    }

    return islandTurnips;
}

bool isUnfilledField(int n)
{
    return n == INT_MIN;
}
