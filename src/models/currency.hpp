#ifndef CURRENCY
#define CURRENCY

#include <utility>

using namespace std;

class Currency {
public:
    utility::string_t currency{};
    double value;

    Currency() = default;

    Currency(utility::string_t cur, double val) : currency{std::move(cur)}, value{val} {}
};


#endif