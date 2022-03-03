#ifndef _COMMON_
#define _COMMON_

#include "../../infox_prose-x86_64-v0.3/include/infox/prose/prose.h"
#include <netdb.h>
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 12346
#define SIZE_MESSAGE 128
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define YELLOW "\033[0;33m"

typedef enum
{
    D_Stop = 0,
    D_FORWARD,
    D_BACKWARD,
    D_LEFT,
    D_RIGHT,
    D_NO,
    D_NB_DIRECTION,
} Direction_e;

typedef enum
{
    O_CHANGE_MVT = 0,
    O_ASK_LOG,
    O_STOP,
    O_NB_ORDER,
} Order_e;

typedef struct
{
    Order_e ordrer;
    Direction_e direction;
    int speed;
    bool_e collision;
    int luminosity;

} Data_s;

#endif // _COMMON_