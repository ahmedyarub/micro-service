#pragma once

#include <cpprest/details/basic_types.h>
#include "std_micro_service.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace cfx {

    using HostInetInfo = tcp::resolver::iterator;

    class NetworkUtils {
    private:
        static HostInetInfo queryHostInetInfo();

        static utility::string_t hostIP(unsigned short family);

    public:
        // gets the host IP4 string formatted
        static utility::string_t hostIP4() {
            return hostIP(AF_INET);
        }
    };

}
