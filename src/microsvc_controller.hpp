#pragma once

#include <basic_controller.hpp>
#include "models/currency.hpp"
#include "cache/icache.hpp"

using namespace cfx;

class MicroserviceController : public BasicController, Controller {
private:
    icache *cache;

public:
    explicit MicroserviceController(icache *cache);

    ~MicroserviceController() = default;

    restinio::request_handling_status_t handle(restinio::request_handle_t req) override;
};