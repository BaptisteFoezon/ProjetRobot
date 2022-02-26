/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#include <stdio.h>

#include "robot.h"
#include "../../infox_prose-x86_64-v0.3/include/infox/prose/prose.h"

#define LEFT_MOTOR MD
#define RIGHT_MOTOR MA
#define LIGHT_SENSOR S1
#define FRONT_BUMPER S3
#define FLOOR_SENSOR S2

static Robot robot;

// start simulateur
void Robot_start()
{
    printf("Initialisation connection simulateur\n");
    ProSE_Intox_init("0.0.0.0", 12345);
    robot.mD = Motor_open(MD);
    robot.mG = Motor_open(MA);
    if (robot.mD == NULL)
        PProseError("Probleme initialisation moteur droit");
    if (robot.mG == NULL)
        PProseError("Probleme initialisation moteur gauche");

    robot.lightSensor = LightSensor_open(LIGHT_SENSOR);
    if (robot.lightSensor == NULL)
        PProseError("Probleme initialisation light sensor ");

    robot.frontSensor = ContactSensor_open(FRONT_BUMPER);
    if (robot.frontSensor == NULL)
        PProseError("Probleme initialisation front sensor ");

    robot.floorSensor = ContactSensor_open(FLOOR_SENSOR);
    if (robot.floorSensor == NULL)
        PProseError("Probleme initialisation floor sensor ");
}

void Robot_stop()
{
    printf("stop Robot simulateur \n");
    ProSE_Intox_close();
}

extern void Robot_new()
{
}
extern void Robot_free()
{
    Motor_close(robot.mD);
    Motor_close(robot.mG);
    ContactSensor_close(robot.frontSensor);
}

extern int Robot_getRobotSpeed()
{
    int vd = Motor_getCmd(robot.mD);
    int vg = Motor_getCmd(robot.mG);
    int speed = (vd + vg) / 2;
    return speed;
}

extern SensorState Robot_getSensorState()
{
    robot.sensorState.collision = (ContactSensor_getStatus(robot.frontSensor) || ContactSensor_getStatus(robot.floorSensor));
    robot.sensorState.luminosity = LightSensor_getStatus(robot.lightSensor);
    return robot.sensorState;
}

extern void Robot_setWheelsVelocity(int mr, int ml)
{
    printf("md: %i   mg: %i \n", mr ,ml);
    Motor_setCmd(robot.mD, mr);
    Motor_setCmd(robot.mG, ml);
}