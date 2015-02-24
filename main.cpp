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
Current Revision: 5.0a
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/13/15	1.0a		Patrick Rye			-Original
=============================================================================================================================================================		
2/14/15 1.1a		Patrick Rye			-Nerffered Level 7+ monsters
											-This change makes 7-9 monster easier but level 10 is extremely difficult.
											-I will have to redo how the monster levels up completely, but not now.
										-Player stat upgrade boosted to 10 points.
										-Player now gets two stat upgrades every level.
										-Fixed grammar and spelling mistakes.
=============================================================================================================================================================											
2/17/15 2.0a		Patrick Rye			-Added change log (everything before this is just a guess and what I remember).
										-Moved the level up to its own function for easier modification.
										-Moved the battle scene to its own function for easier modification.
										-Added other monster base stats, will be used in a later revision for more variety.
										-Fixed mistake that would allow player to heal above the amount they should be allowed to.
										-Added second prompt for exiting game so player doesn't enter it by mistake.
=============================================================================================================================================================										
2/17/15	2.1a		Patrick Rye			-Made function to convert lower case letters into upper case ones so that inputs are less case sensitive.
										-More grammar and spelling fixes.
										-Added more comments to explain what is happening.
										-Fixed bug that allowed monster health to go below 0, causing the battles to never end (oops kind of a big issue).
										-Changed level up checker to a for loop rather than an if statement.
										-Did a general code cleaning to make it look nicer.
										-Added Copyright License as I might put this on the internet and may as well.
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Internet release~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================													
2/17/15	2.2a		Patrick Rye			-Post internet release edits
										-Added function to change string to all upper-case.
											-I am keeping the char and string to upper case functions separated until I test if the string one works on chars.
										-Made player initialize as a separate function that initializes the player. 
											-Made it its own function for later revisions, which may include a saving function.
										-More grammar and spelling fixes (I make a lot of these mistakes).
										-Added random monster function, which changes which monster you fight each battle.
=============================================================================================================================================================											
2/17/15 2.3a		Patrick Rye			-Implemented multiple types of monsters.
										-Went back to old method of monster levelling up due to the new way not working properly with new monsters.
=============================================================================================================================================================		
2/17/15 2.4a		Patrick Rye			-EVEN MORE GRAMMAR AND SPELLIGN FIXES!!
										-More comments explaining stuff.
										-Cleaned up the code some more to make it nicer.
										-Added more randomness to the crit calculator.
										-Added pause if you win the game. (oops)
=============================================================================================================================================================											
2/18/15	2.5a		Patrick Rye			-Replaced old convert to upper case function for char to a better one.
										-More grammar and spelling fixes. >.<
										-Fixed bug that caused more points to be put in LUK than should be.
										-Added random monster modifier, which adds adjectives such as "Strong", "Weak", etc....
											-Not yet implemented have to test for balance.
											-Not yet finished will finish and implement at later time.
=============================================================================================================================================================
2/18/15	2.5.1a		Patrick Rye			-Quick fix for the random monster generator not properly changing monster stats.
=============================================================================================================================================================										
2/18/15	3.0a		Patrick Rye			-Finished random monster modifier and implemented it.
										-Moved license to be first, followed by change log, and then the code.
											-This way the license is the first thing seen, and the code isn't split up by the change log.
										-Even more gosh dang spelling and grammar fixes. Focused more on comments and the change log then anything.
										-Cleaned up old code some more.
										-Added function to lower case a word.
										-Added function to lower case a word then capitalize the first letter.
											-For grammatical purposes.
=============================================================================================================================================================
2/19/15	3.1a		Patrick Rye			-Spelling and grammar fixes. (I swear every time I turn around 3 more mistakes appear).
										-More code clean up.
										-Changed damage calculator to be add 5 then multiply by crit.
										-Moved the 4 functions that changed the case of stuff to a header.
											-To test the functionality of headers and because these functions shouldn't be modified often
=============================================================================================================================================================
2/20/15	4.0a		Patrick Rye			-Redid player levelling up system to allow for 20 points to be placed in any arrangement of stats.
										-Redid dodge chance calculator.
										-Redid monster levelling up system. It still may need some work.
										-Added a "test.h" a header to place some code for debugging and testing purposes later.
=============================================================================================================================================================
2/20/15	4.1a		Patrick Rye			-Moved around a lot of word sections, and added system clears and system pauses.
										-More grammar and spelling fixes.
										-Added header that contains functions to generate random rooms.
										-Got rid of test.h as I can just make another one later.
										-New dungeon generates with each level.
											-At the moment this does nothing but once I figure out how to allow the player to move, a lot of things will change.
=============================================================================================================================================================
2/23/15	5.0a		Patrick Rye			-Player movement system implemented.
										-Moved battle related stuff to its own header.
										-Levelling up and player initializing also moved to battle header.
										-Replaced system("cls") with cout << string(50, '\n');
										-General code clean up.
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
#include "casechanger.h" //Functions that hold change the case of chars and strings
#include "rooms.h" //Functions that deal with generating a dungeon
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
//Make all the global variables that I need
int intMainLevel;
int intPlayerX; //Player position in X and Y
int intPlayerY;
int intTempTile = 6; //Value to hold what the cell that the player is moving into is, 6 is stairs up.
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
    };//From Rooms.h this holds the different possible tiles that can appear on the map.
	intTempTile = tileUpStairs;
	char chrPlayerMade = 'F';
	char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;
	
	int intPlayerNewX;
	int intPlayerNewY;
	
	cout<<"Welcome to the World of Attacker"<<endl<<"Your objective is to kill 10 monsters to win."<<endl;
	cout<<"Each level is harder than the last do you have what it takes to win?"<<endl;
	cout<<"Good luck!"<<endl<<endl<<endl<<endl;

	do {chrPlayerMade = PlayerInitialize();}while (chrPlayerMade != 'T');

	//cout << string(50, '\n');

	for(intMainLevel = 1; intMainLevel <= 10; intMainLevel++)
	{
		charExitFind = 'F';
		cout<<endl;
		Dungeon d;//generates dungeon.
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
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			//cout<<endl<<"("<<intPlayerX<<","<<intPlayerY<<")"<<endl;
			PickDirection:
			cout<<"Please enter a direction you would like to go (N,E,S,W)."<<endl;
			cout<<"> ";
			cin>>charPlayerDirection;
			charPlayerDirection = CharConvertToUpper(charPlayerDirection);
			if (charPlayerDirection == 'N')//Had to make this an if statement as the a case wouldn't work.
			{
				intPlayerNewX = intPlayerX;
				intPlayerNewY = intPlayerY - 1;
			}
			else if (charPlayerDirection == 'S')
			{
				intPlayerNewX = intPlayerX;
				intPlayerNewY = intPlayerY + 1;				
			}
			else if (charPlayerDirection == 'E')
			{
				intPlayerNewX = intPlayerX + 1;
				intPlayerNewY = intPlayerY;
			}
			else if (charPlayerDirection == 'W')
			{
				intPlayerNewX = intPlayerX - 1;
				intPlayerNewY = intPlayerY;
			}
			else
			{
				cout<<endl<<"Invalid direction, please try again."<<endl;
				goto PickDirection;
			}
			if (d.getCell(intPlayerNewX,intPlayerNewY) == tileDownStairs) {charExitFind = 'T';} //Return a true saying that they found the exit, aka the down stairs
			else if (d.getCell(intPlayerNewX,intPlayerNewY) == tileStoneWall) {charExitFind = 'F';} //They try to walk into a wall, just return a false that they did not find the exit
			else if (d.getCell(intPlayerNewX,intPlayerNewY) == tileDirtWall) {charExitFind = 'F';} //They try to walk into a wall, just return a false that they did not find the exit
			else //Player is walking into a tile they are allowed to, move around the tiles.
			{
				d.setCell(intPlayerX,intPlayerY,intTempTile); //Set old location back to what it was.
				intTempTile = d.getCell(intPlayerNewX,intPlayerNewY); //Set the temp value to what the cell is.
				intPlayerY = intPlayerNewY;
				intPlayerX = intPlayerNewX;
				d.setCell(intPlayerX,intPlayerY,tilePlayer); //Move the player.
				charExitFind = 'F'; //Return a false, as they did not find the exit.
			}
			if(rand() % 101 <= 10) //Random chance to encounter monster
			{
				cout << string(50, '\n');
				charBattleEnding = startbattle(intMainLevel); //Starts Battle.
				if(charBattleEnding == 'F') {return 0;} //Player lost battle.
			}
		}while (charExitFind != 'T');
	}
	cout<<endl<<endl<<endl<<endl<<"You win!!";
	system("pause");
	return 0;
//End of main
}
