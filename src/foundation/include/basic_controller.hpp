#pragma once

#include "controller.hpp"

namespace cfx {
    class BasicController {
    protected:
//        http_listener _listener; // main micro service network endpoint

    public:
        BasicController();

        ~BasicController();

//        void setEndpoint(const utility::string_t &value);
//
//        utility::string_t endpoint() const;

//        std::vector<utility::string_t> requestPath(const http_request &message);
    };
}