#include "../include/server_status_singleton.h"

server_status_singleton* server_status_singleton::instance = NULL;

server_status_singleton::server_status_singleton()
{

}

server_status_singleton* server_status_singleton::getInstance()
{
    if (!instance)
    {
        instance = new server_status_singleton();
    }

    return instance;
}

void server_status_singleton::addHandlerConfig(std::string handlerType, std::string URIPrefix)
{
    handlerConfigs[handlerType].push_back(URIPrefix);
}

void server_status_singleton::logReqResp(const http::server::request &req, const http::server::response &resp)
{
    counters_lock.lock();
    if (req_statuses[req.uri_].find(resp.code_) != req_statuses[req.uri_].end())
    {
        req_statuses[req.uri_][resp.code_] += 1;
    }
    else
    {
        req_statuses[req.uri_][resp.code_] = 1;
    }

    if (resp_status_counters.find(resp.code_) != resp_status_counters.end())
    {
        resp_status_counters[resp.code_] += 1;
    }
    else
    {
        resp_status_counters[resp.code_] = 1;
    }
    counters_lock.unlock();
}

std::map<std::string, std::vector<std::string>>* server_status_singleton::getHandlerConfigs()
{
    return &handlerConfigs;
}

std::map<http::server::response::status_type, int>* server_status_singleton::getRespStatusCounters()
{
    return &resp_status_counters;
}

std::map<std::string, std::map<http::server::response::status_type, int>>* server_status_singleton::getReqStatuses()
{
    return &req_statuses;
}