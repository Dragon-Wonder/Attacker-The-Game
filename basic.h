#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions that are pretty basic and likely won't change very often or at all.
Current Revision: 1.0.3
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM BETA TO GAMMA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================
2015/03/16	1.0			Patrick Rye		-Move from beta revisions to gamma revisions.
										-Changed some int to smaller variables because they don't need to be that big.	
=============================================================================================================================================================
2015/03/17	1.0.1		Patrick Rye 	-Changed order of elements
										-Made function that shows bar representing health.
										-Made function that returns multiplier depending on attacking and defending elements.
										-Added function which returns string name of element
										-Added function which returns string name of status
=============================================================================================================================================================	
2015/03/17	1.0.2		Patrick Rye 	-Added key amount to stat
										-Grammar & spelling fixes.
=============================================================================================================================================================	
*/

/*********************************************************************************************************/
#include <string>
//Some constant string for different messages that appear as large ASCII text.
const std::string OpeningMessage[16] = {"                                                             \n",
								   ",--.   ,--.       ,--.                                       \n",
								   "|  |   |  | ,---. |  | ,---. ,---. ,--,--,--. ,---.          \n",
								   "|  |.'.|  || .-. :|  || .--'| .-. ||        || .-. :         \n",
								   "|   ,'.   |\\   --.|  |\\ `--.' '-' '|  |  |  |\\   --.         \n",
								   "'--'   '--' `----'`--' `---' `---' `--`--`--' `----'         \n",
								   "  ,--.                                                       \n",
								   ",-'  '-. ,---.                                               \n",
								   "'-.  .-'| .-. |                                              \n",
								   "  |  |  ' '-' '                                              \n",
								   "  `--'   `---'                                               \n",
								   "  ,---.    ,--.    ,--.                ,--.                  \n",
								   " /  O  \\ ,-'  '-.,-'  '-. ,--,--. ,---.|  |,-. ,---. ,--.--. \n",
								   "|  .-.  |'-.  .-''-.  .-'' ,-.  || .--'|     /| .-. :|  .--' \n",
								   "|  | |  |  |  |    |  |  \\ '-'  |\\ `--.|  \\  \\\\   --.|  |    \n",
								   "`--' `--'  `--'    `--'   `--`--' `---'`--'`--'`----'`--'    \n"};

const std::string WinningMessage[6] = {"__   __            _    _ _       _ _ \n",
								 "\\ \\ / /           | |  | (_)     | | |\n",
								 " \\ V /___  _   _  | |  | |_ _ __ | | |\n",
								 "  \\ // _ \\| | | | | |/\\| | | '_ \\| | |\n",
								 "  | | (_) | |_| | \\  /\\  / | | | |_|_|\n",
								 "  \\_/\\___/ \\__,_|  \\/  \\/|_|_| |_(_|_)\n"};

/*********************************************************************************************************/
enum effectsplacement
{
	effectNone = 0,
	effectBlinded,
	effectFrozen,
	effectBurned,
	effectWet,
	effectPoison,
	effectBleeding,
	effectConfused,
};

enum statsplacement
{
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

enum elementsplacement
{
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

enum spelltypes
{
	typeHeal = 0,
	typeEffect,
	typeDamage,
};
/*********************************************************************************************************/

using namespace std;

unsigned int CalculateHealth(unsigned char HealthLevel, unsigned char ConsStat)
{
	//A simple function for calculating health.
	//In its own function so future changes will be changed everywhere.
	float HealthTemp = 0;
	HealthTemp = (0.9722 * pow(HealthLevel, 2) )+( 0.4167 * HealthLevel) + 48.611;
	HealthTemp += 23.979*exp(0.01414 * ConsStat);
	return floor(HealthTemp);
}

string StatusName(unsigned char effect)
{
	switch (effect)
	{
		case effectNone :
			return "no status";
		case effectBlinded :
			return "blinded";
		case effectFrozen :
			return "frozen";
		case effectBurned :
			return "burned";
		case effectWet :
			return "wet";
		case effectPoison :
			return "poisoned";
		case effectBleeding :
			return "bleeding";
		case effectConfused :
			return "confused";
	};
	return "ERROR";
}

string ElementName(unsigned char element)
{
	switch (element)
	{
		case elementLight :
			return "light";
		case elementWind :
			return "wind";
		case elementIce :
			return "ice";
		case elementWater :
			return "water";
		case elementDarkness :
			return "darkness";
		case elementEarth :
			return "earth";
		case elementFire :
			return "fire";
		case elementEnergy :
			return "energy";
		case elementPhysical :
			return "physical";
		case elementNone :
			return "none";
	};
	return "ERROR";
}

string BarMarker(unsigned int CurrentValue, unsigned int MaxValue)
{
	string TempHealthBar = "<";
	int HealthPercent = floor((CurrentValue * 100)/MaxValue);
	for (unsigned char Bar = 0; Bar < 20; Bar++)
	{
		if (HealthPercent >= 5) {TempHealthBar += "=";}
		else {TempHealthBar += " ";}
		HealthPercent -= 5;
	}
	TempHealthBar += ">";
	//cout<<TempHealthBar<<endl;
	return TempHealthBar;
}

float ElementMulti(unsigned char AttackingElement, unsigned char DefendingElement)
{
	/*The further away two elements are the more damage that they do to each other.
	  For example a fire attack on an ice monster will be 125% damage, while a fire
	  attack on fire monster will only do 75% damage. 2 spaces away will do normal damage
	  And none elements or physical do normal damage as well.*/
	  
	/*
				Light
		Energy			Wind
	Fire					Ice
		Earth			Water
				Darkness
	*/
	if (AttackingElement == elementNone || DefendingElement == elementNone) {return 1.0;}
	if (AttackingElement == elementPhysical || DefendingElement == elementPhysical) {return 1.0;}
	switch (abs(AttackingElement - DefendingElement))
	{
		case 0 :
			return 0.75;
		case 1 :
			return 0.875;
		case 2 :
			return 1;
		case 3 :
			return 1.125;
		case 4 :
			return 1.25;
		default : 
			return 1;
	};
	return 1;
}

bool DodgeCheck(unsigned char LUK, unsigned char DEX)
{
	//The way I worked out this dodge calc is that if the Dex and Luk both equal 150 (which isn't possible under the current levelling up system),
	//then they have a 25% chance to dodge. I also wanted Dex to factor into 75% of the chance and Luk only 25%
	//Can return true, that they dodged or false that they did not.
    float douDodgeChance = ((DEX/2)+(LUK/6)/4);
	if(rand() % 101 <= douDodgeChance) {return true;}
	else {return false;}
}

float DamageHealthPercent(unsigned int CurrentHealth, unsigned int MaximumHealth)
{
	/*Function that returns a percentage value that will be multiplied by the damage.
	  The value will vary with health so that the less health something has
	  The less damage it will do.
	  The max value it return is about 1.01 or something similar, the min value
	  is about 0.64 */
	
	float HealthPercent = CurrentHealth / MaximumHealth;
	float TempValue = 0;
	TempValue -= 0.8981 * pow(HealthPercent, 3);
	TempValue += 1.297 * pow(HealthPercent, 2);
	TempValue -= 0.0358 * HealthPercent;
	TempValue += 0.64;
	return TempValue;
}

string HitName()
{
	/*Outputs a string that represents an attack,
	   for example rather than just "hit" over and over,
	   you could get "stabbed" "hit"*/
	const string HitStringArray[5] = {"hit","stabbed","cut","slashed","damaged"};
	string TempString;
	TempString = HitStringArray[rand() % 5];
	if (TempString != "") {return TempString;}
	return "hit";
}

inline bool StunCheck(unsigned char intAttackerLuck, unsigned char intDefenderLuck)
{
	if (intDefenderLuck < intAttackerLuck) {if(rand()% 101 < (intAttackerLuck - intDefenderLuck) / 3) {return true;}}
	return false;
}

string StateOfBeing(unsigned int intCurrHealth, unsigned int intMaxHealth)
{
	/*Outputs a string that gives a description of how the monster is doing
	  Example: at full health can return "Healthy"
	  while below 10% of max health it might return "dying" or "badly wounded"*/
	float flHealthPercent = (intCurrHealth * 100)/intMaxHealth;
	string strState;
	unsigned char intRandomState;
	
	const string FullHealthOutput[3] = {"steady","well","healthy"};
	const string SeventyPHealthOutput[3] = {"wounded","damaged","hurt"};
	const string FiftyPHealthOutput[3] = {"injured","bleeding","very hurt"};
	const string TwentyFivePHealthOutput[3] = {"really hurt","in pain","badly damaged"};
	const string TenPHealthOutput[3] = {"badly wounded","badly hurt","close to dying"};
	const string FivePHealthOutput[3] = {"to be dying","heavily wounded","gravely wounded"};
	
	intRandomState = rand() % 3; //0-2
	
	if (flHealthPercent <= 5) {strState = FivePHealthOutput[intRandomState];}
	else if (flHealthPercent <= 10) {strState = TenPHealthOutput[intRandomState];}
	else if (flHealthPercent <= 25) {strState = TwentyFivePHealthOutput[intRandomState];}
	else if (flHealthPercent <= 50) {strState = FiftyPHealthOutput[intRandomState];}
	else if (flHealthPercent <= 70) {strState = SeventyPHealthOutput[intRandomState];}
	else {strState = FullHealthOutput[intRandomState];}
	
	return strState;
}

string EndOfEffectString(std::string Target, unsigned char Effect)
{
	string TempStr = "";
	//Returns string describing status effect ending.
	if (Target == "player")
	{
		switch (Effect)
		{
			case effectBlinded : 
				return "Your eyes begin to see again.";
				break;
			case effectFrozen :
				return "The ice surrounding your body melts away.";
				break;
			case effectBurned :
				return "You regain feeling in your burned flesh.";
				break;
			case effectWet :
				return "You feel dry again.";
				break;
			case effectPoison :
				return "Your body ejects the last of the poison.";
				break;
			case effectBleeding :
				return "Your bleeding wounds begin to close.";
				break;
			case effectConfused :
				return "Your head begins to clear.";
				break;
			case effectNone :
			default :
				return "ERROR";
				break;
		};
	}
	else
	{
		switch (Effect)
		{
			case effectBlinded : 
				TempStr = "The ";
				TempStr += Target;
				TempStr += " blinks his eyes and looks right at you.";
				break;
			case effectFrozen :
				TempStr = "The ice around the ";
				TempStr += Target;
				TempStr += " melts away.";
				break;
			case effectBurned :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " no longer appears bothered by its burns.";
				break;
			case effectWet :
				TempStr = "The water on the ";
				TempStr += Target;
				TempStr += " dries off";
				break;
			case effectPoison :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " no longer looks sick.";
				break;
			case effectBleeding :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " no longer appears bothered by its wounds.";
				break;
			case effectConfused :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " managed to stop running in circles.";
				break;
			case effectNone :
			default :
				return "ERROR";
				break;
		};
		return TempStr;
	}
	return "ERROR";
}

string StartOfEffectString(std::string Target, unsigned char Effect)
{
	string TempStr = "";
	//Returns string describing status effect ending.
	if (Target == "player")
	{
		switch (Effect)
		{
			case effectBlinded : 
				return "Your eyes begin to cloud up, preventing vision.";
				break;
			case effectFrozen :
				return "A block of ice encases your legs.";
				break;
			case effectBurned :
				return "A searing pain on your body is present.";
				break;
			case effectWet :
				return "You are now soaked to the bone.";
				break;
			case effectPoison :
				return "You feel sick to your stomach.";
				break;
			case effectBleeding :
				return "A wound has opened up and is bleeding badly.";
				break;
			case effectConfused :
				return "The world spins around you, you don't know where to go.";
				break;
			case effectNone :
			default :
				return "ERROR";
				break;
		};
	}
	else
	{
		switch (Effect)
		{
			case effectBlinded : 
				TempStr = "The ";
				TempStr += Target;
				TempStr += " cannot see any more.";
				break;
			case effectFrozen :
				TempStr = "A block of ice encases the ";
				TempStr += Target;
				TempStr += "'s legs.";
				break;
			case effectBurned :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " has painful burns on its body.";
				break;
			case effectWet :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " is soaked with water.";
				break;
			case effectPoison :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " looks sick.";
				break;
			case effectBleeding :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " has a badly bleeding wound.";
				break;
			case effectConfused :
				TempStr = "The ";
				TempStr += Target;
				TempStr += " starts running in circles.";
				break;
			case effectNone :
			default :
				return "ERROR";
				break;
		};
		return TempStr;
	}
	return "ERROR";
}

inline bool fileexists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

std::string ConvertToUpper(std::string& str)
{
	//Thanks to codekiddy for his post at http://www.cplusplus.com/forum/beginner/70692/
	std::locale settings;
	std::string converted;
	for(unsigned char i = 0; i < str.size(); ++i) {converted += (toupper(str[i], settings));}
	return converted;
}

std::string ConvertToLower(std::string& str)
{
	std::locale settings;
	std::string converted;
	for(unsigned char i = 0; i < str.size(); ++i) {converted += (tolower(str[i], settings));}
	return converted;
}

std::string ProperCase(std::string& str)
{
	std::locale settings;
	std::string converted;
	converted+= (toupper(str[1], settings));
	for(unsigned char i = 1; i < str.size(); ++i) {converted += (tolower(str[i], settings));}
	return converted;
}

char CharConvertToUpper(char chrCheck)
{
	//Modified version of the string convert to upper function to work on char
	locale settings;
	char converted;
	converted = (toupper(chrCheck, settings));
	return converted;
}

inline void ShowOpeningMessage() {for (unsigned char i = 0; i < 16; i++){cout<<OpeningMessage[i];}}

inline void ShowWinningMessage() {for (unsigned char i = 0; i < 6; i++) {cout<<WinningMessage[i];}}

#endif //If header was already called load nothing
