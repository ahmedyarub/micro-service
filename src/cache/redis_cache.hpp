#ifndef PROJECT_REDIS_CACHE_HPP
#define PROJECT_REDIS_CACHE_HPP

#include "../models/currency.hpp"
#include "icache.hpp"
#include <cpp_redis/cpp_redis>

class rediscache : icache {
private:
    cpp_redis::client client;
public:
    rediscache();

    void add(Currency *currency) override;

    Currency *get(const string &currency) override;
};


#endif //PROJECT_REDIS_CACHE_HPP
