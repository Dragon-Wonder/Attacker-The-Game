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
Current Revision: 1.0e
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXPERIEMENTAL VERISON~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
3/3/15	1.0e		Patrick Rye			-Added arrow key movement controlling.
=============================================================================================================================================================		
*/

/*********************************************************************************************************/
#include <iostream>
#include "ncurses/curses.h"
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

	initscr();
	raw();
	keypad(stdscr, TRUE);
	//noecho();
}

void finalize()
{
	refresh();
	getch();
	endwin();
}


int main()
{
	initialize();
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
	
	printf("Welcome to the World of Attacker\nYour is to go through 10 randomly generated dungeons.\n");
	printf("You are looking for the stairs down (>). While you are represented by †\n");
	printf("Every brings you closer to your goal, but there might be a monster there as well.\n");
	printf("Each level is harder than the last, do you have what it takes to win?\n");
	printf("Good luck!\n\n\n\n");
	
	do {chrPlayerMade = PlayerInitialize();}while (chrPlayerMade != 'T'); //Repeat initialization until player is made.
	//cout << string(50, '\n');
	for(intMainLevel = 1; intMainLevel <= 10; intMainLevel++)
	{
		//Do level up if not first level.
		if( intMainLevel != 1) { LevelUpFunction();}
		charExitFind = 'F';
		cout<<"\n";
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
			cout<<"Level "<<intMainLevel<<" of 10."<<"\n";
			//cout<<"\n"<<"("<<intPlayerX<<","<<intPlayerY<<")"<<"\n";
			int ch;
			ch = wgetch( stdscr );
			switch(ch)
			{
				case KEY_LEFT :
					intPlayerNewX= intPlayerX - 1;
					intPlayerNewY = intPlayerY;
				break;
				case KEY_UP :
					intPlayerNewX= intPlayerX;
					intPlayerNewY = intPlayerY -1;
				break;
				case KEY_RIGHT :
					intPlayerNewX= intPlayerX + 1;
					intPlayerNewY = intPlayerY;
				break;
				case KEY_DOWN :
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
