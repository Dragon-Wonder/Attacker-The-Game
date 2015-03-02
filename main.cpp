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
Current Revision: 2.1b
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
2/27/15	2.0b		Patrick Rye			-Added a save function, for testing purposes.
										-Added load function.
										-Added function to see if file exists.
=============================================================================================================================================================
2/27/15	2.1b		Patrick Rye			-Moved save checker to basic.h
										-Renamed casechecker.h to basic.h
										-Added more comments explaining parts of the code.
										-Changed some names of functions to better reflect what they do.
										-Health is now carried between battles.
										-Moved healing to be able to happen between battles.
										-Added fail check for load function.
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
#include "basic.h" //Functions that are simple and won't need to be changes very often.
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
#include "rooms.h" //Functions that deal with generating a dungeon.
/*********************************************************************************************************/
using namespace std;
Dungeon d;
/*********************************************************************************************************/
//Make all the global variables that I need.
int intMainLevel;
int intLevelStart;
/*********************************************************************************************************/

char savefunction()
{
	/*
	Testing a possible save function.
	2 Return values possible.
	T = True, save succeeded.
	F = False, save failed.
	*/
	int intCheckSum = 0;
	int arrbattlesave[7];
	int arrmainsave[1] = {intMainLevel}; //An array of all the values needed to be saved from main.cpp
	int arrroomsave[80][20];
	for (int i = 0; i < 6; i++) {arrbattlesave[i] = getbattlevalue(i);} //Build array of player stats, and player health.
	for (int y = 0; y < 20; y++) {for (int x = 0; x < 80; x++) {arrroomsave[x][y] = d.getCell(x,y);}} //Build array of the dungeon.
	ofstream savefile;
	savefile.open ("save.bif");
	for (int i = 0; i < 7; i++) {savefile << arrbattlesave[i] << "\n";}
	//savefile << "\n";
	for (int i = 0; i < 1; i++) {savefile << arrmainsave[i] << "\n";}
	//savefile << "\n";
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++) {savefile << arrroomsave[x][y] << "\n";}
		//savefile << " ";
	}
	savefile.close();
	//Save will now attempt to "load" the save it just made and compare it to the data available.
	//Checks to see if save is correct or not.
	ifstream loadfile("save.bif");
	int arrloadnumbers[1608];
	int x;
	for(int i = 0; i < 1608; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	for (int i = 0; i < 8; i++)
	{
		if(i<7) {if (arrloadnumbers[i]==arrbattlesave[i]){intCheckSum++;}}
		else if (i == 7) {if (arrloadnumbers[i]==intMainLevel) {intCheckSum++;}}
	} 
	int num = 7;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	cout<<endl<<endl<<intCheckSum;
	if(intCheckSum >= 1608) {return 'T';} //All of the saved values are correct if it equals 1608.
	else {return 'F';} //Some of the values are wrong, say that the save failed.
}


bool loadfunction()
{
	ifstream loadfile("save.bif");
	int arrloadnumbers[1608];
	int x;
	for(int i = 0; i < 1608; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	for (int i = 0; i < 8; i++)
	{
		if(i<7) {x = setbattlevalue(i,arrloadnumbers[i]);/*cout<<arrloadnumbers[i]<<endl;*/}
		else if (i == 7) {intLevelStart = arrloadnumbers[i];/*cout<<intLevelStart<<endl;*/}
	}
	int num = 7;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			num ++;
			d.setCell(x,y,arrloadnumbers[num]);
			//cout<<arrloadnumbers[num];
		}
	}
	//d.showDungeon();
	
	//Double check that all the values loaded are correct.
	ifstream checkfile("save.bif");
	for(int i = 0; i < 1608; i++) {checkfile>>arrloadnumbers[i];} //Rebuild the array.
	checkfile.close();
	int intCheckSum = 1;
	for (int i = 0; i < 8; i++)
	{
		if(i<7) {if (arrloadnumbers[i]==getbattlevalue(i)){intCheckSum++;}}
		else if (i == 7) {if (arrloadnumbers[i]==intMainLevel) {intCheckSum++;}}
	} 
	num = 7;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	cout<<endl<<endl<<intCheckSum;
	if(intCheckSum >= 1608) {return true;} //All of the saved values are correct if it equals 1608.
	else {return false;} //Some of the values are wrong, say that the save failed.
}


int main()
{

	cout << string(48, '\n');
	char chrPlayerMade = 'F';
	char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;
	bool blLoadSuccess = false;
	bool blOldSave = false;
	char chrSaveSuccess = 'N'; //N means that save has not been run.
	intLevelStart = 1;
	if (saveexists()) //Check if there is a save present.
	{
		blLoadSuccess = loadfunction(); //Try to load the save.
		if (blLoadSuccess) 
		{
			chrPlayerMade = 'T';
			blOldSave = true; 
		}
		else {cout<<endl<<"There is a save present, but game is unable to load it."<<endl<<"Save is possibly corrupted."<<endl<<endl<<endl;} //Load failed.
	}
	
	if(!blOldSave) //If it is not an old save show welcome message.
	{
		cout<<"Welcome to the World of Attacker"<<endl<<"Your objective is to go through 10 randomly generated dungeons."<<endl;
		cout<<"You are looking for the stairs down ( > ). While you are represented by †"<<endl;
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
		if (blOldSave && intMainLevel == intLevelStart) {d.playerfind(); d.showDungeon();} //If old save and the level of that save, just load old dungeon.
		else {Dungeon d;/*Generates dungeon.*/} //If it is not old game OR a different level of old game, make new dungeon.
		
		do
		{
			cout << string(50, '\n');
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			cout<<"Please enter a direction you would like to go ( N , E , S , W )."<<endl<<"Enter X to exit, C to check yourself, H to heal, or P to save."<<endl;
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
					system("pause");
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
				case 'F' :
					cout<<endl<<"Save failed!"<<endl;
					system("pause");
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
			}
			if (!(charExitFind=='S') && !(charPlayerDirection == 'C')) //If player did not save or did not check himself, see if player runs into monster.
			{
				if(rand() % 101 <= 10) //Random chance to encounter monster.
				{
					cout << string(50, '\n');
					charBattleEnding = startbattle(intMainLevel); //Starts battle.
					if(charBattleEnding == 'F') {return 0;} //Player lost battle.
				}
			}
		}while (charExitFind != 'T'); //Repeat until player finds exit.
	}
	cout << string(50, '\n');
	cout<<"You win!!";
	system("pause");
	return 0;
//End of main
}
