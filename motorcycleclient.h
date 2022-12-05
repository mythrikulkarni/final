/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_MOTORCYCLECLIENT_H_
#define JSONRPC_CPP_STUB_MOTORCYCLECLIENT_H_

#include <jsonrpccpp/client.h>

class motorcycleClient : public jsonrpc::Client
{
    public:
        motorcycleClient(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        Json::Value alert(const std::string& action, const std::string& class_id, const std::string& object_id) 
        {
            Json::Value p;
            p["action"] = action;
            p["class_id"] = class_id;
            p["object_id"] = object_id;
            Json::Value result = this->CallMethod("alert",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_MOTORCYCLECLIENT_H_
