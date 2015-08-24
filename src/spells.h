#ifndef _SPELLS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SPELLS_H_INCLUDED__
/*********************************************************************************************************/
#include "main.h"
#include "battle.h"
#include "global.h"
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
struct spell {
	string name; //Name of spell
	unsigned char damage; //Base damage / heal.
	unsigned char cost; //Base cost.
	unsigned char type; //Type, damage, healing or effect
	unsigned char element; //Element of spell, currently does nothing.
	unsigned char effect; //Effect that can be caused by spell
};
/*********************************************************************************************************/
void init_spell(string);
#endif
