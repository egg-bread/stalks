#include <iostream>
#include "turniphelper.h"
#include "turnipexception.h"

using namespace std;

/*
    Created by egg-bread on GitHub.
    Last update: Sept 2, 2020
*/

void run(std::string csvFile)
{
    // read in csv
    vector<Turnip *> islandTurnips = getTurnips(csvFile);

    // generate all ranges of turnip price pattern sequences
    AllPricePatterns *allPriceSeqs = new AllPricePatterns();

    // iterate over all islands to predict prices & generate graphs
    predictTurnips(islandTurnips, allPriceSeqs->getAllPrices());

    delete allPriceSeqs;
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try
        {
            run(argv[argc - 1]);
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
