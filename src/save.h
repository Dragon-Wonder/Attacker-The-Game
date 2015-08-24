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
//This function is needed to pass the version of the program (a constant string in main.cpp)
//and place it in the variable here called Program Version for purposes of calling it in this header.
void PassProgramVerison(const string);
unsigned char SanityChecker(unsigned int, int );
char savefunction();
bool loadfunction();
bool LoadOldSave();
/*********************************************************************************************************/
#endif
