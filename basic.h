#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions that are pretty basic and likely won't change very often or at all.
Current Revision: 2.1
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/20/15	1.0			Patrick Rye			-Original from 3.1a
=============================================================================================================================================================
3/2/15	2.0			Patrick Rye			-Renamed to Basic.h
										-Added save file checker function.
=============================================================================================================================================================
3/2/15	2.1			Patrick Rye			-Changed save file checker to be able to check for any file name.
=============================================================================================================================================================
*/

using namespace std;


bool fileexists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

bool saveexists()
{
  ifstream ifile("save.bif");
  return ifile;
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


#endif //If header was already called load nothing
