#ifndef _BASIC_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BASIC_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions that are pretty basic and likely won't change very often or at all.
Current Revision: 2.1.2
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
*/

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

#endif //If header was already called load nothing
