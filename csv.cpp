#include "csv.h"

Table readCsv(std::string &file) {
    Table contents;
    std::ifstream csv(file);

    if (!csv.is_open()) {
        throw TurnipException(FILE_NOT_FOUND);
    }

    std::string line;

    // read header col
    if (csv.good()) {
        std::string col;

        // first line in csv
        std::getline(csv, line);

        std::istringstream ss(line);

        while (std::getline(ss, col, ',')) {
            contents.push_back({col, std::vector < int > {}});
        }
    }

    int idx = 0;
    // get prev pattern type, first buy, daisy mae price & turnip sell prices
    while (std::getline(csv, line)) {
        std::istringstream ss(line);

        std::string price;

        while (std::getline(ss, price, ',')) {
            if (price == "\r") { // cursed carriage return on csv
                ss.ignore();
                contents[idx++].second.push_back(
                        INT_MIN); // edge case where 2 or more rows of data but first row's last one is unfilled
            } else if (price.empty()) {
                // no price entered on csv, use holder INT_MIN
                contents[idx++].second.push_back(INT_MIN);
            } else {
                try {
                    contents[idx++].second.push_back(std::stoi(price));
                }
                catch (...) {
                    throw TurnipException(NUM_VAL_REQUIRED);
                }
            }
        }

        if (idx == SELL_PRICE_LAST_COL_IDX) { // edge case for when csv has only one row but last cell is unfilled
            contents[idx].second.push_back(INT_MIN);
        }

        idx = 0;
    }

    csv.close();

    return contents;
}

bool validateTurnips(Table & t) {
    if (t.empty()) {
        throw TurnipException(EMPTY_CSV);
    }

    if (t.size() != TurnipPattern::HALF_DAYS + 3) {
        // 12 cols for mon-sat am & pm, 1 for daisy mae's price col,  1 for first time buy col, 1 for prev pattern col
        throw TurnipException(CSV_COL_NUM_INVALID);
    }

    // validate previous week pattern type
    for (int prevPat: t[PREVIOUS_WEEK_PATTERN_COL_IDX].second) {
        if (!Turnip::validatePrevPatType(prevPat)) {
            throw TurnipException(INVALID_PREV_PATTERN);
        }
    }

    // validate daisy mae's sunday price
    for (int daisymae : t[DAISY_MAE_BASE_PRICE_COL_IDX].second) {
        if (!Turnip::validateBasePrice(daisymae)) {
            throw TurnipException(BASE_PRICE_OUT_OF_RANGE + std::to_string(daisymae));
        }
    }

    // validate selling price at nooklings
    for (int day = SELL_PRICE_START_COL_IDX; day < t.size(); ++day) {
        for (int sell : t[day].second) {
            if (!SellPrice::validateSellPrice(sell)) {
                throw TurnipException(NOOKLING_PRICE_OUT_OF_RANGE + std::to_string(sell));
            }
        }
    }

    return true;
}

std::vector<Turnip *> tableToTurnip(Table & t) {
    std::vector < Turnip * > islandTurnips;

    for (int island = 0; island < t[0].second.size(); ++island) { // iterate over rows
        int unfilledDays = 0;
        std::vector<int> islandPrice;

        for (int day = SELL_PRICE_START_COL_IDX; day < t.size(); day += 2) { // get that row's vals (an island's prices)

            int amPrice = t[day].second[island];
            int pmPrice = t[day + 1].second[island];

            if (isUnfilledField(amPrice)) {
                ++unfilledDays;
            }
            if (isUnfilledField(pmPrice)) {
                ++unfilledDays;
            }

            islandPrice.emplace_back(amPrice);
            islandPrice.emplace_back(pmPrice);
        } // done one island's prices

        if (unfilledDays == TurnipPattern::HALF_DAYS) {
            // no data filled in for any day, not even one, how do we predict?
            throw TurnipException(NOT_ENOUGH_SELL_DATA);
        }
        unfilledDays = 0;

        // create turnip obj
        int prevPattern = t[PREVIOUS_WEEK_PATTERN_COL_IDX].second[island];
        bool firstTimeBuyer = t[FIRST_TIME_BUY_COL_IDX].second[island];
        int basePrice = t[DAISY_MAE_BASE_PRICE_COL_IDX].second[island];

        islandTurnips.emplace_back(new Turnip(prevPattern, basePrice, firstTimeBuyer, islandPrice));
    }

    return islandTurnips;
}

bool isUnfilledField(int n) {
    return n == INT_MIN;
}

std::string percentStr(int n) {
    return std::to_string(n) + "%";
}

std::string minMaxStr(int min, int max) {
    return std::to_string(min) + " - " + std::to_string(max);
}

OutputTable matchMapToTable(MatchMap &m, int prevPat, bool firstBuy) {
    OutputTable t;

    // header cols
    t.push_back({"Pattern Type", {}});
    t.push_back({"Pattern Chance", {}});
    for (auto &col: graphLabels) {
        t.push_back({col, {}});
    }

    const int PRICE_COL_START = 2;

    // add pattern type & chance, sequence prices (as max-min) in each row
    for (auto &pat: m) {
        int pt = pat.first; // pattern type
        int chance = prevPat == INT_MIN ? INT_MIN : PATTERN_RATES[prevPat][pt]; // probability pt occurs

        if (firstBuy) {
            chance = 100;
        }

        for (int curSeq = 0; curSeq < pat.second.size(); ++curSeq) { // matched seqs under pattern type

            t[0].second.push_back(PATTERN_NAMES[pt]); // pattern type col
            t[1].second.push_back(chance != INT_MIN ? percentStr(chance) : ""); // pattern chance col

            for (int half = 0; half < pat.second[curSeq].size(); ++half) { // iterate over seq vals
                std::pair<int, int> &minMaxPricePair = pat.second[curSeq][half];
                t[half + PRICE_COL_START].second.push_back(minMaxStr(minMaxPricePair.first, minMaxPricePair.second));
            }
        }
    }

    return t;
}

void writeCsv(int islandNum, MatchMap &matches, int prevPat, bool firstBuy) {
    std::cout << "Generating csv with all matched price sequences..." << std::endl;

    const std::string csvName = "Island " + std::to_string(islandNum) + ".csv";

    OutputTable save = matchMapToTable(matches, prevPat, firstBuy);
    const int MAX_COL_IDX = save.size() - 1;
    const int DATA_SIZE = save[0].second.size();

    std::ofstream outCsv(csvName);

    // add header cols to output csv
    for (int colIdx = 0; colIdx < save.size(); ++colIdx) {
        outCsv << save[colIdx].first;
        if (colIdx != MAX_COL_IDX) {
            outCsv << ",";
        }
    }
    outCsv << "\n";

    // populate each row after header cols
    for (int data = 0; data < DATA_SIZE; ++data) {
        for (int colIdx = 0; colIdx < save.size(); ++colIdx) {
            outCsv << save[colIdx].second[data];
            if (colIdx != MAX_COL_IDX) {
                outCsv << ",";
            }
        }
        outCsv << "\n";
    }

    // close csv
    outCsv.close();

    std::cout << "Saved all matched price sequences as: " << csvName << std::endl;
}
