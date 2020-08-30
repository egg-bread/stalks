#include "csv.h"
#include <iostream>

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

    // get daisy mae price & turnip sell prices
    while (std::getline(csv, line))
    {
        std::istringstream ss(line);

        int idx = 0;
        std::string price;

        while (std::getline(ss, price, ','))
        {
            std::cout << ":) " << price << ":)" << std::endl;
            if (price == "")
            {
                // no price entered on csv, use holder INT_MIN
                contents[idx++].second.push_back(INT_MIN);
            }
            else
            {
                contents[idx++].second.push_back(1);
            }
        }
    }

    csv.close();

    return contents;
}

bool validateTurnips(Table &t)
{
    if (t.size() != 13)
    {
        // 12 cols for mon-sat am & pm, plus 1 more for daisy mae's price col
        throw TurnipException(CSV_COL_NUM_INVALID);
    }

    // validate daisy mae's sunday price
    for (int daisymae : t[0].second)
    {
        if (!Turnip::validateBasePrice(daisymae))
        {
            throw TurnipException(BASE_PRICE_OUT_OF_RANGE);
        }
    }

    // validate selling price at nooklings
    for (int day = 1; day < t.size(); ++day)
    {
        for (int sell : t[day].second)
        {
            if (!SellPrice::validateSellPrice(sell))
            {
                throw TurnipException(NOOKLING_PRICE_OUT_OF_RANGE);
            }
        }
    }

    return true;
}

std::vector<Turnip> tableToTurnip(Table &t)
{
    // TODO: count # INT_MINs per row, if thats = 12, throw turnips
}
