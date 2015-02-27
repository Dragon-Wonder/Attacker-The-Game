/*
 ---------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
---------------------------------------------------------------------------
*/
/*
Made By: Patrick J. Rye
Purpose: A game I made as an attempt to teach myself c++, just super basic, but going to try to keep improving it as my knowledge increases.
Current Revision: 1.3b
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM ALPHA TO BETA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/24/15	1.0b		Patrick Rye			-Moved from V5.0-alpha to V1.0-beta
										-Fixed level up so it happens when you get to a new level.
										-Allowed exit on map.
										-Fixed opening text to reflect recent changes in the game.
										-Grammar and spelling fixes (yay, made it several revisions without having to do this. :) ).
=============================================================================================================================================================
2/24/15	1.1b		Patrick Rye			-Attempted to allow movement on map through arrow keys.
											-Could not get this to work and broke everything. Rolling back to previous version.
											-Keeping this attempt in the record and will try to implement it again later.
=============================================================================================================================================================
2/25/15	1.2b		Patrick Rye			-Grammar and spelling fixes. ((╯°□°)╯︵ ┻━┻)
										-Cleaned up code some more.
										-Changed some if statements to case switches.
										-Added breaks to case switches.
=============================================================================================================================================================
2/26/15	1.3b		Patrick Rye			-Moved player movement to the room.h
=============================================================================================================================================================
*/

/*********************************************************************************************************/
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <cstdio>
#include <ctime>
/*********************************************************************************************************/
#include "casechanger.h" //Functions that hold change the case of chars and strings.
#include "rooms.h" //Functions that deal with generating a dungeon.
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
//Make all the global variables that I need.
int intMainLevel;
/*********************************************************************************************************/

int main()
{

	char chrPlayerMade = 'F';
	char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;

	cout<<"Welcome to the World of Attacker"<<endl<<"Your objective is to go through 10 randomly generated dungeons."<<endl;
	cout<<"You are looking for the stairs down ( > ). While you are represented by †"<<endl;
	cout<<"Every step brings you closer to your goal, but there might be a monster there as well."<<endl;
	cout<<"Each level is harder than the last, do you have what it takes to win?"<<endl;
	cout<<"Good luck!"<<endl<<endl<<endl<<endl;

	do {chrPlayerMade = PlayerInitialize();}while (chrPlayerMade != 'T'); //Repeat initialization until player is made.
	//cout << string(50, '\n');
	for(intMainLevel = 1; intMainLevel <= 10; intMainLevel++)
	{
		//Do level up if not first level.
		if( intMainLevel != 1) { LevelUpFunction();}
		charExitFind = 'F';
		cout<<endl;
		Dungeon d;//Generates dungeon.

		do
		{
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			cout<<"Please enter a direction you would like to go ( N , E , S , W )."<<endl<<"Enter X to exit."<<endl;
			cout<<"> ";
			cin>>charPlayerDirection;
			charPlayerDirection = CharConvertToUpper(charPlayerDirection);
			charExitFind = d.PlayerMovement(charPlayerDirection);
			if (charExitFind == 'E') {return 0;} //If we get an error exit program.
			if(rand() % 101 <= 10) //Random chance to encounter monster.
			{
				cout << string(50, '\n');
				charBattleEnding = startbattle(intMainLevel); //Starts battle.
				if(charBattleEnding == 'F') {return 0;} //Player lost battle.
			}
		}while (charExitFind != 'T'); //Repeat until player finds exit.
	}
	cout << string(50, '\n');
	cout<<"You win!!";
	system("PAUSE");
	return 0;
//End of main
}
