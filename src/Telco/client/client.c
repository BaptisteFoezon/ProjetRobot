#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../../common.h"
#include "client.h"

#define MAX_CONNECTION_ATTEMP (60)

Data_s data;

static int socket_ecoute;
static struct sockaddr_in server_address;

extern void Client_New()
{
    struct hostent *host = gethostbyname(IP_SERVER);

    if (host == NULL)
    {
        printf("Hote inconnu");
        return;
    }
    server_address.sin_port = htons(PORT_SERVER);
    server_address.sin_family = AF_INET;
    server_address.sin_addr = *((struct in_addr *)host->h_addr_list[0]);
    socket_ecoute = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ecoute < 0)
    {
        printf("%sErreur dans les sockets%s", RED, WHITE);
        return;
    }
    printf("%sClient is created\n%s", GREEN, WHITE);
}

extern void Client_Start()
{
    int timeoutCounter = 0;
    printf("%stentative de connexion au serveur .....%s\n", YELLOW, WHITE);
    while (timeoutCounter < MAX_CONNECTION_ATTEMP)
    {
        timeoutCounter++;
        if (connect(socket_ecoute, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        {
            printf("%sEchec de la connexion%s\n", RED, WHITE);
            sleep(1);
        }
        else
        {
            printf("%sConnexion réuissit \n%s", GREEN, WHITE);
            break;
        }
    }
}

extern void Client_stop()
{
    TRACE("Client Stop");
    close(socket_ecoute);
}

extern void Client_sendMsg(Data_s datasend)
{
    int _quantityWritten = 0;
    int _quantityToWrite = sizeof(datasend);
    TRACE("Mouvement envoyer par le client : %i \n", datasend.direction);

    while (_quantityToWrite > 0)
    {
        _quantityWritten += write(socket_ecoute, &datasend, _quantityToWrite);
        if (_quantityToWrite < 0)
        {
            printf("%sErreur lors de l'envoie du message%s", RED, WHITE);
            break;
        }
        else
        {
            _quantityToWrite -= _quantityWritten;
        }
    }
}

extern Data_s Client_readMsg()
{
    Data_s _datarcv;
    int _quantityRead = 0;
    int _quantityToRead = sizeof(_datarcv);
    while (_quantityToRead > 0)
    {
        _quantityRead = read(socket_ecoute, &_datarcv, _quantityToRead);
        if (_quantityRead < 0)
        {
            printf("%sErreur lors de la réception du message%s", RED, WHITE);
            break;
        }
        else
        {
            _quantityToRead -= _quantityRead;
        }
    }
    if (_quantityToRead == 0)
    {
        TRACE("Data read\n");
    }
    return _datarcv;
}