#include "network_utils.hpp"
#include "cpprest/asyncrt_utils.h"

namespace cfx {

    HostInetInfo NetworkUtils::queryHostInetInfo() {
        io_service ios;
        tcp::resolver resolver(ios);
        tcp::resolver::query query(host_name(), "");
        return resolver.resolve(query);
    }

    utility::string_t NetworkUtils::hostIP(unsigned short family) {
        auto hostInetInfo = queryHostInetInfo();
        tcp::resolver::iterator end;
        while (hostInetInfo != end) {
            tcp::endpoint ep = *hostInetInfo++;
            sockaddr sa = *ep.data();
            if (sa.sa_family == family) {
                return utility::conversions::to_string_t(ep.address().to_string());
            }
        }
        return nullptr;
    }

}