//
// Created by Artem on 31.01.2022.
//

#include "CarHelper.h"
#include <wiringPi.h>
#include <softPwm.h>
#define ENA_PIN 1 //for driver ena
#define IN1_PIN 4 //for driver in1
#define IN2_PIN 5 //for driver in1

//right motors
#define ENB_PIN 25 //for driver enb
#define IN3_PIN 22 //for driver in2
#define IN4_PIN 23 //for driver in2

//for driver  deceleration ratio
#define SPEED_COEF 3
const unsigned int  moveForward = 1; //0001;
const unsigned int  moveBack = 2;//0010;
const unsigned int  moveLeft = 4;//0100;
const unsigned int  moveRight = 8;//1000;
const unsigned int  moveStop = 0;//0000;
CarHelper::CarHelper() {

    wiringPiSetup();
    //pinMode (ENA_PIN, OUTPUT);
    softPwmCreate(ENA_PIN, 0, 255);
    pinMode (IN1_PIN, OUTPUT);
    pinMode (IN2_PIN, OUTPUT);
    //pinMode (ENB_PIN, OUTPUT);
    softPwmCreate(ENB_PIN, 0, 255);
    pinMode (IN3_PIN, OUTPUT);
    pinMode (IN4_PIN, OUTPUT);

    //pinMode (1, OUTPUT);
    //pinMode (4, OUTPUT);
    //pinMode (5, OUTPUT);
    //pinMode (11, OUTPUT);
    //pinMode (12, OUTPUT);
    //pinMode (21, OUTPUT);
    //pinMode (22, OUTPUT);
    //pinMode (23, OUTPUT);
    //pinMode (24, OUTPUT);
    //pinMode (25, OUTPUT);
    //digitalWrite (1, LOW);
    //digitalWrite (4, HIGH);
    //digitalWrite (5, HIGH);
    //digitalWrite (11, HIGH);
    //digitalWrite (12, HIGH);
    //digitalWrite (21, HIGH);
    //digitalWrite (22, HIGH);
    //digitalWrite (23, HIGH);
    //digitalWrite (24, HIGH);
    //digitalWrite (25, HIGH);
}
void CarHelper::updateDriveStructure(DriveModel *driveModel, JsonObject &object){
    JsonVariant speed = object.getMember("speed");
    JsonVariant direction = object.getMember("direction");
    driveModel->speed = speed.as<int>();
    driveModel->direction = direction.as<int>();

}
void CarHelper::drivingLoop(DriveModel *driveModel){
    switch(driveModel->direction){
        case moveStop:
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, LOW);
            digitalWrite(IN3_PIN, LOW);
            digitalWrite(IN4_PIN, LOW);
            softPwmWrite(ENA_PIN, driveModel->speed);
            softPwmWrite(ENB_PIN, driveModel->speed);
            break;
        case moveForward:
            std::cout << "json: " + driveModel->toJsonString() << std::endl;
            softPwmWrite(ENA_PIN, driveModel->speed);
            digitalWrite(IN1_PIN, HIGH);
            digitalWrite(IN2_PIN, LOW);
            softPwmWrite(ENB_PIN, driveModel->speed);
            digitalWrite(IN3_PIN, HIGH);
            digitalWrite(IN4_PIN, LOW);
            break;
        case moveBack:
            softPwmWrite(ENA_PIN, driveModel->speed);
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, HIGH);
            softPwmWrite(ENB_PIN, driveModel->speed);
            digitalWrite(IN3_PIN, LOW);
            digitalWrite(IN4_PIN, HIGH);
            break;
        case moveRight:
            softPwmWrite(ENA_PIN, driveModel->speed);
            softPwmWrite(ENB_PIN, 0);
            digitalWrite(IN1_PIN, HIGH);
            digitalWrite(IN2_PIN, LOW);
            digitalWrite(IN3_PIN, LOW);
            digitalWrite(IN4_PIN, LOW);
            break;
        case moveLeft:
            softPwmWrite(ENB_PIN, driveModel->speed);
            softPwmWrite(ENA_PIN, 0);
            digitalWrite(IN3_PIN, HIGH);
            digitalWrite(IN4_PIN, LOW);
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, LOW);
            break;
        case (moveForward | moveLeft):
            softPwmWrite(ENA_PIN, driveModel->speed/SPEED_COEF);
            digitalWrite(IN1_PIN, HIGH);
            digitalWrite(IN2_PIN, LOW);
            softPwmWrite(ENB_PIN, driveModel->speed);
            digitalWrite(IN3_PIN, HIGH);
            digitalWrite(IN4_PIN, LOW);
            break;
        case (moveForward | moveRight):
            softPwmWrite(ENA_PIN, driveModel->speed);
            digitalWrite(IN1_PIN, HIGH);
            digitalWrite(IN2_PIN, LOW);
            softPwmWrite(ENB_PIN, driveModel->speed/SPEED_COEF);
            digitalWrite(IN3_PIN, HIGH);
            digitalWrite(IN4_PIN, LOW);
            break;
        case (moveBack | moveLeft):
            softPwmWrite(ENA_PIN, driveModel->speed/SPEED_COEF);
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, HIGH);
            softPwmWrite(ENB_PIN, driveModel->speed);
            digitalWrite(IN3_PIN, LOW);
            digitalWrite(IN4_PIN, HIGH);
            break;
        case (moveBack | moveRight):
            softPwmWrite(ENA_PIN, driveModel->speed);
            digitalWrite(IN1_PIN, LOW);
            digitalWrite(IN2_PIN, HIGH);
            softPwmWrite(ENB_PIN, driveModel->speed/SPEED_COEF);
            digitalWrite(IN3_PIN, LOW);
            digitalWrite(IN4_PIN, HIGH);
            break;

    }

}

