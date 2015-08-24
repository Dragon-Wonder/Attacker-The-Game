#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__
/*********************************************************************************************************/
#include <string>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <fstream>
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
enum effectsplacement {
	effectNone = 0,
	effectBlinded,
	effectFrozen,
	effectBurned,
	effectWet,
	effectPoison,
	effectBleeding,
	effectConfused,
};

enum statsplacement {
	statStr = 0,
	statCons,
	statDef,
	statDex,
	statLuk,
	statCurrHealth,
	statMaxHealth,
	statStatus,
	statStatusCounter,
	statKeys,
	statCurrMana,
	statMaxMana,
	statElement,
};

enum elementsplacement {
	elementLight = 0,
	elementWind,
	elementIce,
	elementWater,
	elementDarkness,
	elementEarth,
	elementFire,
	elementEnergy,
	elementPhysical,
	elementNone //For spells that don't do damage.
};

enum spelltypes {
	typeHeal = 0,
	typeEffect,
	typeDamage,
};
/*********************************************************************************************************/
unsigned int CalculateHealth(unsigned char, unsigned char);
string StatusName(unsigned char);
string ElementName(unsigned char);
string BarMarker(unsigned int, unsigned int);
float ElementMulti(unsigned char, unsigned char);
bool DodgeCheck(unsigned char, unsigned char);
float DamageHealthPercent(unsigned int, unsigned int);
string HitName(void);
bool StunCheck(unsigned char, unsigned char);
string StateOfBeing(unsigned int, unsigned int);
string EndOfEffectString(string, unsigned char);
string StartOfEffectString(string, unsigned char);
bool fileexists(const char *);
string ConvertToUpper(string&);
string ConvertToLower(string&);
string ProperCase(string&);
char CharConvertToUpper(char);
void ShowOpeningMessage(void);
void ShowWinningMessage(void);
/*********************************************************************************************************/
#endif //If header was already called load nothing
