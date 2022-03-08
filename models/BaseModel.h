//
// Created by Artem on 30.01.2022.
//

#ifndef ORANGECOMPILETEST_BASEMODEL_H
#define ORANGECOMPILETEST_BASEMODEL_H
#include <string>
struct BaseModel {
    std::string type = "";
    virtual std::string toJsonString() = 0;
};
#endif //ORANGECOMPILETEST_BASEMODEL_H
