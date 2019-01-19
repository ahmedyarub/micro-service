
#include <iostream>

#include <usr_interrupt_handler.hpp>

#include "microsvc_controller.hpp"
#include "soci/boost-tuple.h"

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

using namespace web;
using namespace cfx;

int main(int argc, const char *argv[]) {
    InterruptHandler::hookSIGINT();

    soci::session sql(*soci::factory_sqlite3(), "/tmp/microservice.db");

    map<utility::string_t, Currency *> cache;

    soci::rowset<soci::row> rowset = (sql.prepare << "SELECT currency, value FROM Currency");

    cache[_XPLATSTR("USD")] = new Currency(_XPLATSTR("USD"), 1);

    for (auto &r : rowset) {
        cache[utility::conversions::to_string_t(r.get<utility::string_t>(0))] =
                new Currency(utility::conversions::to_string_t(r.get<utility::string_t>(0)),
                             r.get<double>(0));
    }

    MicroserviceController *server = new MicroserviceController(cache);
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
