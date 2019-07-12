#include <std_micro_service.hpp>
#include "microsvc_controller.hpp"

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <boost/lexical_cast.hpp>

MicroserviceController::MicroserviceController(icache *cache) {
#ifdef _WIN32
    soci::session sql(*soci::factory_sqlite3(), "d:/tmp/microservice.db");
#else
    soci::session sql(*soci::factory_sqlite3(), "/tmp/microservice.db");
#endif

    soci::rowset<soci::row> rowset = (sql.prepare << "SELECT currency, value FROM Currency");

    cache->add(new Currency("USD", 1));

    for (auto &r : rowset) {
        cache->add(new Currency(r.get<std::string>(0),
                                r.get<double>(1)));
    }

    this->cache = cache;
}

restinio::request_handling_status_t MicroserviceController::handle(restinio::request_handle_t req) {
    cout << "Handler" << std::endl;

    if (restinio::http_method_get() == req->header().method()) {
        if (req->header().path() == "/convert") {
            Currency cur;

            const auto query_parameters = restinio::parse_query(req->header().query());

            rapidjson::StringBuffer response;
            rapidjson::Writer<rapidjson::StringBuffer> writer(response);
            writer.StartObject();

            auto from_currency = cache->get(
                    std::string{query_parameters["from"].data(), query_parameters["from"].size()});
            auto to_currency = cache->get(std::string{query_parameters["to"].data(), query_parameters["to"].size()});
            auto amount = boost::lexical_cast<double>(query_parameters["amount"]);

            if (from_currency == nullptr || to_currency == nullptr) {
                return req->create_response(restinio::status_not_found())
                        .connection_close()
                        .append_header_date_field()
                        .done();
            }

            writer.Key("result");
            writer.Double(from_currency->value / to_currency->value * amount);

            writer.EndObject();

            return req->create_response()
                    .append_header(restinio::http_field::content_type, "text/html; charset=utf-8")
                    .set_body(response.GetString())
                    .done();
        } else {
            try {
                restinio::string_view_t filename = req->header().path().substr(1, req->header().path().size() - 1);

                cout << "Loading file " << filename << std::endl;

                auto sf = restinio::sendfile(filename);

                return req->create_response()
                        .append_header(restinio::http_field::content_type, "text/html; charset=utf-8")
                        .set_body(std::move(sf))
                        .done();
            }
            catch (const std::exception &) {
                return req->create_response(restinio::status_not_found())
                        .connection_close()
                        .append_header_date_field()
                        .done();
            }
        }
    }

    return restinio::request_rejected();
}

/*
void MicroserviceController::handle(http_request request) {
    auto path = requestPath(request);
    if (!path.empty()) {
        if (path[0] == _XPLATSTR("convert")) {
            Currency cur;


            auto query_parameters = uri::split_query(request.request_uri().query());

            auto response = json::value::object();
            auto from_currency = cache->get(query_parameters[_XPLATSTR("from")]);
            auto to_currency = cache->get(query_parameters[_XPLATSTR("to")]);
            auto amount = boost::lexical_cast<double>(query_parameters[_XPLATSTR("amount")]);

            if (from_currency == nullptr || to_currency == nullptr) {
                request.reply(status_codes::NotFound);
                return;
            }

            response[_XPLATSTR("result")] = json::value::number(from_currency->value / to_currency->value * amount);

            request.reply(status_codes::OK, response);
        } else {
            try {
                file_stream<uint8_t>::open_istream(_XPLATSTR("/home/osboxes/Documents/asmttpd/web_root/" + path[0]))
                        .then([=](Concurrency::streams::istream inFile) -> pplx::task<void> {
                            return request.reply(status_codes::OK, inFile.streambuf(),
                                                 _XPLATSTR("text/html; charset=utf-8")).then(
                                    [=]() {
                                        return inFile.close();
                                    });
                        }).get();
            }
            catch (...) {
                request.reply(status_codes::NotFound);
            }
        }
    } else {
        request.reply(status_codes::NotFound);
    }
}
 */