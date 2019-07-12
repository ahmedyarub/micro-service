#ifndef PROJECT_MAP_CACHE_HPP
#define PROJECT_MAP_CACHE_HPP


#include "../models/currency.hpp"
#include "icache.hpp"
#include <map>

class mapcache : icache {
private:
    map<string, Currency *> cache;

public:
    void add(Currency *currency);

    Currency *get(const string &currency);
};


#endif //PROJECT_MAP_CACHE_HPP
