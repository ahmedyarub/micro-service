#ifndef PROJECT_MAP_CACHE_HPP
#define PROJECT_MAP_CACHE_HPP


#include <cpprest/details/basic_types.h>
#include "../models/currency.hpp"
#include "icache.hpp"
#include <map>

class mapcache : icache {
private:
    map<utility::string_t, Currency *> cache;

public:
    void add(Currency *currency);

    Currency *get(const utility::string_t &currency);
};


#endif //PROJECT_MAP_CACHE_HPP
