#ifndef _SAVE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SAVE_H_INCLUDED__
/*********************************************************************************************************/
#include "main.h"
#include "basic.h"
#include "battle.h"
#include "rooms.h"
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
unsigned char SanityChecker(unsigned int, int );
char savefunction();
bool loadfunction();
bool LoadOldSave();
/*********************************************************************************************************/
#endif
