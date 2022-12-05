//
// Created by Fatima Shaik on 12/3/22.
//
#include "carclient.h"
#include "motorcycleserver.h"
#include <iostream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "Auto_V.h"
#include "Person.h"

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
    Auto_V Left_Motorcycle = Auto_V("left motorcycle");
    /*Person Biker = Person("Biker");
    Biker.setPassengerAge(55);
    Biker.setDangerPoints();*/
    //int lm = Biker.getDangerPoints();
    //should be 50
    Json::Value myv;
    int lm = 50;
    //Set up client to car server:
    HttpClient lefthttpclient("http://127.0.0.1:7374");
    carClient leftMotorcycle(lefthttpclient, JSONRPC_CLIENT_V2);
    //Send number to car:
    try{
        myv = leftMotorcycle.sendData("send data", "motorcycle", lm, "leftmotorcycle");
    }
    catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    cout << myv.toStyledString() << endl;
    //TODO: Set up server of lm to car:
    HttpServer httpserver(7375);
    cout << "Server started" << endl;
    finalMotorcycleServer motorcycleLeftServer(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    motorcycleLeftServer.StartListening();
    cout << "Hit enter to stop the server" << endl;
    getchar();
    motorcycleLeftServer.StopListening();
    return 0;

}