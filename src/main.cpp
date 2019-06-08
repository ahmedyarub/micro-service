/*
	Simple example using sendfile facility.
*/

#include <iostream>

#include <restinio/all.hpp>

#include <fmt/format.h>
#include <clara.hpp>

#include "di.hpp"

#include "cache/redis_cache.hpp"

//
// app_args_t
//

template<typename Server_Traits>
void run_server() {
    restinio::run(
            restinio::on_thread_pool<Server_Traits>(40)
                    .port(8088)
                    .address("0.0.0.0")
                    .concurrent_accepts_count(40)
                    .request_handler(
                            [&](auto req) {
                                cout << "Handler" << std::endl;

                                if (restinio::http_method_get() == req->header().method()) {
                                    cout << "GET" << std::endl;
                                    if (req->header().path() == "/convert") {

                                    } else {
                                        try {
                                            cout << "Loading file" << req->header().path() << std::endl;

                                            auto sf = restinio::sendfile(req->header().path());

                                            return
                                                    req->create_response()
                                                            .append_header(
                                                                    restinio::http_field::content_type,
                                                                    "text/html; charset=utf-8")
                                                            .set_body(std::move(sf))
                                                            .done();
                                        }
                                        catch (const std::exception &) {
                                            return
                                                    req->create_response(
                                                                    restinio::status_not_found())
                                                            .connection_close()
                                                            .append_header_date_field()
                                                            .done();
                                        }
                                    }
                                }

                                return restinio::request_rejected();
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
