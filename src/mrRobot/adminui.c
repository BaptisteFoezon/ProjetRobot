/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "adminui.h"
#include "pilot.h"

typedef struct admin_s
{
	char choice;
} Admin;

static bool quiter = false;

// prototype

static void AdminUI_display();
static void AdminUI_captureChoice();
static void AdminUI_run();

void AdminUI_start()
{
	printf("Admin start\n");
	Pilot_start();
	AdminUI_run();
}

void AdminUI_stop()
{
	Pilot_stop();
}

void AdminUI_new()
{
	Pilot_new();
}

void AdminUI_free()
{
	Pilot_free();
}

void AdminUI_quit()
{
	Pilot_stop();
}

static void AdminUI_run()
{
	while (!quiter)
	{
		AdminUI_display();
		AdminUI_captureChoice();
	}
	
}

static void AdminUI_display()
{
	printf("Vous pouvez effectuer les actions suivantes: \n"
		   "z: allez tout droit \n"
		   "s: reculer/stopper \n"
		   "q: gauche \n"
		   "d: droite \n"
		   "e: effacer les logs \n"
		   "r: afficher etat du robot \n"
		   "a: quitter \n");
}



static VelocityVector translate(Direction direction){
	VelocityVector vel;
	switch (direction)
	{
	case FORWARD:
		vel.dir = direction;
		vel.power = 80;
		break;
	case BACKWARD:
		vel.dir = direction;
		vel.power = 40;
		break;
	case NO:
		vel.dir = direction;
		vel.power = 0;
		break;
	case RIGHT:
		vel.dir = direction;
		vel.power = 30;
		break;
	case LEFT:
		vel.dir = direction;
		vel.power = 30;
		break;
	
	default:
		break;
	}
	return vel;
}

static void quit(){
	quiter = true;
}

static void ask4log(){
	Pilot_check();
}


static void eraseLog(){
	system("clear");
}

static void askMvt(Direction direction){
	VelocityVector vel = translate(direction);
	Pilot_setVelocity(vel);
}

static void AdminUI_captureChoice()
{
	char input;
	system("stty -icanon -echo");
	Direction direction;
	printf("Votre choix: ");
	input = getchar();
	printf("Input : %c\n",input);
	switch (input)
	{
	case 'z':
		printf("Robot Avance \n");
		direction = FORWARD;
		askMvt(direction);
		break;
	case 's':
		printf("Robot recule \n");
		direction = BACKWARD;
		askMvt(direction);
		break;
	case 'q':
		printf("Robot va a gauche\n");
		direction = LEFT;
		askMvt(direction);
		break;
	case 'd':
		printf("Robot va a droite\n");
		direction = RIGHT;
		askMvt(direction);
		break;
	case 'e':
		eraseLog();
		break;
	case 'r':
		printf("ask for log \n");
		ask4log();
		break;
	case 'a':
		system("stty icanon echo");
		printf("quit");
		quit();
		break;
	case ' ':
		direction = NO;
		askMvt(direction);
		break;
	default:
		printf("on arrete le bolide \n");
		direction = NO;
		askMvt(direction);
		break;
	}
	
}