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
Current Revision: 3.0a
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
2/17/15  2.0a		Patrick Rye			-Added change log (everything before this is just a guess and what I remember).
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
										-Made player initialize() as a separate function that initializes the player. 
											-Made it its own function for later revisions, which may include a saving function.
										-More grammar and spelling fixes (I make a lot of these mistakes).
										-Added random monster function, which changes which monster you fight each battle.
=============================================================================================================================================================											
2/17/15 2.3a		Patrick Rye			-Implemented multiple types of monsters.
										-Went back to old method of monster levelling up due to the new types breaking the other method.
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
										-Moved License to be first, followed by Change Log, and then the code.
											-This way the license is the first thing seen, and the code isn't split up by the change log.
										-Even more gosh dang spelling and grammar fixes. Focused more on comments and the change log then anything.
										-Cleaned up old code some more.
										-Added function to lower case a word.
										-Added function to lower case a word then capitalize the first letter.
											-For grammatical purposes.
=============================================================================================================================================================
*/
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <locale>
using namespace std;

/*
For Stat Arrays 
0 = STR
1 = CONS
2 = DEF
3 = DEX
4 = LUK
*/
//Make all the global variables that I need
int PlayerStats[5];
int MonsterBaseStats[5] = {25,25,10,25,10}; //A base array for the monsters 
const int ZombieBaseStats[5] = {25,25,10,25,10};
const int SkeletonBaseStats[5] = {20,35,15,35,6};
const int WitchBaseStats[5] = {15,15,20,40,30};
const int ImpBaseStats[5] = {10,10,10,40,10};
const string MonsterNames[4] = {"Zombie","Skeleton","Witch","Imp"};
const string PosMonsterModifiers[7] = {"Strong","Large","Massive","Fast","Lucky","Powerful","Solid"};
const string NegMonsterModifiers[5] = {"Weak","Small","Tiny","Slow","Unlucky"};
string MonsterName;
string MonsterModifier;
double PlayerHealth[2]; //An array 0 is current health 1 is max
double MonsterHealth[2]; //An array 0 is current health 1 is max
int MonsterStats[5];
int intLevel;
//cout <<
//cin>>

std::string ConvertToUpper(std::string& str)
{
	//Thanks to codekiddy for his post at http://www.cplusplus.com/forum/beginner/70692/
	std::locale settings;
	std::string converted;
	for(short i = 0; i < str.size(); ++i)
		converted += (toupper(str[i], settings));
	return converted;
}

string ConvertToLower(string& str)
{
	locale settings;
	string converted;
	for(short i = 0; i < str.size(); ++i)
		converted += (tolower(str[i], settings));
	return converted;
}

string ProperCase(string& str)
{
	locale settings;
	string converted;
	converted+= (toupper(str[1], settings));
	for(short i = 1; i < str.size(); ++i)
		converted += (tolower(str[i], settings));
	return converted;
}

char CharConvertToUpper(char chrCheck)
{
	//Modified version of the String convert to upper function to work on char
	locale settings;
	char converted;
	converted = (toupper(chrCheck, settings));
	return converted;
}

void LevelUpFunction()
{
	//Holds function for levelling up
	int intPlayerStatUpgradeAmount;
	intPlayerStatUpgradeAmount = 0; //Keeps track of how many times the player levels up a stat, player only gets two
		
	StatUpgrade:
	for (int intPlayerStatUpgradeAmount=1; intPlayerStatUpgradeAmount<=2; intPlayerStatUpgradeAmount++)
	{
		string strLevelUpChoice;
		cout<<endl<<"LEVEL UP!"<<endl<<"You can put 10 points in two stats, which ones would you like?"<<endl;
		cout<<"STR: "<<PlayerStats[0]<<endl<<"CONS: "<<PlayerStats[1]<<endl;
		cout<<"DEF: "<<PlayerStats[2]<<endl<<"DEX: "<<PlayerStats[3]<<endl;
		cout<<"LUK: "<<PlayerStats[4]<<endl<<"NONE to not use upgrade";
		LevelUpChoice:
		cout<<endl<<"> ";
		cin>>strLevelUpChoice;
		strLevelUpChoice = ConvertToUpper(strLevelUpChoice);
		int intLevelUpChoice;
		if (strLevelUpChoice == "STR")
			intLevelUpChoice = 0;
		else if (strLevelUpChoice == "CONS")
			intLevelUpChoice = 1;
		else if (strLevelUpChoice == "DEF")
			intLevelUpChoice = 2;
		else if (strLevelUpChoice == "DEX")
			intLevelUpChoice = 3;
		else if (strLevelUpChoice == "LUK")
			intLevelUpChoice = 4;
		else if (strLevelUpChoice == "NONE")
			continue; //Do next for loop if player does not want to use a stat upgrade.
		else 
		{
			cout<<endl<<"Invalid choice, try again.";
			goto LevelUpChoice;
		}
		PlayerStats[intLevelUpChoice] = PlayerStats[intLevelUpChoice]+ 10;
	//End of for level up loop
	}
    LevelUpEnd:
    cout<<endl<<"Your stats are now:"<<endl;
    cout<<"STR: "<<PlayerStats[0]<<endl<<"CONS: "<<PlayerStats[1]<<endl;
    cout<<"DEF: "<<PlayerStats[2]<<endl<<"DEX: "<<PlayerStats[3]<<endl;
    cout<<"LUK: "<<PlayerStats[4]<<endl;
//End of Level up function
}

char BattleScene() 
{
	
	/*
	Function that holds the battle scene
	Returns a T, F or E,
	T stands for True meaning that they won
	F stands for false meaning that they lost
	E stands for error meaning something went horribly wrong
	*/
	
	//system("cls");
    double douPlayerHealAmount;
	char chrPlayerBattleChoice;
    //Do a level up if not level one
    if( intLevel != 1) { LevelUpFunction();}
    /*
	Recalculate all of the stats needed
    Update monster stats to new Level
	*/
	for (int i=0; i<5; i++) {MonsterStats[i] = floor(.5 * intLevel * MonsterBaseStats[i]);/*cout<<endl<<MonsterStats[i];*/ /*Debugging line*/}
    //Recalculate healths and re-heal them
    PlayerHealth[1] = floor((23*((5.25+0.5625*intLevel+0.00375*pow(intLevel,2))+(1+0.066*intLevel)*(PlayerStats[1]/16))));
    PlayerHealth[0] = PlayerHealth[1];
    MonsterHealth[1] = floor((23*((5.25+0.5625*intLevel+0.00375*pow(intLevel,2))+(1+0.066*intLevel)*(MonsterStats[1]/16))/3));
    MonsterHealth[0] = MonsterHealth[1];
    //Recalculate amount Player heals for
    douPlayerHealAmount = floor(PlayerHealth[1]/10);
    //system("cls");
    BattleGoto:
    //system("cls");
    double douPlayerDodgeChance = ((PlayerStats[3]/4 + PlayerStats[4]/20)/25) * 100;
    double douMonsterDodgeChance = ((MonsterStats[3]/4 + MonsterStats[4]/20)/25) * 100;
    double douPlayerCritChance = ((PlayerStats[4])/10 + rand() %5) * 4; 
    double douMonsterCritChance =((MonsterStats[4])/10 + rand() %5) * 4;
    double douMonsterDamageMuli = 1;
    double douPlayerDamageMuli = 1;
    int intPlayerDamage = 0;
    int intMonsterDamage = 0;
    //Check both monster and Player to see if they get a crit this round
	//Rand() % 101 generates a random number between 0 and 100.
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.375;}
    //Check to see if Monster or Player dodges
    if(rand() % 101 <= douPlayerDodgeChance) {douMonsterDamageMuli = 0;} //Player dodges set Monster Damage to 0
    if(rand() % 101 <= douMonsterDodgeChance) {douPlayerDamageMuli = 0;} // Monster Dodges
    //Calculate Damage Done
    intPlayerDamage = floor(((2 * (intLevel/5) + 2) * ((10*intLevel)/MonsterStats[2]))*(PlayerStats[0]/8)*douPlayerDamageMuli)+5;
    intMonsterDamage = floor(((2 * (intLevel/5) + 2) * ((10*intLevel)/PlayerStats[2]))*(MonsterStats[0]/8)*douMonsterDamageMuli)+5;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"You are now fighting a level "<<intLevel<<" "<<MonsterName<<"!";
    cout<<endl<<"It has "<<MonsterHealth[0]<<" out of "<<MonsterHealth[1]<<" HP left"<<endl;
    cout<<endl<<endl<<"You have "<<PlayerHealth[0]<<" out of "<<PlayerHealth[1]<<" HP left."<<endl;
    PlayerChoice:
    cout<<endl<<"What you like to do?"<<endl<<"A = Attack, H = Heal, E = Exit, Q = Help"<<endl;
    cout<<"> ";
    cin>>chrPlayerBattleChoice;
    chrPlayerBattleChoice = CharConvertToUpper(chrPlayerBattleChoice);
    switch(chrPlayerBattleChoice)
    {
        case 'A' :
            cout<<endl<<endl<<endl<<endl<<endl;
			
            if (intPlayerDamage != 0) //Check to see if monster manages to dodge the player
            {
                if(douPlayerDamageMuli > 1) {cout<<"You got a crit on the "<<MonsterName<<"! ";}
                cout<<"You swing at the "<<MonsterName<<" for "<<intPlayerDamage<<".";
                MonsterHealth[0] = MonsterHealth[0] - intPlayerDamage;
            }
            else { cout<<"The "<<MonsterName<<" dodges your attack!"; }
            
            cout<<endl<<endl;
            if(intMonsterDamage !=0)
            {
                if(douMonsterDamageMuli > 1){cout<<"The "<<MonsterName<<" got a crit on you! ";}
                cout<<"The "<<MonsterName<<" hits you for "<<intMonsterDamage<<".";
                PlayerHealth[0] = PlayerHealth[0] - intMonsterDamage;
            }
            else {cout<<"You dodged the "<<MonsterName<<"'s attack!";}

            cout<<endl<<endl;
            goto HealthCheck;
        case 'H' :
            //Code for Player Healing
            if(intMonsterDamage !=0)
            {
                if(douMonsterDamageMuli > 1){cout<<"The "<<MonsterName<<" got a crit on you! ";}
                cout<<"The "<<MonsterName<<" hit you for "<<intMonsterDamage/2<<".";
                PlayerHealth[0] = PlayerHealth[0] - intMonsterDamage/2;
            }
            else {cout<<"You dodged the "<<MonsterName<<"'s attack!";}

			if (PlayerHealth[0]+douPlayerHealAmount > PlayerHealth[1]) {PlayerHealth[0]=PlayerHealth[1];}
			else {PlayerHealth[0] = PlayerHealth[0] + douPlayerHealAmount;}
            cout<<endl<<"You heal yourself for "<<douPlayerHealAmount<<" HP.";
            goto HealthCheck;
        case 'Q' :
            cout<<endl<<"Attacking means that you attack the monster and you both deal damage to each other assuming no one dodges";
            cout<<endl<<"Healing means that you heal for 10% of your maximum health, "<< douPlayerHealAmount<<" HP. While healing you also take less damage.";
			cout<<endl<<"Exit will leave the game and lose all progress.";
            cout<<endl<<"Help brings up this menu"<<endl;
            goto PlayerChoice;
        case 'D' : //debug code reveal some values
            cout<<endl<<"Player crit chance: "<<douPlayerCritChance;
            cout<<endl<<"Monster crit chance: "<<douMonsterCritChance;
            cout<<endl<<"Player dodge chance: "<<douPlayerDodgeChance;
            cout<<endl<<"Monster dodge chance: "<<douMonsterDodgeChance;
            cout<<endl<<"Player muli: "<<douPlayerDamageMuli;
            cout<<endl<<"Monster muli: "<<douMonsterDamageMuli;
            cout<<endl<<"Player damage: "<<intPlayerDamage;
            cout<<endl<<"Monster damage: "<<intMonsterDamage;
            goto PlayerChoice;
        case 'K' : //debug code "kills" the current monster
            return 'T';
        case 'E' : //exits game
			cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All progress will be lost"<<endl<<"Y or N"<<endl<<"> ";
			cin>>chrPlayerBattleChoice;
			chrPlayerBattleChoice = CharConvertToUpper(chrPlayerBattleChoice);
			switch (chrPlayerBattleChoice)
			{
				case 'Y' :
					return 'F';
				default :
					goto PlayerChoice;
			}
        default :
            cout<<endl<<"Invalid choice, try again";
            goto PlayerChoice;
		    //Check if Player Dead
    }
	HealthCheck:
	if (PlayerHealth[0] <= 0) {return 'F';}	
	if (MonsterHealth[0] <= 0) {return 'T';}
	//Neither player or monster is dead; go back to choice again
	goto BattleGoto;
//End of battle scene function
}

char PlayerInitialize()
{
//Code for making a character, in its own function for later features.
int intStr = 0;
int intCons = 0;
int intDef = 0;
int intDex = 0;
int intLuk = 0;

cout<<"In this game there are five stats that effect different elements of the game.";
cout<<endl<<"Strength (STR) - your attack strength"<<endl;
cout<<"Constitution (CONS) - your health."<<endl;
cout<<"Dexterity (DEX) - Effects if you dodge."<<endl;
cout<<"Defence (DEF) - Effects how much damage you take."<<endl;
cout<<"Luck (LUK) - The random chance things will go your way, with dodges and crits."<<endl;
int intSkillPointsLeft = 100;
cout<<"You have "<< intSkillPointsLeft <<" points to spend however you desire on these five stats, however each stat must have at least 1 point"<<endl;

do 
{
    cout<<endl<<"Enter your stat for your STRENGTH: ";
    cin>> intStr;
}while (intStr <=0);
intSkillPointsLeft = intSkillPointsLeft - intStr;
//A check to see if they put too many points into a stat
//Since each stat must have at least 1 point
if( intSkillPointsLeft < 4 )
{
    cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
    return 'F';
}

cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend.";
do 
{
    cout<<endl<<"Enter your stat for your CONSTITUTION: ";
    cin>> intCons;
}while (intCons <=0);
intSkillPointsLeft = intSkillPointsLeft - intCons;
if(intSkillPointsLeft < 3)
{
    cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
    return 'F';
}
cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend";
do 
{
    cout<<endl<<"Enter your stat for your DEFENCE: ";
    cin>> intDef;
}while (intDef <=0);
intSkillPointsLeft = intSkillPointsLeft - intDef;
if(intSkillPointsLeft < 2)
{
    cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
    return 'F';
}
cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend";
do 
{
    cout<<endl<<"Enter your stat for your DEXTERITY: ";
    cin>> intDex;
}while (intDex <=0);
intSkillPointsLeft = intSkillPointsLeft - intDex;
if(intSkillPointsLeft < 1)
{
    cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
    return 'F';
}

cout<<endl<< intSkillPointsLeft <<" points are placed in LUCK."<<endl;
intLuk = intSkillPointsLeft;
/*
Something to clear the screen but doesn't work here
This is because I was using Coding Grounds On-line C++ complier to do tests,
But it doesn't allow system commands to be run. 
I delete these comments dashes when I compile it with Cygwin, but otherwise I keep them commented out.
*/
//system("cls");

char strAnswer;
cout<<endl<<endl<<endl<<endl<<endl;
AgreeWithStats:
cout<<"Your current stats are as follows:"<<endl;
cout<<"Strength: "<<intStr<<endl;
cout<<"Constitution: "<<intCons<<endl;
cout<<"Defence: "<<intDef<<endl;
cout<<"Dexterity: "<<intDex<<endl;
cout<<"Luck: "<<intLuk<<endl;
cout<<"Do you agree with these stats? Y or N"<<endl;

    cout<<"Y or N? > ";
    cin>>strAnswer;
	strAnswer = CharConvertToUpper(strAnswer);
    switch(strAnswer)
    {
    case 'Y' :
        goto RestofGame;
    case 'N' :
        return 'F';
    default :
        cout<<endl<<"Invalid choice, try again."<<endl;
        goto AgreeWithStats;
    }

//Make an Array of the Player's Stats for easier referencing of them later
RestofGame:
PlayerStats[0]=intStr;
PlayerStats[1]=intCons;
PlayerStats[2]=intDef;
PlayerStats[3]=intDex;
PlayerStats[4]=intLuk;
//End of Player Initialize
return 'T';
}

void RandomMonster()
{
	//Generates a number 0 - 4 representing the location of a monster in the Monster Name array
	//It then places the name and base stats of the monster appropriately. 
	int intRandomMonsterNumber;
	
	intRandomMonsterNumber = rand() % 4;
	MonsterName = MonsterNames[intRandomMonsterNumber];
	if (MonsterName == "Witch") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=WitchBaseStats[i];}}
	else if (MonsterName == "Imp") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=ImpBaseStats[i];}}
	else if (MonsterName == "Skeleton") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=SkeletonBaseStats[i];}}
	else if (MonsterName == "Zombie") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=ZombieBaseStats[i];}}
	else
	{
		//In the event that the name wasn't found default to zombie
		MonsterName = "Zombie";
		for (int i=0; i <=4; i++) {MonsterBaseStats[i]=ZombieBaseStats[i];}
	}
}

void RandomMonsterModifier()
{
	//Adds a Random Modifier onto a monster it can be a boost of stats or reduced
	//Varies a bit with a player's LUK
	//I call a LUK of 20 average, therefore it should have 
	MonsterModifier = "";
	//Two random numbers that are added onto player and monster stats
	int intMRandomNumber;
	int intPRandomNumber;
	int intRandomNumber;
	int intRandomModifier;
	intMRandomNumber = rand() % 20;
	intPRandomNumber = rand() % 20;
	intRandomNumber = rand() % 100 + 1;
	
	if (MonsterStats[4] + intMRandomNumber > PlayerStats[4]+intPRandomNumber)
	{
		//Monster has better chance of spawning with positive effect
		if (intRandomNumber < 60){MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %7;
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {MonsterBaseStats[0]=MonsterBaseStats[0]+5;}
			else if (MonsterModifier == "Large") {MonsterBaseStats[1]=MonsterBaseStats[1]+5;}
			else if (MonsterModifier == "Massive")
			{
				MonsterBaseStats[1]=MonsterBaseStats[1]+5;
				MonsterBaseStats[0]=MonsterBaseStats[0]+5;
				MonsterBaseStats[3]=MonsterBaseStats[0]-5;
			}
			else if (MonsterModifier == "Fast") {MonsterBaseStats[3]=MonsterBaseStats[3]+5;}
			else if (MonsterModifier == "Lucky") {MonsterBaseStats[4]=MonsterBaseStats[4]+5;}
			else if (MonsterModifier == "Powerful") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=MonsterBaseStats[i]+5;}}
			else if (MonsterModifier == "Solid") {MonsterBaseStats[1]=MonsterBaseStats[1]+5;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %4;
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {MonsterBaseStats[0]=MonsterBaseStats[0]-5;}
			else if (MonsterModifier == "Small") {MonsterBaseStats[1]=MonsterBaseStats[1]-5;}
			else if (MonsterModifier == "Tiny") {MonsterBaseStats[2]=MonsterBaseStats[2]-5;}
			else if (MonsterModifier == "Slow") {MonsterBaseStats[3]=MonsterBaseStats[3]-5;}
			else if (MonsterModifier == "Unlucky") {MonsterBaseStats[4]=MonsterBaseStats[4]-5;}
			else {MonsterModifier="";}
		}
		else {/*This shouldn't happen but just in case.*/MonsterModifier="";}
	}
	else if (MonsterStats[4] + intMRandomNumber < PlayerStats[4]+intPRandomNumber)
	{
		//Monster has better chance of spawning with positive effect
		if (intRandomNumber < 60) {MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %4;
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {MonsterBaseStats[0]=MonsterBaseStats[0]-5;}
			else if (MonsterModifier == "Small") {MonsterBaseStats[1]=MonsterBaseStats[1]-5;}
			else if (MonsterModifier == "Tiny") {MonsterBaseStats[2]=MonsterBaseStats[2]-5;}
			else if (MonsterModifier == "Slow") {MonsterBaseStats[3]=MonsterBaseStats[3]-5;}
			else if (MonsterModifier == "Unlucky") {MonsterBaseStats[4]=MonsterBaseStats[4]-5;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %7;
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {MonsterBaseStats[0]=MonsterBaseStats[0]+5;}
			else if (MonsterModifier == "Large") {MonsterBaseStats[1]=MonsterBaseStats[1]+5;}
			else if (MonsterModifier == "Massive")
			{
				MonsterBaseStats[1]=MonsterBaseStats[1]+5;
				MonsterBaseStats[0]=MonsterBaseStats[0]+5;
				MonsterBaseStats[3]=MonsterBaseStats[0]-5;
			}
			else if (MonsterModifier == "Fast") {MonsterBaseStats[3]=MonsterBaseStats[3]+5;}
			else if (MonsterModifier == "Lucky") {MonsterBaseStats[4]=MonsterBaseStats[4]+5;}
			else if (MonsterModifier == "Powerful") {for (int i=0; i <=4; i++) {MonsterBaseStats[i]=MonsterBaseStats[i]+5;}}
			else if (MonsterModifier == "Solid") {MonsterBaseStats[1]=MonsterBaseStats[1]+5;}
			else {MonsterModifier="";}
		}
		else {/*This shouldn't happen but just in case.*/MonsterModifier="";}
	}
	else {/*The two stats are equal therefore the Monster is a normal monster without any other checks*/MonsterModifier = "";}
//End of random monster modifier	
}

int main()
{
char chrPlayerMade = 'F';
cout<<"Welcome to the World of Attacker"<<endl<<"Your objective is to kill 10 monsters to win."<<endl;
cout<<"Each level is harder than the last do you have what it takes to win?"<<endl;
cout<<"Good luck!"<<endl<<endl<<endl<<endl;

do 
{
    chrPlayerMade = PlayerInitialize();
	//repeat the function to make player until we get a value saying that the player has been made.
}while (chrPlayerMade != 'T');

//system("cls");

char charBattleSceneEnding;
for(intLevel = 1; intLevel <= 10; intLevel++)
{
	RandomMonster();
	RandomMonsterModifier();
	if (MonsterModifier != "") {MonsterName = ConvertToLower(MonsterModifier) + " " + ConvertToLower(MonsterName);}
	else {MonsterName = ConvertToLower(MonsterName);}
    charBattleSceneEnding = BattleScene();
	switch(charBattleSceneEnding)
	{
		case 'T' :
			    cout<<"You beat the "<<MonsterName<<endl<<"Now advancing to level: "<<intLevel + 1;
                continue;
		case 'F' : 
			    cout<<"You lost..."<<endl<<"You defeated "<<intLevel - 1 <<" monsters.";
                cout<<endl<<"Press enter to close this game and try again!";
                cin>>PlayerHealth[0]; //just some random input to "pause" the game so they can read the message before it quits
                return 0;
		default :
			cout<<endl<<"An error has occurred in the code. Sorry :( The game will exit.";
			cin>>PlayerHealth[0]; //random input to allow system "Pause"
	}  
}
cout<<endl<<endl<<endl<<endl<<"You win!!";
cin>>PlayerHealth[1];
return 0;
//End of main
}
