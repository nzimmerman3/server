#ifndef SERVER_STATUS_H
#define SERVER_STATUS_H

#include <map>
#include <vector>
#include <mutex>
#include "../libraries/boost-http/include/response.hpp"
#include "../libraries/boost-http/include/request.hpp"

class server_status_singleton
{
    public:
        static server_status_singleton* getInstance();
        void addHandlerConfig(std::string handlerType, std::string URIPrefix);
        void logReqResp(const http::server::request &req, const http::server::response &resp);
        std::map<std::string, std::vector<std::string>>* getHandlerConfigs();
        std::map<http::server::response::status_type, int>* getRespStatusCounters();
        std::map<std::string, std::map<http::server::response::status_type, int>>* getReqStatuses();

    private:
        server_status_singleton();
        static server_status_singleton *instance;
        std::map<std::string, std::vector<std::string>> handlerConfigs;
        std::map<http::server::response::status_type, int> resp_status_counters;
        std::map<std::string, std::map<http::server::response::status_type, int>> req_statuses;
        std::mutex counters_lock;
};

#endif // SERVER_STATUS_H