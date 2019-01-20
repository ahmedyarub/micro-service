#include <cpprest/details/basic_types.h>
#include <cpprest/asyncrt_utils.h>
#include <boost/lexical_cast.hpp>
#include "../models/currency.hpp"
#include "redis_cache.hpp"

rediscache::rediscache() {
    client.connect("127.0.0.1", 6379,
                   [](const std::string &host, std::size_t port, cpp_redis::client::connect_state status) {
                       if (status == cpp_redis::client::connect_state::dropped) {
                           std::cout << "client disconnected from " << host << ":" << port << std::endl;
                       }
                   });
}

void rediscache::add(Currency *currency) {
    client.set(utility::conversions::to_utf8string(currency->currency), boost::lexical_cast<string>(currency->value));
}

Currency *rediscache::get(const utility::string_t &currency) {
    double value;

    client.get(utility::conversions::to_utf8string(currency), [value](cpp_redis::reply &reply) mutable {
        value = boost::lexical_cast<double>(reply.as_string());
    });

    return new Currency(currency, value);
}
