#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions that are pretty basic and likely won't change very often or at all.
Current Revision: 2.1.3
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
	elementPhysical, //Currently does nothing.
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
