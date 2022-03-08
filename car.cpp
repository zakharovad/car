#include <iostream>
#include <wiringPi.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <ArduinoJson.h>
#include <CarHelper.h>
#include <CarHelper.cpp>
#include <thread>
#include <chrono>
typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;
CarHelper carHelper;
//models
DriveModel driveModel;
DriveModel *pDriveModel  = &driveModel;
// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    StaticJsonDocument<1536> doc;
    DeserializationError error = deserializeJson(doc, msg->get_payload());
    if (error) {
        std::string message = error.c_str();
        s->send(hdl, "json error: " +  message, msg->get_opcode());
        std::cout << " json error: " << error.c_str()
                  << std::endl;
        return;
    }
    JsonObject root = doc.as<JsonObject>();
    JsonVariant type = root.getMember("type");
    if(type.as<std::string>() == pDriveModel->type){
        carHelper.updateDriveStructure(pDriveModel, root);
    }

    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: " << "(" << e.what() << ")" << std::endl;
    }
}
void update(){
    while (1){
        carHelper.drivingLoop(pDriveModel);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}
void loop(){
    std::thread tr(update);
    tr.detach();
}
int main() {
    try {

        server echo_server;
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(9002);
        // Start the server accept loop
        echo_server.start_accept();
        loop();
        // Start the ASIO io_service run loop
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
    return 0;
}
