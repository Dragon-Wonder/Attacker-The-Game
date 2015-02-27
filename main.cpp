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
Current Revision: 1.1b
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
2/24/15	1.1b		Patrick Rye			-Added arrow key movement controlling.
=============================================================================================================================================================		
*/

/*********************************************************************************************************/
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <cstdio>
#include <ctime>
/*********************************************************************************************************/
#include "casechanger.h" //Functions that hold change the case of chars and strings
#include "rooms.h" //Functions that deal with generating a dungeon
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
/*********************************************************************************************************/
using namespace std;
/*********************************************************************************************************/
/*#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77*/
/*********************************************************************************************************/
//Make all the global variables that I need
int intMainLevel;
int intPlayerX; //Player position in X and Y
int intPlayerY;
int intTempTile = 6; //Value to hold what the cell that the player is moving into is, 6 is stairs up.
/*********************************************************************************************************/

void initialize()
{
	/* Curses Initialisations */
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
}

void finalize()
{
	refresh();
	getch();
	endwin();
}

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
	//char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;
	
	int intPlayerNewX;
	int intPlayerNewY;
	
	initialize();
	
	cout<<"Welcome to the World of Attacker"<<endl<<"Your is to go through 10 randomly generated dungeons."<<endl;
	cout<<"You are looking for the stairs down (>). While you are represented by †"<<endl;
	cout<<"Every brings you closer to your goal, but there might be a monster there as well."<<endl;
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
			//PickDirection:
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			//cout<<endl<<"("<<intPlayerX<<","<<intPlayerY<<")"<<endl;
			/*cout<<"Please enter a direction you would like to go (N,E,S,W)."<<endl<<"Enter X to exit."<<endl;
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
			else if (charPlayerDirection == 'D')
			{
				//Debug code that moves player directly to down stairs.
				for (int y = 0; y < 25; y++){
					for (int x = 0; x < 80; x++){
						if (d.getCell(x,y)==tileDownStairs) //Finds where the down stairs are.
						{
							intPlayerNewX = x;
							intPlayerNewY = y;
						};
					}
				}
			}
			else if (charPlayerDirection == 'X')
			{
				cout << string(50, '\n');
				cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All progress will be lost"<<endl<<"Y or N"<<endl<<"> ";
				cin>>charPlayerDirection;
				charPlayerDirection = CharConvertToUpper(charPlayerDirection);
				switch (charPlayerDirection)
				{
					case 'Y' :
						return 0;
					default :
						goto PickDirection;
				}
			}
			else
			{
				cout<<endl<<"Invalid direction, please try again."<<endl;
				goto PickDirection;
			}*/
			int key;
			key = wgetch( stdscr );
			switch(key)
			{
				case KEY_LEFT:
					intPlayerNewX= intPlayerX - 1;
					intPlayerNewY = intPlayerY;
				break;
				case KEY_UP:
					intPlayerNewX= intPlayerX;
					intPlayerNewY = intPlayerY -1;
				break;
				case KEY_RIGHT:
					intPlayerNewX= intPlayerX + 1;
					intPlayerNewY = intPlayerY;
				break;
				case KEY_DOWN:
					intPlayerNewX= intPlayerX;
					intPlayerNewY = intPlayerY + 1;
				break;
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
	cout << string(50, '\n');
	cout<<"You win!!";
	system("pause");
	finalize();
	return 0;
//End of main
}
