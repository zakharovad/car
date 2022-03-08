//
// Created by Artem on 30.01.2022.
//

#ifndef ORANGECOMPILETEST_DRIVEMODEL_H
#define ORANGECOMPILETEST_DRIVEMODEL_H
#include "BaseModel.h"
#include ".././third-party/ArduinoJson/src/ArduinoJson.h"
struct DriveModel :  BaseModel {
public:
    int speed = 0;
    int direction = 0;
    std::string type = "DriveModel";
    std::string toJsonString(){
        StaticJsonDocument<200> doc;
        JsonObject root = doc.to<JsonObject>();
        root["type"] = type;
        root["direction"] = direction;
        root["speed"] = speed;
        std::string output;
        serializeJson(root,output);
        return output;
    };
};
#endif //ORANGECOMPILETEST_DRIVEMODEL_H
