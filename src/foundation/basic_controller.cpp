#include "basic_controller.hpp"
#include "network_utils.hpp"

namespace cfx {
    BasicController::BasicController() {

    }

    BasicController::~BasicController() {

    }

    void BasicController::setEndpoint(const utility::string_t &value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == U("host_auto_ip4")) {
            endpointBuilder.set_host(NetworkUtils::hostIP4());
            //endpointBuilder.set_host(U("127.0.0.1"));
        }
//        else if (endpointURI.host() == U("host_auto_ip6")) {
//            endpointBuilder.set_host(NetworkUtils::hostIP6());
//        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri());
    }

    utility::string_t BasicController::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> BasicController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> BasicController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> BasicController::requestPath(const http_request &message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);
    }
}