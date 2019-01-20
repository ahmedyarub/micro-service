#include <iostream>

#include <usr_interrupt_handler.hpp>
#include "di.hpp"

#include "microsvc_controller.hpp"
#include "cache/map_cache.hpp"

using namespace web;
using namespace cfx;

namespace di = boost::di;

int main(int argc, const char *argv[]) {
    InterruptHandler::hookSIGINT();

    di::bind<icache>().to<mapcache>();

    auto *server = di::make_injector().create<MicroserviceController *>();
    server->setEndpoint(_XPLATSTR("http://host_auto_ip4:6502/v1/service/api"));

    try {
        server->accept().wait();
        std::cout << "Listening on: " << utility::conversions::to_utf8string(server->endpoint()) << '\n';

        InterruptHandler::waitForUserInterrupt();

        server->shutdown().wait();
    }
    catch (std::exception &e) {
        std::cerr << "Initialization error: " << '\n';
        std::cerr << e.what();
    }
    catch (...) {
        //RuntimeUtils::printStackTrace();
    }

    return 0;
}
