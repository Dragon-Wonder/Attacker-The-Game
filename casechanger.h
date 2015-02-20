#ifndef _CASECHANGER_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again
#define _CASECHANGER_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold the case changing functions, in a header as these should not be changed often and to test the options that headers give me.
Current Revision: 1.0
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/20/15	1.0			Patrick Rye			-Original from 3.1a
=============================================================================================================================================================		
*/

using namespace std;

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
