//
// Created by Fatima Shaik on 12/3/22.
//
#include "carclient.h"
#include "motorcycleserver.h"
#include <iostream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "Auto_V.h"
#include "Dog.h"

using namespace jsonrpc;
using namespace std;

class finalMotorcycleServer : public motorcycleServer {
public:
    //header
    finalMotorcycleServer(AbstractServerConnector &connector, serverVersion_t type);
    virtual Json::Value alert(const std::string& action, const std::string& class_id, const std::string& object_id);
};
//constructor
finalMotorcycleServer:: finalMotorcycleServer(jsonrpc::AbstractServerConnector &connector, jsonrpc::serverVersion_t type) : motorcycleServer(connector, type) {
}
//functions
Json::Value finalMotorcycleServer::alert(const std::string& action, const std::string& class_id, const std::string& object_id){
    Json::Value result;
    result["status"] = "successful";
    return result;
}


int main()
{
    Auto_V Motorcyle_Right = Auto_V("right motorcycle");
    /*Dog SkyeTerrier = Dog("SkyTerrier");
    SkyeTerrier.setEndangered(true);
    SkyeTerrier.setDangerPoints();*/
    Json::Value myv;
    //int rm = SkyeTerrier.getDangerPoints(); //should be 35
    //Set up client to car server:
    int rm = 35;
    HttpClient righthttpclient("http://127.0.0.1:7374");
    carClient rightMotorcycle(righthttpclient, JSONRPC_CLIENT_V2);
    //Send number to car:
    try{
        myv = rightMotorcycle.sendData("send data", "motorcycle", rm, "rightmotorcycle");
    }
    catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    cout << myv.toStyledString() << endl;
    HttpServer httpserver(7376);
    cout << "Server started" << endl;
    finalMotorcycleServer motorcycleRightServer(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    motorcycleRightServer.StartListening();
    cout << "Hit enter to stop the server" << endl;
    getchar();
    motorcycleRightServer.StopListening();
    return 0;

}