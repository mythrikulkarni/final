//
// Created by Fatima Shaik on 12/3/22.
//
#include "motorcycleclient.h"
#include "carserver.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace jsonrpc;
using namespace std;

class finalCarServer : public carServer {
public:
    int left;
    int right;
    //header
    finalCarServer(AbstractServerConnector &connector, serverVersion_t type);
    Json::Value sendData(const std::string& action, const std::string& class_id, const int number, const std::string& object_id);
};
//constructor
finalCarServer::finalCarServer(jsonrpc::AbstractServerConnector &connector, jsonrpc::serverVersion_t type) : carServer(connector, type) {

}

//functions
Json::Value finalCarServer::sendData(const std::string& action, const std::string& class_id, const int number, const std::string& object_id) {
    Json::Value result;
    if (object_id == "leftmotorcycle"){
        left = number;
        result["status"] = "successful";
        //result["number"] = left;
    }
    else if (object_id == "rightmotorcycle"){
        right = number;
        result["status"] = "successful";
        //result["number"] = right;
    }
    else{
        result["status"] = "failed";
    }
    return result;
}

int main(){
    //Starting the car server
    Json::Value myv;
    HttpServer httpserver(7374);
    finalCarServer car(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    car.StartListening();
    cout << "Hit enter to stop the server" << endl;
    HttpClient carhttpclientleft("http://127.0.0.1:7375");
    motorcycleClient middleCarleft (carhttpclientleft, JSONRPC_CLIENT_V2);
    HttpClient carhttpclientright("http://127.0.0.1:7376");
    motorcycleClient middleCarright (carhttpclientright, JSONRPC_CLIENT_V2);
    getchar();
    car.StopListening();
    if( car.left > car.right){
        try{
            myv = middleCarleft.alert("alert", "car", "middleCar");
            cout << myv.toStyledString() << endl;
        }
        catch (JsonRpcException &e) {
            cerr << e.what() << endl;
        }
        cout<< "left motorcycle is hit" <<endl;
    }
    else{
        try{
            myv = middleCarright.alert("alert", "car", "middleCar");
            cout << myv.toStyledString() << endl;
        }
        catch (JsonRpcException &e) {
            cerr << e.what() << endl;
        }
        cout<< "right is hit" <<endl;
    }
    return 0;
}


