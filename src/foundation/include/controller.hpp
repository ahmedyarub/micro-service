#pragma once

#include <restinio/all.hpp>

#include <fmt/format.h>
#include <clara.hpp>

namespace cfx {
    class Controller {
    public:
        virtual restinio::request_handling_status_t handle(restinio::request_handle_t req) = 0;
    };
}