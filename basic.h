#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions that are pretty basic and likely won't change very often or at all.
Current Revision: 2.1.4
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2015/02/20	1.0			Patrick Rye		-Original from 3.1a
=============================================================================================================================================================
2015/03/02	2.0			Patrick Rye		-Renamed to Basic.h
										-Added save file checker function.
=============================================================================================================================================================
2015/03/02	2.1			Patrick Rye		-Changed save file checker to be able to check for any file name.
=============================================================================================================================================================
2015/03/04	2.1.1		Patrick Rye		-Removed save exists function as it was replaced by file exists.
=============================================================================================================================================================
2015/03/05	2.1.2 		Patrick Rye		-Changed change log date format from MM/DD/YY to YYYY/MM/DD because I like it better.
=============================================================================================================================================================
2015/03/09	2.1.3		Patrick Rye		-Moved win / opening messages here.
										-Moved enums here.
=============================================================================================================================================================
2015/03/09	2.1.4		Patrick Rye		-Added more effects.
										-Updated some other stuff.
										-Function to return string of start / end of status effect.
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
enum effects
{
	effectNone = 0,
	effectBlinded,
	effectFrozen,
	effectBurned,
	effectWet,
	effectPoison,
	effectBleeding,
	effectConfused
};

enum stats
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
};

enum elements
{
	elementFire = 0,
	elementIce,
	elementEnergy,
	elementDarkness,
	elementLight,
	elementEarth,
	elementWind,
	elementWater,
	elementPhysical, //Currently does nothing. (Will factor in when I make elemental weaknesses)
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

bool DodgeCheck(int LUK, int DEX)
{
	//The way I worked out this dodge calc is that if the Dex and Luk both equal 150 (which isn't possible under the current levelling up system),
	//then they have a 25% chance to dodge. I also wanted Dex to factor into 75% of the chance and Luk only 25%
	//Can return true, that they dodged or false that they did not.
    double douDodgeChance = ((DEX/2)+(LUK/6)/4);
	if(rand() % 101 <= douDodgeChance) {return true;}
	else {return false;}
}

bool RemoveStatusEffect(int TargetLuk, int CurrentEffect, int EffectTurns)
{
	//Check if status effect should be removed based on turns and luck.
	if (EffectTurns >= 5) {return true;} //Get rid of effect if it has been there for more than 5 turns.
	if (rand() % 101 <= (TargetLuk)  + (EffectTurns *2.5) - (intBattleLevel * 2)) {return true;}
	return false;
}

float DamageHealthPercent(int CurrentHealth, int MaximumHealth)
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

bool StunCheck(int intAttackerLuck, int intDefenderLuck)
{
	if (intDefenderLuck < intAttackerLuck) {if(rand()% 101 < (intAttackerLuck - intDefenderLuck) / 3) {return true;}}
	return false;
}

string StateOfBeing(int intCurrHealth, int intMaxHealth)
{
	/*Outputs a string that gives a description of how the monster is doing
	  Example: at full health can return "Healthy"
	  while below 10% of max health it might return "dying" or "badly wounded"*/
	long flHealthPercent = (intCurrHealth * 100)/intMaxHealth;
	string strState;
	int intRandomState;
	
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

string EndOfEffectString(std::string Target, int Effect)
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
				return "Your bleeding wounds being to close.";
				break;
			case effectConfused :
				return "Your head is now clear.";
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

string StartOfEffectString(std::string Target, int Effect)
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

bool fileexists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

std::string ConvertToUpper(std::string& str)
{
	//Thanks to codekiddy for his post at http://www.cplusplus.com/forum/beginner/70692/
	std::locale settings;
	std::string converted;
	for(short i = 0; i < str.size(); ++i) {converted += (toupper(str[i], settings));}
	return converted;
}

std::string ConvertToLower(std::string& str)
{
	std::locale settings;
	std::string converted;
	for(short i = 0; i < str.size(); ++i) {converted += (tolower(str[i], settings));}
	return converted;
}

std::string ProperCase(std::string& str)
{
	std::locale settings;
	std::string converted;
	converted+= (toupper(str[1], settings));
	for(short i = 1; i < str.size(); ++i) {converted += (tolower(str[i], settings));}
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

void ShowOpeningMessage() {for (int i = 0; i < 16; i++){cout<<OpeningMessage[i];}}

void ShowWinningMessage() {for (int i = 0; i < 6; i++) {cout<<WinningMessage[i];}}

#endif //If header was already called load nothing
