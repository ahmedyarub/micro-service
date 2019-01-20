#pragma once

#include <basic_controller.hpp>
#include "models/currency.hpp"
#include "cache/icache.hpp"

using namespace cfx;

class MicroserviceController : public BasicController, Controller {
private:
    icache *cache;

public:
    MicroserviceController(icache *cache);

    ~MicroserviceController() = default;

    void handleGet(http_request request) override;

    void initRestOpHandlers() override;
};