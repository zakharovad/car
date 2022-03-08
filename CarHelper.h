//
// Created by Artem on 31.01.2022.
//

#ifndef ORANGECOMPILETEST_CARBUILDER_H
#define ORANGECOMPILETEST_CARBUILDER_H
#include "./models/DriveModel.h"



class CarHelper {

public:

    CarHelper();
    void updateDriveStructure(DriveModel *driveModel, JsonObject &object);
    void drivingLoop(DriveModel *driveModel);
};


#endif //ORANGECOMPILETEST_CARBUILDER_H
