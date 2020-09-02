#include "turniphelper.h"
#include "csv.h"
#include "turnipart.h"

void printReadTurnips(std::vector<Turnip *> &islandTurnips)
{

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "READ IN TURNIP DATA" << std::endl
              << std::endl;

    for (Turnip *t : islandTurnips)
    {
        std::cout << t << std::endl;
    }

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl
              << std::endl;
}

std::vector<Turnip *> getTurnips(std::string &csv)
{
    TurnipArt *splash = new TurnipArt();
    std::cout << splash << std::endl;
    delete splash;

    std::cout << "Getting your turnip prices..." << std::endl;
    Table stalkBucket = readCsv(csv);

    std::cout << "Validating turnip prices..." << std::endl;
    validateTurnips(stalkBucket);

    std::cout << "Bucketing turnips..." << std::endl
              << std::endl;
    std::vector<Turnip *> islandTurnips = tableToTurnip(stalkBucket);

    if (islandTurnips.empty())
    {
        throw TurnipException(NO_ISLANDS);
    }

    return islandTurnips;
}

void predictTurnips(std::vector<Turnip *> &islandTurnips, AllPrices *allPrices)
{
    for (auto &turnip : islandTurnips)
    {
        turnip->calculateLastInputDay();
        if (turnip->getLastInputDay() == -1)
        { // -1 means that sat PM was filled in, so nothing to predict
            std::cout << CANT_PREDICT << std::endl;
            std::cout << turnip << std::endl;
        }
        else
        {
            // predict from lastInputDay + 1 and onwards
            std::cout << PREDICTING << std::endl;
            std::cout << turnip << std::endl;

            turnip->predict(allPrices);
        }
    }
}

void cleanupTurnips(std::vector<Turnip *> &islandTurnips)
{
    for (Turnip *t : islandTurnips)
    {
        delete t;
    }
}