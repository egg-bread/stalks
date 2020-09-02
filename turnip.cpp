#include "turnip.h"
#include "turnipexception.h"

namespace plt = matplotlibcpp;


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

void Turnip::predict(AllPrices *a) {
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
        std::cout << "Found " << matches.size() << " potential price sequences!" << std::endl;
        graph();
    }
}

void Turnip::predictHelper(std::map<int, UniquePriceSeqs> &seqs, MatchMap &matches, int patType) {
    UniquePriceSeqs &seqForBase = seqs[basePrice];

    for (auto &priceSeq: seqForBase) { // iterate over all price sequences for in base price
        if (dataMatchesPriceSequence(priceSeq)) {
            matches[priceSeq] = patType;
            std::cout << "Found a potential price sequence with pattern type: " << PATTERN_NAMES[patType] << std::endl;
          //  printPriceSequence(priceSeq);
        }
    }
}

void Turnip::graph() {
    std::cout << "Generating graph for pattern match(es)..." << std::endl;
    // TODO: matplotlib
    // display percentages of matched pattern type(s) on graph text area if not first buy (otherwise it's 100% small profit pattern)
    std::cout << "Completed prediction for current island." << std::endl << std::endl;
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