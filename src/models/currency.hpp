#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>

using namespace std;

class Currency {
public:
    string currency{};
    double value{};

    Currency() = default;

    Currency(string cur, double val) : currency{std::move(cur)}, value{val} {}
};


#endif