/*
Made By: Patrick J. Rye
Purpose: A game I made as an attempt to teach myself c++, just super basic, but going to try to keep improving it as my knowledge increases.
Current Revision: 1.1c
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM BETA TO GAMMA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2015/03/13	1.0c		Patrick Rye		-Move from beta revisions to gamma revisions.
										-Changed some int to smaller variables because they don't need to be that big.
										-Fixed bug where new dungeon wasn't generating properly. (This is what happens when you don't play test changes for a while).
										-Made it so you have to be in debug mode to force a monster (Don't know why you would want this otherwise)
										-General code improvement.
=============================================================================================================================================================
2015/03/17	1.1c		Patrick Rye		-Grammar & spelling fixes.
										-Updated save.h with more values.
										-Implemented mana system.
=============================================================================================================================================================		
*/

/*********************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <cstdio>
#include <ctime>
/*********************************************************************************************************/
#include "basic.h" //Functions that are simple, referenced many places and/or won't need to be changed very often.
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
#include "rooms.h" //Functions that deal with generating a dungeon, and moving through it.
#include "spells.h" //Functions that deal with spells and magic.
/*********************************************************************************************************/
using namespace std;
Dungeon d; //Define the dungeon class as 'd' so I can use functions in there anywhere later in the code.
/*********************************************************************************************************/
//Make all the global variables that I need.
unsigned char intMainLevel = 1; //The level of the dungeon.
unsigned char intLevelStart = 1; //The level that the game starts at. Will be 1 unless loading from a save.
bool blDebugMode = false; //If game is in debug mode or not, effects if player has access to debug commands.
const string CurrentVerison = "1.1c"; //The current version of this program, stored in a save file later on.
/*********************************************************************************************************/
//These functions have to be up here as functions in save.h use them.
//These values are used to pass values to the save header so that they may be saved.
//Or to set values from a load.
int getmainvalue(unsigned char intvalue)
{
	if(intvalue == 0 ) {return intMainLevel;}
	else if (intvalue == 1) {return intLevelStart;}
	else {return 1;}
}
void setmainvalue(unsigned char intlocation, unsigned int intvalue) {if (intlocation == 0) {intLevelStart = intvalue;}}
void setdebugmode(bool blsetdebugmode) {blDebugMode = blsetdebugmode;}
#include "save.h" //A header to hold functions related to saving and loading.
/*********************************************************************************************************/

int main()
{
	PassProgramVerison(CurrentVerison); //Pass current program version into the save header.
	cout << string(48, '\n');
	char charPlayerDirection;
	bool blBattleEnding = false;
	char charExitFind;
	bool blOldSave = false;
	char chrPlayerMade = 'F';
	char chrSaveSuccess = 'N'; //N means that save has not been run.
	//If game is not already in debug mode, checks if source code exists then put it in debug mode if it does.
	if (!(blDebugMode)) {blDebugMode = fileexists("main.cpp"); } 
	//Sets debug mode for rooms.h, battle.h, & spells.h
	if (blDebugMode) {SetBattleDebugMode(true); SetRoomDebugMode(true); SetSpellDebugMode(true);}
	ShowOpeningMessage();
	getchar();
	cout<<string(50,'\n');
	
	if (fileexists("save.bif")) //Check if there is a save present.
	{
		blOldSave = LoadOldSave();
		if (blOldSave) {chrPlayerMade = 'T';}
	//End of if save exists.	
	}
	else {cout<<string(50, '\n');}
	
	if(!blOldSave) //If it is not an old save show welcome message.
	{
		cout<<endl<<"Your objective is to go through 10 randomly generated dungeons."<<endl;
		cout<<"You are looking for the stairs down ( > ). While you are represented by @ ."<<endl;
		cout<<"Every step brings you closer to your goal, but there might be a monster there as well."<<endl;
		cout<<"Each level is harder than the last, do you have what it takes to win?"<<endl;
		cout<<"Good luck!"<<endl<<endl<<endl<<endl;
		while (chrPlayerMade != 'T') {chrPlayerMade = PlayerInitialize();}; //Repeat initialization until player is made.
	}

	for(intMainLevel = intLevelStart; intMainLevel <= 10; intMainLevel++)
	{
		//Do level up if new level.
		if (intMainLevel > intLevelStart) {LevelUpFunction();}
		charExitFind = 'F';
		cout<<endl;
		if (blOldSave && intMainLevel == intLevelStart) {/*d.playerfind();*/ d.showDungeon();} //If old save and the level of that save, just load old dungeon.
		else {d.cmain();/*Generates dungeon.*/} //If it is not old game OR a different level of old game, make new dungeon.
		
		do
		{
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<(int)intMainLevel<<" of 10."<<endl;
			cout<<"Please enter a direction you would like to go: "<<endl;
			cout<<"[N]orth,  [E]ast,  [S]outh,  [W]est  "<<endl;
			cout<<"E[X]it,   [C]heck your health, [H]eal,   Sa[V]e  "<<endl;
			if (blDebugMode) {cout<<"[L]evel up, or [M]onster."<<endl;}
			cout<<"> ";
			cin>>charPlayerDirection;
			charPlayerDirection = CharConvertToUpper(charPlayerDirection);
			charExitFind = d.PlayerMovement(charPlayerDirection);
			if (charExitFind == 'E') {return 0;} //If we get an error exit program.
			if (charExitFind == 'S') {chrSaveSuccess = savefunction();} //Save the game.
			switch (chrSaveSuccess)
			{
				case 'T' :
					cout<<endl<<"Save succeeded."<<endl;
					getchar();
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
				case 'F' :
					cout<<endl<<"Save failed!"<<endl;
					getchar();
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
			}
			if (!(charExitFind=='S') && !(charPlayerDirection == 'C')) //If player did not save or did not check himself, see if player runs into monster.
			{
				if(rand() % 101 <= 10 || (charExitFind == 'M' && blDebugMode)) //Random chance to encounter monster, or debug code to force monster encounter.
				{
					cout << string(50, '\n');
					blBattleEnding = startbattle(intMainLevel); //Starts battle.
					setbattlevalue(statKeys,getbattlevalue(statKeys) + getmonstervalue(statKeys)); //Give player a key if monster had one.
					if(!blBattleEnding) {return 0;} //Player lost battle.
				}
			}
		}while (charExitFind != 'T'); //Repeat until player finds exit.
	//End of FOR levels.
	}
	cout << string(50, '\n');
	ShowWinningMessage();
	getchar();
	return 0;
//End of main
}
