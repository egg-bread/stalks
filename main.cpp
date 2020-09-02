#include <iostream>
#include "csv.h"
#include "turnipart.h"
#include "turnippatterns.h"

using namespace std;

/*
    Created by egg-bread on GitHub.
    Last update: Sept 1, 2020
*/

const string INVALID_ARG_NUM = "You've entered an invalid number of arguments!";
const string HELP_MSG = "Usage: ./stalks turnip_prices.csv";
const string NO_ISLANDS = "There are no islands to predict turnip prices for!";
const string CANT_PREDICT = "Nothing to predict for this island. Last possible price on Sat PM already provided. Given island's turnip data:";
const string PREDICTING = "Predicting turnip prices for this island's turnip data:";

void printReadTurnips(vector<Turnip *> &islandTurnips)
{

    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "READ IN TURNIP DATA" << endl << endl;

    for (Turnip *t : islandTurnips)
    {
        cout << t << endl;
    }

    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
}

vector<Turnip *> getTurnips(string &csv)
{
    TurnipArt *splash = new TurnipArt();
    cout << splash << endl;
    delete splash;

    cout << "Getting your turnip prices..." << endl;
    Table stalkBucket = readCsv(csv);

    cout << "Validating turnip prices..." << endl;
    validateTurnips(stalkBucket);

    cout << "Bucketing turnips..." << endl
         << endl;
    ;
    vector<Turnip *> islandTurnips = tableToTurnip(stalkBucket);

    if (islandTurnips.empty())
    {
        throw TurnipException(NO_ISLANDS);
    }

    return islandTurnips;
}

void predictTurnips(vector<Turnip *> &islandTurnips)
{
    for (auto &turnip : islandTurnips)
    {
        turnip->calculateLastInputDay();
        if (turnip->getLastInputDay() == -1)
        { // -1 means that sat PM was filled in, so nothing to predict
            cout << CANT_PREDICT << endl;
            cout << turnip << endl;
        }
        else
        {
            // predict from lastInputDay + 1 and onwards
            cout << PREDICTING << endl;
            cout << turnip << endl;
            turnip->predict();
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try
        {
            // generate all ranges of turnip price pattern sequences
            AllPrices * allPriceSeqs = new AllPrices();
            // TODO;
        
            // read in csv
            string csvFile = argv[argc - 1];
            vector<Turnip *> islandTurnips = getTurnips(csvFile);

            // iterate over all islands to predict prices
            predictTurnips(islandTurnips); // TODO;

            // generate graphs
            // TODO;

            delete allPriceSeqs;
        }
        catch (TurnipException &e)
        {
            cout << e.what() << endl;
            return 1;
        }
    }
    else
    {
        cout << INVALID_ARG_NUM << endl;
        cout << HELP_MSG << endl;
        return 1;
    }
}
