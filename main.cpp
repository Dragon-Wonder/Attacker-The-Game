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
Current Revision: 1.2b
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
int intPlayerX; //Player position in X and Y.
int intPlayerY;
int intTempTile; //Value to hold what the cell that the player is moving into is.
/*********************************************************************************************************/

int main()
{
	enum
    {
        tileUnused = 0, //0
        tileDirtWall, //1
        tileDirtFloor, //2
        tileStoneWall, //3
        tileCorridor, //4
        tileDoor, //5
        tileUpStairs, //6
        tileDownStairs, //7
        tileChest, //8
		tilePlayer //9
    };//From rooms.h this holds the different possible tiles that can appear on the map.
	intTempTile = tileUpStairs;
	char chrPlayerMade = 'F';
	char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;
	
	int intPlayerNewX;
	int intPlayerNewY;
	
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
		for (int y = 0; y < 25; y++){
			for (int x = 0; x < 80; x++){
				if (d.getCell(x,y)==9) //Finds where player is.
				{
					intPlayerX = x;
					intPlayerY = y;
					goto PostPlayerFind;
				};
			}
		}
		PostPlayerFind:
		do
		{
			PickDirection:
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			//cout<<endl<<"("<<intPlayerX<<","<<intPlayerY<<")"<<endl;
			cout<<"Please enter a direction you would like to go ( N , E , S , W )."<<endl<<"Enter X to exit."<<endl;
			cout<<"> ";
			cin>>charPlayerDirection;
			charPlayerDirection = CharConvertToUpper(charPlayerDirection);
			switch (charPlayerDirection)
			{
				case 'N' :
					intPlayerNewX = intPlayerX;
					intPlayerNewY = intPlayerY - 1;
					break;
				case 'S' :
					intPlayerNewX = intPlayerX;
					intPlayerNewY = intPlayerY + 1;
					break;
				case 'E' :
					intPlayerNewX = intPlayerX + 1;
					intPlayerNewY = intPlayerY;
					break;
				case 'W' :
					intPlayerNewX = intPlayerX - 1;
					intPlayerNewY = intPlayerY;
					break;
				case '&' :
					for (int y = 0; y < 25; y++){
						for (int x = 0; x < 80; x++){
							if (d.getCell(x,y)==tileDownStairs) //Finds where the down stairs are.
							{
								intPlayerNewX = x;
								intPlayerNewY = y;
								goto PostMovingCode;
							};
						}
					}
					break;
				case 'X' :
					cout << string(50, '\n');
					cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All progress will be lost."<<endl<<"Y or N"<<endl<<"> ";
					cin>>charPlayerDirection;
					charPlayerDirection = CharConvertToUpper(charPlayerDirection);
					switch (charPlayerDirection)
					{
						case 'Y' :
							return 0;
							break;
						default :
							goto PickDirection;
							break;
					}
					break;
				default : 
					cout<<endl<<"Invalid direction, please try again."<<endl;
					goto PickDirection;
					break;
			//End of case for direction picked.
			}
			PostMovingCode:
			switch (d.getCell(intPlayerNewX,intPlayerNewY))
			{
				case tileDownStairs :
					//Return a true saying that the player found the exit, aka the down stairs.
					charExitFind = 'T';
					break;
				case tileStoneWall :
				case tileDirtWall :
				case tileUnused :
				case tilePlayer :
					//Player is trying to walk into something they can't.
					//Just return a False saying they did not find the exit.
					charExitFind = 'F';
					break;
				case tileCorridor :
				case tileChest :
				case tileDirtFloor :
				case tileDoor :
				case tileUpStairs :
					//Player is walking into a tile they are allowed to, move around the tiles.
					d.setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
					intTempTile = d.getCell(intPlayerNewX,intPlayerNewY); //Set the temp value to what the next cell is.
					intPlayerY = intPlayerNewY;
					intPlayerX = intPlayerNewX;
					d.setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
					charExitFind = 'F'; //Return a false, as they did not find the exit.
					break;
				default :
					//Player is stepping on a tile that should never exist, if I remember to add it.
					//Therefore just return a false.
					charExitFind = 'F';
					break;
			//End of switch based on next cell.	
			}
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
