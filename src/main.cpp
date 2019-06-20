/*
	Simple example using sendfile facility.
*/

#include <iostream>

#include "di.hpp"

#include "microsvc_controller.hpp"
#include "cache/redis_cache.hpp"

namespace di = boost::di;

//
// app_args_t
//

template<typename Server_Traits>
void run_server() {
//    di::bind<icache>().to<rediscache>();
//
//    auto *controller = di::make_injector().create<MicroserviceController *>();

    auto *controller = new MicroserviceController();

    restinio::run(
            restinio::on_thread_pool<Server_Traits>(40)
                    .port(8088)
                    .address("0.0.0.0")
                    .concurrent_accepts_count(40)
                    .request_handler(
                            [&](auto req) {
                                return controller->handle(req);
                            }));
}

int main(int argc, const char *argv[]) {
    try {
        run_server<restinio::default_traits_t>();
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
