/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer

#include <stdlib.h>
#include <stdio.h>
#include "robot.h"
#include "pilot.h"


static PilotState state;
static Pilot pilot;
static e_state etatPilot;


typedef enum
{
    SETVEL,
    CHECK,
    STOP,
} e_event;

/* prototype privee 
*/
static void Pilot_run(e_event event, VelocityVector VelocityVector);
static bool_e Pilot_hasBumped();

void Pilot_start()
{
    Robot_start();
}

void Pilot_stop()
{
    printf("fct Pilot stop");
    VelocityVector vel = {NO, 0};
    Pilot_run(STOP, vel);
}

void Pilot_new()
{
    Robot_new();
}

void Pilot_free()
{
    Robot_free();
}


void Pilot_setVelocity(VelocityVector vel){
    Pilot_run(SETVEL, vel);
};

void Pilot_sendMvt(VelocityVector vel)
{
    switch (vel.dir)
    {
    case FORWARD:
        printf("pilot send mvt FORAWRD \n");
        printf("Vel: %i\n",vel.power);
        Robot_setWheelsVelocity(vel.power, vel.power);
        break;
    case BACKWARD:
        printf("pilot send mvt BACKWARD \n");
        Robot_setWheelsVelocity(-vel.power, -vel.power);
        break;
    case LEFT:
        printf("pilot send mvt LEFT \n");
        Robot_setWheelsVelocity(vel.power, -vel.power);
        break;
    case RIGHT:
        printf("pilot send mvt RIGHT \n");
        Robot_setWheelsVelocity(-vel.power, vel.power);
        break;
    case NO:
        printf("pilot send mvt NO \n");
        Robot_setWheelsVelocity(0, 0);
        break;
    default:
        break;
    }
}

PilotState Pilot_getState()
{
    pilot.pilot_state.speed = Robot_getRobotSpeed();
    pilot.pilot_state.collision = Robot_getSensorState().collision;
    pilot.pilot_state.luminosity = Robot_getSensorState().luminosity;
    return pilot.pilot_state;
}

void Pilot_check()
{
    VelocityVector vel;
    Pilot_run(CHECK, vel);
}

static bool_e Pilot_hasBumped()
{
    SensorState sensorState = Robot_getSensorState();

    return sensorState.collision == BUMPED;
}

void Pilot_run(e_event event, VelocityVector vel)
{
    switch (event)
    {
    case SETVEL:
        if (etatPilot ==RUNNING || etatPilot == IDLE)
        {
            if (vel.dir != NO)
            {
                etatPilot = RUNNING;
                Pilot_sendMvt(vel);
            }
            else
                Pilot_sendMvt(vel);
                etatPilot = IDLE;  
        }
        break;
    case CHECK:
        if (etatPilot == RUNNING )
        {
            Pilot_getState();
            state = Pilot_getState();
            printf("Etat du robot :\n");
            printf("    Vitesse: %d\n", state.speed);
            printf("    Collision: %d\n", state.collision);
            etatPilot = RUNNING;
          
        }
    case STOP:
        vel.dir = STOP;
        vel.power = 0;
        Pilot_sendMvt(vel);
        break;
        
    
    default:
        break;
    }
}
