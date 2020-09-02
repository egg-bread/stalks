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
    int islands = islandTurnips.size();
    int complete = 0;
    
    std::cout << "Finding pattern matches for " << islands << " island(s)." << std::endl;
    std::cout << std::endl;
    
    for (auto &turnip : islandTurnips)
    {
        std::cout << "- On island " << complete + 1 << " out of " << islands << " -" << std::endl;
        turnip->calculateLastInputDay();
        if (turnip->getLastInputDay() == -1)
        { // -1 means that sat PM was filled in, so nothing to predict
            std::cout << CANT_PREDICT << std::endl;
            std::cout << turnip;
        }
        else
        {
            // predict from lastInputDay + 1 and onwards
            std::cout << PREDICTING << std::endl;
            std::cout << turnip;

            turnip->predict(allPrices);
        }
        ++complete;
    }

    std::cout << "Turnipin' in the stalk market done for " << complete << " island(s)." << std::endl;
}

void cleanupTurnips(std::vector<Turnip *> &islandTurnips)
{
    for (Turnip *t : islandTurnips)
    {
        delete t;
    }
}