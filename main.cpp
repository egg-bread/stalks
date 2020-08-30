#include <iostream>
#include "csv.h"

using namespace std;

const string INVALID_ARG_NUM = "You've entered an invalid number of arguments!";
const string HELP_MSG = "Usage: ./stalks [true | false] turnip_prices.csv";

int main(int argc, char** argv) {
    if (argc == 2 || argc == 3) {
        try {
            // ./stalks 0 turnip_prices.csv VS ./stalks turnip_prices.csv
            bool firstTimeBuyer = false;
            if (argc - 2 == 1) {
                istringstream(argv[1]) >> firstTimeBuyer; // invalid input -> false
            } 
            
            string csvFile = argv[argc - 1];

            Table stalkBucket = readCsv(csvFile);
            validateTurnips(stalkBucket);

            // TODO 
        } catch (TurnipException &e) {
            cout << e.what() << endl;
            return 1;
        }   
    } else {
        cout << INVALID_ARG_NUM << endl;
        cout << HELP_MSG << endl;
        return 1;
    }
}
