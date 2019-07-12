#include "../models/currency.hpp"
#include <map>
#include "map_cache.hpp"

void mapcache::add(Currency *currency) {
    cache[currency->currency] = currency;
}

Currency *mapcache::get(const utility::string_t &currency) {
    return cache[currency];
}
