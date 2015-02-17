#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>

/*
Made By: Patrick J. Rye
Purpose: A game I made as an attempt to teach myself c++, just super basic, but going to try to keep improving it as my knowledge increases.
Current Revision: 2.1a
Change Log------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		------------------------------------------------------------------------------------------------------
?		 1.0a		Patrick Rye			-Original
?		 1.1a		Patrick Rye			-Nerffered Level 7+ Monsters
											-This changes makes 7-9 monster easier but level 10 is extremely difficult.
											-I will have to redo how the monster levels up completely, but not now.
										-Player Stat Upgrade boosted to 10 points
										-Player Now gets two stat upgrades every level
										-Fixed grammar and spelling mistakes
										
2/17/15  2.0a		Patrick Rye			-Added Change log
										-Moved the Level Up to its own function for easier modification
										-Moved the battle scene to its own function for easier modification
										-Added other monster base stats, will be used in a later revision for more variety
										-Fixed mistake that would allow player to heal above the amount they should be allowed to
										-Added second prompt for exiting game so player doesn't enter it by mistake.
										
2/17/15	2.1a		Patrick Rye			-Made function to convert lower case letters into upper case ones so that inputs are less case sensitive.
										-More grammar and spelling fixes
										-Added more comments to explain what is happening
										-Fixed Bug that allowed Monster health to go below 0, causing the battle to never end (oops kind of a big issue)
										-Changed Level up checker to a For loop rather than an if statement
										-Did a general code cleaner to make it look nicer.
										-Added Copyright License as I might put this on the internet and may as well.
										
										

*/

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


using namespace std;
int PlayerStats[5];
const int MonsterBaseStats[5] = {25,25,10,25,10}; //a base array for the monsters 
const int ZombieBaseStats[5] = {25,25,10,25,10};
const int SkeletonBaseStats[5] ={20,35,15,35,5};
const int WitchBaseStats[5] = {15,15,20,40,30};
const int ImpBaseStats[5] = {10,10,10,40,10};
//Will be changed later for more monsters but for now its just a constant
double PlayerHealth[2]; //An Array 0 is current health 1 is max
double MonsterHealth[2]; //An Array 0 is current health 1 is max
int MonsterStats[5];
int intLevel;
//cout <<
//cin>>

char CaseChecker(char chrCheck)
{
	/*
	This function takes a char and checks if it is one of the lower case letters of the alphabet.
	if it is it returns the upper case version of the letter. If it isn't it just returns what char it got.
	Made to allow lower case input that would be corrected, so its not a case sensitive.
	Should be able to modify to allow it to work on string but that will be latter.
	*/
	switch (chrCheck)
	{
		case 'a' :
			return 'A';
		case 'b' :
			return 'B';
		case 'c' :
			return 'C';
		case 'd' :
			return 'D';
		case 'e' :
			return 'E';
		case 'f' :
			return 'F';
		case 'g' :
			return 'G';
		case 'h' :
			return 'H';
		case 'i' :
			return 'I';
		case 'j' :
			return 'J';
		case 'k' :
			return 'K';
		case 'l' :
			return 'L';
		case 'm' :
			return 'M';
		case 'n' :
			return 'N';
		case 'o' :
			return 'O';
		case 'p' :
			return 'P';
		case 'q' :
			return 'Q';
		case 'r' :
			return 'R';
		case 's' :
			return 'S';
		case 't' :
			return 'T';
		case 'u' :
			return 'U';
		case 'v' :
			return 'V';
		case 'w' :
			return 'W';
		case 'x' :
			return 'X';
		case 'y' :
			return 'Y';
		case 'z' :
			return 'Z';
		default :
			return chrCheck;
	}
}
void LevelUpFunction()
{
	//Holds Function for levelling up
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
			cout<<endl<<"Invalid Choice";
			goto LevelUpChoice;
		}
		PlayerStats[intLevelUpChoice] = PlayerStats[intLevelUpChoice]+ 10;
	//End of for level up loop
	}
    LevelUpEnd:
    cout<<endl<<"Your Stats are now:"<<endl;
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
    if( intLevel != 1)
    {
		LevelUpFunction();
    }
    /*
	Recalculate all of the stats needed
    Update Monster Stats to new Level
	The reason for the changed level up method is that before the level 7 monster was unbeatable.
	This change nerfs monsters over level 7 until I can figure out a better way to scale the points.
	However, it makes level 10 monster really hard.
	*/
	if (intLevel < 7)
	{
		for (int i=0; i<5; i++)
		{
			MonsterStats[i] = floor(.5 * intLevel * MonsterBaseStats[i]);
			cout<<endl<<MonsterStats[i];
		}
	}
	else
	{
		for(int i=0; i<5; i++)
		{
			MonsterStats[i]=MonsterStats[i]+5;
			cout<<endl<<MonsterStats[i];
		}
	}
    //Recalculate Healths and re-heal them
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
    double douPlayerCritChance = ((PlayerStats[4])/10 /*+ rand() %100*/) * 4; 
    //The rand number is commented out because I want to test it a bit to ensure it is not broken
    double douMonsterCritChance =((MonsterStats[4])/10 /*+ rand() %100*/) * 4;
    double douMonsterDamageMuli = 1;
    double douPlayerDamageMuli = 1;
    int intPlayerDamage = 0;
    int intMonsterDamage = 0;
    //Check both Monster and Player to see if they get a crit this round
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.375;}
    //Check to see if Monster or Player dodges
    if(rand() % 101 <= douPlayerDodgeChance) {douMonsterDamageMuli = 0;} //Player dodges set Monster Damage to 0
    if(rand() % 101 <= douMonsterDodgeChance) {douPlayerDamageMuli = 0;} // Monster Dodges
    //Calculate Damage Done
    intPlayerDamage = floor(((2 * (intLevel/5) + 2) * ((10*intLevel)/MonsterStats[2]))*(PlayerStats[0]/8)*douPlayerDamageMuli)+5;
    intMonsterDamage = floor(((2 * (intLevel/5) + 2) * ((10*intLevel)/PlayerStats[2]))*(MonsterStats[0]/8)*douMonsterDamageMuli)+5;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"You are now fighting a Level "<<intLevel<<" Zombie!";
    cout<<endl<<"It has "<<MonsterHealth[0]<<" out of "<<MonsterHealth[1]<<" HP left"<<endl;
    cout<<endl<<endl<<"You have "<<PlayerHealth[0]<<" out of "<<PlayerHealth[1]<<" HP left."<<endl;
    PlayerChoice:
    cout<<endl<<"What you like to do?"<<endl<<"A = Attack, H = Heal, E = Exit, Q = Help"<<endl;
    cout<<"> ";
    cin>>chrPlayerBattleChoice;
    chrPlayerBattleChoice = CaseChecker(chrPlayerBattleChoice);
    switch(chrPlayerBattleChoice)
    {
        case 'A' :
            cout<<endl<<endl<<endl<<endl<<endl;
			
            if (intPlayerDamage != 0) //Check to see if monster manages to dodge the player
            {
                if(douPlayerDamageMuli > 1) {cout<<"You got a crit on the monster! ";}
                cout<<"You swing at the Monster for "<<intPlayerDamage<<".";
                MonsterHealth[0] = MonsterHealth[0] - intPlayerDamage;
            }
            else
            {
                cout<<"The monster dodges your attack!";
            }
			
            cout<<endl<<endl;
            if(intMonsterDamage !=0)
            {
                if(douMonsterDamageMuli > 1){cout<<"The Monster got a crit on you! ";}
                cout<<"The monster hit you for "<<intMonsterDamage<<".";
                PlayerHealth[0] = PlayerHealth[0] - intMonsterDamage;
            }
            else
            {
                cout<<"You dodged the monster's attack!";
            }
            cout<<endl<<endl;
            goto HealthCheck;
        case 'H' :
            //Code for Player Healing
            if(intMonsterDamage !=0)
            {
                if(douMonsterDamageMuli > 1){cout<<"The Monster got a crit on you! ";}
                cout<<"The monster hit you for "<<intMonsterDamage/2<<".";
                PlayerHealth[0] = PlayerHealth[0] - intMonsterDamage/2;
            }
            else
            {
                cout<<"You Dodged the monster's attack!";
            }
			
			if (PlayerHealth[0]+douPlayerHealAmount > PlayerHealth[1])
			{
				PlayerHealth[0]=PlayerHealth[1];
			}
			else
			{
				PlayerHealth[0] = PlayerHealth[0] + douPlayerHealAmount;
			}
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
            cout<<endl<<"Player Dodge chance: "<<douPlayerDodgeChance;
            cout<<endl<<"Monster dodge chance: "<<douMonsterDodgeChance;
            cout<<endl<<"Player Muli: "<<douPlayerDamageMuli;
            cout<<endl<<"Monster Muli: "<<douMonsterDamageMuli;
            cout<<endl<<"Player Damage: "<<intPlayerDamage;
            cout<<endl<<"Monster Damage: "<<intMonsterDamage;
            goto PlayerChoice;
        case 'K' : //debug code "kills" the current monster
            return 'T';
        case 'E' : //exits game
			cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All process will be lost"<<endl<<"Y or N"<<endl<<"> ";
			cin>>chrPlayerBattleChoice;
			chrPlayerBattleChoice = CaseChecker(chrPlayerBattleChoice);
			switch (chrPlayerBattleChoice)
			{
				case 'Y' :
					return 'F';
				default :
					goto PlayerChoice;
			}
        default :
            cout<<endl<<"Invalid Choice, try again";
            goto PlayerChoice;
		    //Check if Player Dead
    }
	HealthCheck:
	if (PlayerHealth[0] <= 0)
    {
		//Player lost
		return 'F';
        //system("cls");
    }
	
	if (MonsterHealth[0] <= 0)
	{
		//Monster is Dead but not player, they win
		return 'T';
		//system("cls");
	}
		//neither player to monster is dead go back to choice again
		goto BattleGoto;
//End of Battle Scene Function
}
int main()
{
int intStr = 0;
int intCons =0;
int intDef = 0;
int intDex =0;
int intLuk = 0;
cout<<"Welcome to the World of Attacker"<<endl<<"You objective is to kill 10 monsters to win."<<endl;
cout<<"Each level is harder than the last do you have what it takes to win?"<<endl;
cout<<"Good Luck!"<<endl<<endl<<endl<<endl;
PickStats:
cout<<"In this game there are five stats that effect different elements of the game.";
cout<<endl<<"Strength (STR) - your attack strength"<<endl;
cout<<"Constitution (CONS) - your health."<<endl;
cout<<"Dexterity (DEX) - Effects if you move first and if you dodge."<<endl;
cout<<"Defence (DEF) - Effects how much damage you take."<<endl;
cout<<"Luck (LUK) - The Random chance things will go your way with dodges and crits."<<endl;
int intSkillPointsLeft = 100;
cout<<"You have "<< intSkillPointsLeft <<" points to spend however you desire on these five stats, however each stat must have at least 1 point"<<endl;

do 
{
    cout<<endl<<"Enter your stat for your Strength: ";
    cin>> intStr;
}while (intStr <=0);
intSkillPointsLeft = intSkillPointsLeft - intStr;
//A check to see if they put too many points into a stat
//Since each stat must have at least 1 point
if( intSkillPointsLeft < 4 )
{
    cout<<"You used too many points"<<endl;
    goto PickStats;
}

cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend";
do 
{
    cout<<endl<<"Enter your stat for your Constitution: ";
    cin>> intCons;
}while (intCons <=0);
intSkillPointsLeft = intSkillPointsLeft - intCons;
if(intSkillPointsLeft < 3)
{
    cout<<"You used too many points"<<endl;
    goto PickStats;
}
cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend";
do 
{
    cout<<endl<<"Enter your stat for your Defence: ";
    cin>> intDef;
}while (intDef <=0);
intSkillPointsLeft = intSkillPointsLeft - intDef;
if(intSkillPointsLeft < 2)
{
    cout<<"You used too many points"<<endl;
    goto PickStats;
}
cout<<endl<<"You have "<< intSkillPointsLeft <<" Points Left to spend";
do 
{
    cout<<endl<<"Enter your stat for your Dexterity: ";
    cin>> intDex;
}while (intDex <=0);
intSkillPointsLeft = intSkillPointsLeft - intDef;
if(intSkillPointsLeft < 1)
{
    cout<<"You used too many points"<<endl;
    goto PickStats;
}

cout<<endl<< intSkillPointsLeft <<" points are placed in Luck"<<endl;
intLuk = intSkillPointsLeft;
//Something to clear the screen but doesn't work here
//system("clear");

char strAnswer;
cout<<endl<<endl<<endl<<endl<<endl;
cout<<"Your current stats are as follows:"<<endl<<"Strength: "<<intStr<<endl;
cout<<"Constitution: "<<intCons<<endl;
cout<<"Defence: "<<intDef<<endl;
cout<<"Dexterity: "<<intDex<<endl;
cout<<"Luck: "<<intLuk<<endl;
cout<<"Do you agree with these stats? Y or N"<<endl;

AgreeWithStats:

    cout<<"Y or N? ";
    cin>>strAnswer;
	strAnswer = CaseChecker(strAnswer);
    switch(strAnswer)
    {
    case 'Y' :
        //Add something here
        goto RestofGame;
    case 'N' :
        goto PickStats;
        //Fix this later so you can go back
    default :
        cout<<endl<<"Invalid Answer"<<endl;
        goto AgreeWithStats;
    }

//Make an Array of the Player's Stats for easier referencing of them later
RestofGame:
PlayerStats[0]=intStr;
PlayerStats[1]=intCons;
PlayerStats[2]=intDef;
PlayerStats[3]=intDex;
PlayerStats[4]=intLuk;

//system("cls");
char charBattleSceneEnding;
for(intLevel = 1; intLevel <= 10; intLevel++)
{
    charBattleSceneEnding = BattleScene();
	switch(charBattleSceneEnding)
	{
		case 'T' :
			    cout<<"You beat the Monster!"<<endl<<"Now advancing to Level: "<<intLevel + 1;
                continue;
		case 'F' : 
			    cout<<"You lost"<<endl<<"You defeated "<<intLevel - 1 <<" monsters.";
                cout<<endl<<"Press enter to close this game and try again!";
                cin>>PlayerHealth[0]; //just some random input to "pause" the game so they can read the message before it quits
                return 0;
		default :
			cout<<endl<<"An Error has occurred in the code. The game will exit.";
			cin>>PlayerHealth[0]; //random Input to allow system "Pause"
	}
    

//End of For Levels    
}
//End of Main
cout<<endl<<endl<<endl<<endl<<"You Win";
return 0;
}
