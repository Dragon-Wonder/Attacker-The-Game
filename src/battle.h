#ifndef _BATTLE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BATTLE_H_INCLUDED__
/*********************************************************************************************************/
#include "basic.h"
#include "main.h"
#include "rooms.h"
#include <string>
#include <cstdio>
#include <cstdlib>
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
//Structure for different attacks used
struct stcAttack {
	string name; //Name of attack, kinda useless
	unsigned char element; //Element of attack, for calc multi later
	unsigned char basedamage; //Nothing at the moment, just here to try some stuff later.
	string hit; //Text that appears when the attack lands
};

//Structure for Mana and Health
struct healthmana {
	int current; //Current amount
	unsigned int max; //Max amount
};

//Structure for stats
struct stcStats {
	unsigned char str; //Strength (damage)
	unsigned char cons; //Constitution (health)
	unsigned char def; //Defence (damage taken)
	unsigned char dex; //Dexterity (speed)
	unsigned char luk; //Luck (randomness)
};

//Structure for status
struct stcStatus {
	unsigned int effect; //Effect Number based on enum
	unsigned char counter;//Keeps track of turns with effect for increased chance of it going away.
};

//Structure for items
/*
struct item {
	//Will expand as this becomes more relevant
	string name;
	unsigned char amount;
};

//Structure for inventory
struct inventory {
	item item1;
	item item2;
	item item3;
	item item4;
	item item5;
};
*/

//Structure for entities such as player and monsters
struct entity {
	string name; //Name of entity
	struct healthmana health; //Max and Current Health
	struct healthmana mana; //Max and Current Mana (only used for players atm)
	struct stcStats stats; //Entity Stats
	struct stcStatus status; //Entity status
	unsigned char element; //Element that the monster is. (for player is just physical)
	struct stcAttack attack; //Attack that it uses.
	unsigned char keys; //Currently does nothing.
};
/*********************************************************************************************************/
//These functions are here so that they can be referenced in the spells.h
int getbattlevalue(unsigned int);
void setbattlevalue(unsigned int, int);
int getmonstervalue(unsigned int);
void setmonstervalue(unsigned int, int);
unsigned int CalculateDamage(unsigned char, unsigned char, unsigned char);
string getMonsterName(void);
/*********************************************************************************************************/
bool RemoveStatusEffect(unsigned char, unsigned char, unsigned char);
void ApplyPoisonDamage(void);
void ApplyBleedingDamage(void);
bool MonsterAttack(unsigned int, float, bool);
bool PlayerAttack(unsigned int, float);
void RandomMonster(void);
void RandomMonsterModifier();
void LevelUpMonster();
void LevelUpFunction();
char BattleScene();
char PlayerInitialize();
bool startbattle(unsigned char);
/*********************************************************************************************************/
#include "spells.h"
/*********************************************************************************************************/
#endif
