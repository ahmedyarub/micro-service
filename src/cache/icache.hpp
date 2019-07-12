#ifndef PROJECT_ICACHE_HPP
#define PROJECT_ICACHE_HPP


#include "../models/currency.hpp"
#include <map>

class icache {
private:
    map<string, Currency *> cache;

public:
    virtual void add(Currency *currency) {
        cache[currency->currency] = currency;
    }

    virtual Currency *get(const string &currency) {
        return cache[currency];
    }
};


#endif //PROJECT_ICACHE_HPP
