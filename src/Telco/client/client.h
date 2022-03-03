#ifndef _Client_
#define _Client_

#include "../../common.h"

extern void Client_New();
extern void Client_Start();
extern Data_s Client_readMsg();
extern void Client_sendMsg(Data_s data);

#endif // _Client_