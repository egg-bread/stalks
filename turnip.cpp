#include "turnip.h"

namespace plt = matplotlibcpp;

const int Turnip::MIN_BASE = 90;
const int Turnip::MAX_BASE = 110;

Turnip::Turnip(int prevPat, int base, bool buy, std::vector<int> sells) : prevPat{prevPat}, basePrice{base},
                                                                          firstBuy{buy},
                                                                          sellPrices{std::move(sells)} {}

int Turnip::getLastInputDay() {
    return lastInputDay;
}

void Turnip::setLastInputDay(int day) {
    lastInputDay = day;
}

bool Turnip::getFirstBuy() {
    return firstBuy;
}

void Turnip::calculateLastInputDay() {
    if (sellPrices.back() != INT_MIN) {
        setLastInputDay(-1); // Sat PM filled, nothing to predict
        return;
    }

    // iterate backwards to find first non INT_MIN price
    for (int i = sellPrices.size() - 1; i > 0; i -= 2) {
        int pm = i;
        int am = i - 1;

        if (sellPrices[i] != INT_MIN) {
            setLastInputDay(pm);
            break;
        }

        if (sellPrices[i - 1] != INT_MIN) {
            setLastInputDay(am);
            break;
        }
    }
}

bool Turnip::dataMatchesPriceSequence(const std::vector <std::pair<int, int>> &ps) {
    for (int i = 0; i <= lastInputDay; ++i) {
        if (sellPrices[i] != INT_MIN && (ps[i].first > sellPrices[i] || ps[i].second < sellPrices[i])) {
            return false;
        }
    }
    return true;
}

void Turnip::printPriceSequence(const std::vector <std::pair<int, int>> &ps) {
    for (auto &pair: ps) {
        std::cout << pair.first << "," << pair.second << " ";
    }
    std::cout << std::endl << std::endl;
}

void Turnip::predict(AllPrices *a, int islandNum) {
    MatchMap matches; // pattern sequence & pattern type kv pair

    if (getLastInputDay()) {
        // turnip pattern 3 (SmallPat) guaranteed
        std::map<int, UniquePriceSeqs> &smallPat = (*a)[(int) Patterns::SMALL];
        predictHelper(smallPat, matches, (int) Patterns::SMALL);
    } else {
        // check against all 4 patterns
        for (int option = 0; option < 4; ++option) {
            std::map<int, UniquePriceSeqs> &pat = (*a)[option];
            predictHelper(pat, matches, option);
        }
    }

    if (matches.empty()) {
        std::cout << NO_MATCHES << std::endl;
        std::cout << std::endl;
    } else {
        int numMatches = matches[0].size() + matches[1].size() + matches[2].size() + matches[3].size();
        std::cout << "Found " << numMatches << " potential price sequences!" << std::endl;

        int matchMin = SellPrice::MAX_SELL, matchMax = SellPrice::MIN_SELL;
        OnePriceSeq consolidatedMatch = consolidateMatches(matches, &matchMin, &matchMax);

        writeCsv(islandNum, matches, prevPat, firstBuy);
        graph(islandNum, consolidatedMatch, matchMin, matchMax);

        std::cout << "Completed prediction for current island." << std::endl << std::endl;
    }
}

void Turnip::predictHelper(std::map<int, UniquePriceSeqs> &seqs, MatchMap &matches, int patType) {
    UniquePriceSeqs &seqForBase = seqs[basePrice];

    for (auto &priceSeq: seqForBase) { // iterate over all price sequences for in base price
        if (dataMatchesPriceSequence(priceSeq)) {
            matches[patType].emplace_back(priceSeq);
            std::cout << "Found a potential price sequence with pattern type: " << PATTERN_NAMES[patType] << std::endl;
            //  printPriceSequence(priceSeq); TODO: CHECk
        }
    }
}

OnePriceSeq Turnip::consolidateMatches(MatchMap &m, int *min, int *max) {
    OnePriceSeq merged(12, std::make_pair(SellPrice::MAX_SELL, SellPrice::MIN_SELL));

    for (int pType = 0; pType < 4; ++pType) {
        if (!m[pType].empty()) { // prediction includes this pattern type
            for (auto &seq: m[pType]) { // iterate through matched sequences of the pattern type
                for (int i = 0; i < seq.size(); ++i) {
                    // update min and max if necessary
                    if (seq[i].first < *min) {
                        *min = seq[i].first;
                    }
                    if (seq[i].second > *max) {
                        *max = seq[i].second;
                    }

                    // update merged
                    if (seq[i].first < merged[i].first &&
                        seq[i].second > merged[i].second) { // update min and max for half day i
                        merged[i] = std::make_pair(seq[i].first, seq[i].second);
                    } else if (seq[i].first < merged[i].first) { // update min for half day i
                        merged[i] = std::make_pair(seq[i].first, merged[i].second);
                    } else if (seq[i].second > merged[i].second) { // update max for half day i
                        merged[i] = std::make_pair(merged[i].first, seq[i].second);
                    }
                }
            }
        }
    }

    return merged;
}

void Turnip::graph(int islandNum, OnePriceSeq &consolidatedMatch, int yMin, int yMax) {
    std::cout << "Generating graph for consolidated pattern match(es)..." << std::endl;

    const std::string island = "Island " + std::to_string(islandNum);
    const std::string daisyBase = "Sunday Buy Price: " + std::to_string(basePrice);
    const std::string graphName = island + ".pdf";

    // data
    std::vector<int> mins, maxes;

    for (auto &pair: consolidatedMatch) {
        mins.emplace_back(pair.first);
        maxes.emplace_back(pair.second);
    }

    plt::figure_size(1600, 830); // pixel size width and height
    plt::suptitle(island, {{"size",   "x-large"},
                           {"weight", "demi"}});
    plt::title(daisyBase);
    plt::ylim(yMin - 1, yMax + 1);
    plt::plot(graphLabels, sellPrices, "oC7");
    plt::plot(graphLabels, mins, "or:");
    plt::plot(graphLabels, maxes, "og:");

    for (int i = 0; i < sellPrices.size(); ++i) {
        if (sellPrices[i] != INT_MIN) {
            plt::annotate(std::to_string(sellPrices[i]), i + 0.05, sellPrices[i] + 0.05);
        }
    }

    plt::save(graphName);

    std::cout << "Saved graph as: " << graphName << std::endl;
}

std::ostream &operator<<(std::ostream &out, Turnip *turnip) {
    std::string buyer = turnip->firstBuy ? "Yes" : "No";
    std::string previousWeek = turnip->prevPat != INT_MIN ? PATTERN_NAMES[turnip->prevPat] : "N/A";

    out << "======================" << std::endl;
    out << "Previous week's pattern: " << previousWeek << std::endl;
    out << "First time buyer? " << buyer << std::endl;
    out << "Base price: " << turnip->basePrice << std::endl;
    out << "======================" << std::endl;
    out << std::left << std::setw(5) << std::setfill(' ') << "";
    out << std::left << std::setw(5) << std::setfill(' ') << "AM";
    out << std::left << std::setw(5) << std::setfill(' ') << "PM" << std::endl;

    int day = 0;
    std::vector<int> prices = turnip->sellPrices;
    for (int p = 0; p < prices.size(); p += 2) {
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

bool Turnip::validateBasePrice(int p) {
    return (Turnip::MAX_BASE >= p && Turnip::MIN_BASE <= p) || p == INT_MIN;
}

bool Turnip::validatePrevPatType(int pat) {
    return (PATTERN_NAMES.size() > pat && 0 <= pat) || pat == INT_MIN;
}