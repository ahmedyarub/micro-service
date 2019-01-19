#pragma once

#include <basic_controller.hpp>
#include "models/currency.hpp"

using namespace cfx;

class MicroserviceController : public BasicController, Controller {
private:
    map<utility::string_t, Currency *> cache;

public:
    MicroserviceController(map<utility::string_t, Currency *> cache) : cache{cache} {}

    ~MicroserviceController() {}

    void handleGet(http_request request) override;

    void initRestOpHandlers() override;
};