#ifndef PROJECT_ICACHE_HPP
#define PROJECT_ICACHE_HPP


#include <cpprest/details/basic_types.h>
#include "../models/currency.hpp"
#include <map>

class icache {
private:
    map<utility::string_t, Currency *> cache;

public:
    virtual void add(Currency *currency) {
        cache[currency->currency] = currency;
    }

    virtual Currency *get(const utility::string_t &currency) {
        return cache[currency];
    }
};


#endif //PROJECT_ICACHE_HPP
