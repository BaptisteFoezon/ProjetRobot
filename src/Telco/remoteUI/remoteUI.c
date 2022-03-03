#include "../client/client.h"
#include "../../common.h"
#include <stdio.h>
#include <stdlib.h>
#include "remoteUI.h"


static void display();

static void run();

static void askMvt(Direction_e direction);

static void eraseLog();

static void quit();

static void RemoteUI_ask4log();

static bool_e running = FALSE;

extern void RemoteUI_New(){
    Client_New();
}

extern void RemoteUI_Start(){
    Client_Start();
    running = TRUE;
    run();

}


extern void RemoteUI_Stop(){
    quit();

}


extern void RemoteUI_setIP(char ip){

}


extern void captureChoice(){
char input;
	system("stty -icanon -echo");
	Direction_e direction;
	printf("Votre choix: ");
	input = getchar();
	printf("Input : %c\n",input);
	switch (input)
	{
	case 'z':
		printf("Robot Avance \n");
		direction = D_FORWARD;
		askMvt(direction);
		break;
	case 's':
		printf("Robot recule \n");
		direction = D_BACKWARD;
		askMvt(direction);
		break;
	case 'q':
		printf("Robot va a gauche\n");
		direction = D_LEFT;
		askMvt(direction);
		break;
	case 'd':
		printf("Robot va a droite\n");
		direction = D_RIGHT;
		askMvt(direction);
		break;
	case 'e':
		eraseLog();
		break;
	case 'r':
		printf("ask for log \n");
		RemoteUI_ask4log();
		break;
	case 'a':
		system("stty icanon echo");
		printf("quit\n");
		quit();
		break;
	case ' ':
		direction = D_NO;
		askMvt(direction);
		break;
	default:
		direction = D_NO;
		askMvt(direction);
		break;
	}
}









extern void askMvt(Direction_e dir){
	Data_s data;
	data.direction = dir;
    data.ordrer = O_CHANGE_MVT;
    Client_sendMsg(data);

}

void RemoteUI_ask4log(){
    Data_s data;
    Data_s _logData;
    data.ordrer = O_ASK_LOG;
    Client_sendMsg(data);
    _logData = Client_readMsg();
    printf("%sEtat du bolide :\n"
           "Vitesse : %i \n"
           "Collision: %i \n"
           "Luminosité: %i %s\n",
           YELLOW, _logData.speed, _logData.collision, _logData.luminosity, WHITE);

}



extern void eraseLog(){
    system("clear");
    display();
}

extern void quit(){
    running = FALSE;
}
  
extern void run(){
    while (running == TRUE)
    {
        display();
        captureChoice();
    }
    

}

extern void display(){
    printf("Vous pouvez effectuer les actions suivantes: \n"
    "z: allez tout droit \n"
    "s: reculer/stopper \n"
    "q: gauche \n"
    "d: droite \n"
    "e: effacer les logs \n"
    "r: afficher etat du robot \n"
    "a: quitter \n");
}