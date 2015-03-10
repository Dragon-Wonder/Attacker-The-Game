#ifndef _BATTLE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BATTLE_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold all the functions related to battling, levelling up and player stats.
Current Revision: 3.1.1
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2015/02/23	1.0			Patrick Rye		-Original
=============================================================================================================================================================
2015/02/24	1.1			Patrick Rye		-Changed system("cls") to cout << string(50, '\n');
=============================================================================================================================================================
2015/02/24	1.2			Patrick Rye		-Moved level up to happen when you change levels.
										-Fixed bug that would cause endless loop is you entered non integer numbers for starting stats.
											-Bug has been there since the start I just didn't know how to fix it till now.
										-Fixed bug where player could enter values below 1 for stats.
										-Fixed bug where player could enter decimal places for stats.
=============================================================================================================================================================
2015/02/25	1.3			Patrick Rye		-Improved look of the code by adding separators.
										-Reduced chance for dodges and crits (cut by half).
										-Grammar and spelling fixes. (Whelp back to the old grim I guess).
										-Added breaks to case switches (kinda surprised it worked before).
=============================================================================================================================================================
2015/02/26	1.4			Patrick Rye		-General code improvement.
										-Fixed losing message to better represent changes to objectives.
										-Grammar and spelling fixes.
=============================================================================================================================================================
2015/02/27	1.5			Patrick Rye		-Added function that saves needed values.
										-Changed health arrays from doubles to integers.
=============================================================================================================================================================
2015/03/02	1.6			Patrick Rye		-Changed name of some functions to better reflect what they do.
										-Changed health to carry over between battles.
										-Moved health calculating to its own function.
										-Moved damage calculating to its own function.
=============================================================================================================================================================
2015/03/02	1.7			Patrick Rye		-Improved code.
										-Grammar and spelling fixes.
										-Moved dodge check to its own function.
=============================================================================================================================================================
2015/03/03	2.0			Patrick Rye		-Grammar and spelling fixes.
										-Initialized certain variables with values.
										-Nerffered monster health, now 1/3 of a player's with the same stats.
										-Added debug mode.
										-Floored damage done when healing.
=============================================================================================================================================================
2015/03/04	2.1			Patrick Rye		-Added new monster, Golem.
										-Changed monster base stats so that they total to 100.
										-Floored monster health.
=============================================================================================================================================================
2015/03/04	2.2			Patrick Rye		-Change battle menu a bit.
										-Exit is now 'X' instead of 'E'.
										-Changed help to 'P' instead of 'Q'
										-Added function which can randomly return a string giving a description of the state of the monster based on current health.
										-During battle the status of the monster is replaced with description.
=============================================================================================================================================================
2015/03/06	2.3			Patrick Rye		-General code improvement.
										-Changed change log date format from MM/DD/YY to YYYY/MM/DD because I like it better.
										-Changed battles so that the monster or player will apply damage first, depending on dexterity.
										-Added option to run away from battle.
										-Moved player attacking and monster attacking to their own functions.
										-Changed battle start to return a boolean.
=============================================================================================================================================================
2015/03/06	2.3.1		Patrick Rye		-Changed system("pause") to getchar();
										-Added more pauses.
=============================================================================================================================================================
2015/03/06	3.0			Patrick Rye		-Added chance for stun.
										-Redid monster levelling.
										-Redid health calculation.
										-Redid damage calculation.
										-Added some variability to attack damage.
=============================================================================================================================================================
2015/03/09	3.0.1		Patrick Rye		-Changed some text to better reflect certain changes.
										-The less health something has the less damage it will do.
										-Nerffered attack damage a bit.
=============================================================================================================================================================
2015/03/09	3.1			Patrick Rye		-Made structures of entities
=============================================================================================================================================================
2015/03/09	3.1.1		Patrick Rye		-Added status effects (do nothing at the moment).
										-Added functions to get and set monster values.
										-Moved enums to basic.h
=============================================================================================================================================================						
*/
/*********************************************************************************************************/
struct entity {
	string name;
	int currhealth;
	int maxhealth;
	int str;
	int cons;
	int def;
	int dex;
	int luk;
	int status;
};
/*********************************************************************************************************/
/*A quick note on the base stats, a stat cannot be lower than 6, as a modifier might reduce the value by 5 points.
  The base stat point should also add up to be 100. */
const entity monsters[5] = {{"Zombie",0,0,25,25,10,25,15,effectNone},
							{"Skeleton",0,0,35,18,6,25,6,effectNone},
							{"Witch",0,0,15,15,20,20,30,effectNone},
							{"Imp",0,0,15,15,15,40,15,effectNone},
							{"Golem",0,0,20,34,34,6,6,effectNone}};
entity monster = {"Generic",0,0,20,20,20,20,20,effectNone};
entity player = {"Player",0,0,20,20,20,20,20,effectNone};
/*********************************************************************************************************/
const string MonsterNames[5] = {"Zombie","Skeleton","Witch","Imp","Golem"};
const string PosMonsterModifiers[6] = {"Strong","Large","Massive","Fast","Lucky","Solid"};
const string NegMonsterModifiers[5] = {"Weak","Small","Tiny","Slow","Unlucky"};
/*********************************************************************************************************/
string MonsterModifier;
/*********************************************************************************************************/
int intBattleLevel = 1;
bool blBattleDebugMode = false;
/*********************************************************************************************************/
void SetBattleDebugMode(bool isDebug) {blBattleDebugMode = isDebug;}
/*********************************************************************************************************/

bool StunCheck(int intAttackerLuck, int intDefenderLuck)
{
	if (intDefenderLuck < intAttackerLuck) {if(rand()% 101 < (intAttackerLuck - intDefenderLuck) / 3) {return true;}}
	return false;
}

float DamageHealthPercent(int CurrentHealth, int MaximumHealth)
{
	/*Function that returns a percentage value that will be multiplied by the damage.
	  The value will vary with health so that the less health something has
	  The less damage it will do.
	  The max value it return is about 1.01 or something similar, the min value
	  is about 0.64 */
	
	float HealthPercent = CurrentHealth / MaximumHealth;
	float TempValue = 0;
	TempValue -= 0.8981 * pow(HealthPercent, 3);
	TempValue += 1.297 * pow(HealthPercent, 2);
	TempValue -= 0.0358 * HealthPercent;
	TempValue += 0.64;
	return TempValue;
}

string HitName()
{
	/*Outputs a string that represents an attack,
	   for example rather than just "hit" over and over,
	   you could get "stabbed" "hit"*/
	const string HitStringArray[5] = {"hit","stabbed","cut","slashed","damaged"};
	string TempString;
	TempString = HitStringArray[rand() % 5];
	if (TempString != "") {return TempString;}
	return "hit";
}

bool MonsterAttack(int MonsterDamage, double MonsterMuli, bool ishealing)
{
	//Holds stuff for when monster attacks.
	//Only returns true if player died.
	//Is in its own function so I can call it a couple of different places.
	cout<<endl;
	MonsterDamage = floor(MonsterDamage * DamageHealthPercent(monster.currhealth,monster.maxhealth)); //Reduce damage based on health.
	if (ishealing) {floor(MonsterDamage /= 2);} //if player is healing reduce damage.
	if (MonsterDamage != 0)
	{
		if (MonsterMuli > 1){cout<<"The "<<monster.name<<" got a crit on you! ";}
		cout<<"The "<<monster.name<<" hit you for "<<MonsterDamage<<".";
	}
	else {cout<<"You dodged the "<<monster.name<<"'s attack!";}
	player.currhealth -= MonsterDamage;
	if (player.currhealth <= 0) {return true;}
	return false;
}

bool PlayerAttack(int PlayerDamage, double PlayerMuli)
{
	//Holds stuff for when player attacks.
	//Only returns true if monster died.
	//Is in its own function so I can call it a couple of different places.
	cout<<endl;
	PlayerDamage = floor(PlayerDamage * DamageHealthPercent(player.currhealth,player.maxhealth)); //Reduce damage based on health.
	if (PlayerDamage != 0)
	{
		if (PlayerMuli > 1){cout<<"You got a crit on the "<<monster.name<<"! ";}
		cout<<"You "<<HitName()<<" the "<<monster.name<<" for "<<PlayerDamage<<".";
	}
	else {cout<<"The "<<monster.name<<" dodged your attack.";}
	monster.currhealth -= PlayerDamage;
	if (monster.currhealth<=0) {return true;}
	return false;
}

string StateOfBeing(int intCurrHealth, int intMaxHealth)
{
	/*Outputs a string that gives a description of how the monster is doing
	  Example: at full health can return "Healthy"
	  while below 10% of max health it might return "dying" or "badly wounded"*/
	long flHealthPercent = (intCurrHealth * 100)/intMaxHealth;
	string strState;
	int intRandomState;
	
	const string FullHealthOutput[3] = {"steady","well","healthy"};
	const string SeventyPHealthOutput[3] = {"wounded","damaged","hurt"};
	const string FiftyPHealthOutput[3] = {"injured","bleeding","very hurt"};
	const string TwentyFivePHealthOutput[3] = {"really hurt","in pain","badly damaged"};
	const string TenPHealthOutput[3] = {"badly wounded","badly hurt","close to dying"};
	const string FivePHealthOutput[3] = {"to be dying","heavily wounded","gravely wounded"};
	
	intRandomState = rand() % 3; //0-2
	
	if (flHealthPercent <= 5) {strState = FivePHealthOutput[intRandomState];}
	else if (flHealthPercent <= 10) {strState = TenPHealthOutput[intRandomState];}
	else if (flHealthPercent <= 25) {strState = TwentyFivePHealthOutput[intRandomState];}
	else if (flHealthPercent <= 50) {strState = FiftyPHealthOutput[intRandomState];}
	else if (flHealthPercent <= 70) {strState = SeventyPHealthOutput[intRandomState];}
	else {strState = FullHealthOutput[intRandomState];}
	
	return strState;
}

bool DodgeCheck(int LUK, int DEX)
{
	//The way I worked out this dodge calc is that if the Dex and Luk both equal 150 (which isn't possible under the current levelling up system),
	//then they have a 25% chance to dodge. I also wanted Dex to factor into 75% of the chance and Luk only 25%
	//Can return true, that they dodged or false that they did not.
    double douDodgeChance = ((DEX/2)+(LUK/6)/4);
	if(rand() % 101 <= douDodgeChance) {return true;}
	else {return false;}
}

int CalculateHealth(int HealthLevel, int ConsStat)
{
	//A simple function for calculating health.
	//In its own function so future changes will be changed everywhere.
	double HealthTemp = 0;
	HealthTemp = (0.9722 * pow(HealthLevel, 2) )+( 0.4167 * HealthLevel) + 48.611;
	HealthTemp += 23.979*exp(0.01414 * ConsStat);
	return floor(HealthTemp);
}

int CalculateDamage(int DamageLevel, int StrStat, int DefStat)
{
	//A simple function for calculating damage.
	//In its own function so future changes will be changed everywhere.
	int DamageTemp = 0;
	int intMinDamage = floor((monster.maxhealth+player.maxhealth)/20) + 1;
	StrStat += rand() % DamageLevel;
	DefStat += rand() % DamageLevel;
	if (DefStat > StrStat) {return intMinDamage;}
	else if (DefStat == StrStat) {return intMinDamage + rand() % (DamageLevel *2);}
	else
	{
		DamageTemp = floor((StrStat - DefStat)*1.75);
		DamageTemp += intMinDamage;
		DamageTemp += rand() % (DamageLevel *2);
		return DamageTemp;
	}
	
	return intMinDamage;
}

void RandomMonster()
{
	//Generates a number 0 - 4 representing the location of a monster in the monster name array
	//It then places the name and base stats of the monster appropriately. 
	int intRandomMonsterNumber;
	
	intRandomMonsterNumber = rand() % 5;
	monster.name = monsters[intRandomMonsterNumber].name;
	monster.str = monsters[intRandomMonsterNumber].str;
	monster.cons = monsters[intRandomMonsterNumber].cons;
	monster.def = monsters[intRandomMonsterNumber].def;
	monster.dex = monsters[intRandomMonsterNumber].dex;
	monster.luk = monsters[intRandomMonsterNumber].luk;
	//monster.maxhealth = CalculateHealth(intBattleLevel, monster.cons);
	//monster.currhealth = monster.maxhealth;
}

void RandomMonsterModifier()
{
	//Adds a random modifier onto a monster it can boost or reduce the stats of the monster.
	//Varies a bit with a player's LUK
	MonsterModifier = "";
	//Two random numbers that are added onto player and monster stats
	int intMRandomNumber;
	int intPRandomNumber;
	//Two more random numbers for further randomization of the effects.
	int intRandomNumber;
	int intRandomModifier;
	intMRandomNumber = rand() % 20; //0 - 19
	intPRandomNumber = rand() % 20; //0 - 19
	intRandomNumber = rand() % 100 + 1; //1 - 100
	
	if (monster.luk + intMRandomNumber > player.luk+intPRandomNumber)
	{
		//Monster has better chance of spawning with a positive effect
		if (intRandomNumber < 60){MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {monster.str+=5;}
			else if (MonsterModifier == "Large") {monster.cons+=5;}
			else if (MonsterModifier == "Massive")
			{
				monster.cons+=5;
				monster.str+=5;
				monster.dex-=5;
			}
			else if (MonsterModifier == "Fast") {monster.dex+=5;}
			else if (MonsterModifier == "Lucky") {monster.luk+=5;}
			else if (MonsterModifier == "Solid") {monster.cons+=5;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %5; //0 - 4
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.str-=5;}
			else if (MonsterModifier == "Small") {monster.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.def-=5;}
			else if (MonsterModifier == "Slow") {monster.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.luk-=5;}
			else {MonsterModifier="";}
		}
		else {/*This shouldn't happen but just in case.*/MonsterModifier="";}
	}
	else if (monster.luk + intMRandomNumber < player.luk+intPRandomNumber)
	{
		//Monster has better chance of spawning with a negative effect
		if (intRandomNumber < 60) {MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %5; //0 - 4
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.str-=5;}
			else if (MonsterModifier == "Small") {monster.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.def-=5;}
			else if (MonsterModifier == "Slow") {monster.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.luk-=5;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {monster.str+=5;}
			else if (MonsterModifier == "Large") {monster.cons+=5;}
			else if (MonsterModifier == "Massive")
			{
				monster.cons+=5;
				monster.str+=5;
				monster.dex-=5;
			}
			else if (MonsterModifier == "Fast") {monster.dex+=5;}
			else if (MonsterModifier == "Lucky") {monster.luk+=5;}
			else if (MonsterModifier == "Solid") {monster.cons+=5;}
			else {MonsterModifier="";}
		}
		else {/*This shouldn't happen but just in case.*/MonsterModifier="";}
	}
	else {/*The two stats are equal therefore the monster is a normal monster without any other checks.*/MonsterModifier = "";}
//End of random monster modifier.	
}

void LevelUpMonster()
{
	//Function to level up the monster.
	int StatUpgradeChance[5] = {0,0,0,0,0};
	int intStatPoints = (intBattleLevel - 1) *5; //How many stat points the monster gets.
	int intRandomStatChoice = 0;
	
	StatUpgradeChance[0] = monster.str;
	StatUpgradeChance[1] = monster.cons + StatUpgradeChance[0];
	StatUpgradeChance[2] = monster.def + StatUpgradeChance[1];
	StatUpgradeChance[3] = monster.dex + StatUpgradeChance[2];
	StatUpgradeChance[4] = monster.luk + StatUpgradeChance[3];
	
	for (int i = 0; i < intStatPoints; i++) //Random place points in the different stats.
	{
		intRandomStatChoice = rand() % 101;
		if (intRandomStatChoice < StatUpgradeChance[0]) {monster.str += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[1]) {monster.cons += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[2]) {monster.def += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[3]) {monster.dex += 1;}
		else {monster.luk += 1;}
	}
	if (blBattleDebugMode)
	{
		cout<<endl<<monster.str;
		cout<<endl<<monster.cons;
		cout<<endl<<monster.def;
		cout<<endl<<monster.dex;
		cout<<endl<<monster.luk;
		cout<<endl;
	}
	//Recalculate healths and re-heal them
    monster.maxhealth = floor(CalculateHealth(intBattleLevel,monster.cons)/2);
    monster.currhealth = monster.maxhealth;
}

void LevelUpFunction()
{
	//Holds function for levelling up.
	int intPlayerStatPoints = 20; //Player gets 20 skill points to spend how they would like.
	int intBattleLevelUpAmount;
	string strLevelUpChoice;
	cout << string(50, '\n');
	cout<<endl<<"LEVEL UP!"<<endl<<"You can put 20 points in any way you wish."<<endl;
	
	do
	{
		LevelUpChoice:
		cout<<"You have "<<intPlayerStatPoints<<" left to spend."<<endl<<endl;
		cout<<"STR: "<<player.str<<endl<<"CONS: "<<player.cons<<endl;
		cout<<"DEF: "<<player.def<<endl<<"DEX: "<<player.dex<<endl;
		cout<<"LUK: "<<player.luk<<endl<<"NONE to not use any points.";
		cout<<endl<<"Enter the stat you wish to improve."<<endl;
		
		cout<<"> ";
		
		cin>>strLevelUpChoice;
		strLevelUpChoice = ConvertToUpper(strLevelUpChoice); //Capitalize all letters in the string.
		
		if (!(strLevelUpChoice == "STR" || strLevelUpChoice == "CONS" || strLevelUpChoice == "DEF" || strLevelUpChoice == "DEX" || strLevelUpChoice == "LUK" || strLevelUpChoice == "NONE"))
		{
			cout << string(50, '\n');
			cout<<endl<<"Invalid choice, try again."<<endl;
			goto LevelUpChoice;
		}
		
		if (strLevelUpChoice != "NONE")
		{
			LevelUpAmount:
			cout << string(50, '\n');
			cout<<endl<<"You have chosen to upgrade "<<strLevelUpChoice<<" please enter the points you wish to add."<<endl;
			cout<<"You have "<<intPlayerStatPoints<<" left to spend."<<endl;
			cout<<"If you chose the wrong stat just enter 0 to not give it any points."<<endl<<endl;
			cout<<"> ";
			if ( !(cin >> intBattleLevelUpAmount) ) //Checks that value entered is correct
			{
				cin.clear();
				cin.ignore();
				cout <<endl<< "Incorrect entry. Try again: ";
			}
			intBattleLevelUpAmount = floor(intBattleLevelUpAmount);
			if (intBattleLevelUpAmount > intPlayerStatPoints || intBattleLevelUpAmount < 0) 
			{
				cout << string(50, '\n');
				cout<<endl<<"You have entered an invalid number, please try again.";
				goto LevelUpAmount;
			}
			
			if (strLevelUpChoice == "STR") {player.str += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "CONS") {player.cons += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "DEF") {player.def += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "DEX") {player.dex += intBattleLevelUpAmount;}
			else{player.luk += intBattleLevelUpAmount;}
			
			intPlayerStatPoints -= intBattleLevelUpAmount;
		}
		else {intPlayerStatPoints = 0;} //Player chose not to use rest of points so just cause the loop to end.
		
	} while (intPlayerStatPoints > 0);
	//Recalculate player's health.
    player.maxhealth = CalculateHealth(intBattleLevel, player.cons);
    player.currhealth = player.maxhealth;
//End of level up function.
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
	
	
    double douPlayerHealAmount;
	char chrPlayerBattleChoice;
	
    //Recalculate amount player heals for.
    douPlayerHealAmount = floor(player.maxhealth/10);
    BattleGoto:
	cout << string(10, '\n');

    double douPlayerCritChance = ((player.luk)/20 + rand() %3) * 4; 
    double douMonsterCritChance =((monster.luk)/20 + rand() %3) * 4;
	
    double douMonsterDamageMuli = 1;
    double douPlayerDamageMuli = 1;
	
    int intPlayerDamage = 0;
    int intMonsterDamage = 0;
	
	bool blPlayerDead = false;
	bool blMonsterDead = false;
	
    //Check both monster and player to see if they get a crit this round.
	//Rand() % 101 generates a random number between 0 and 100.
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.375;}
	
	if(DodgeCheck(player.dex,player.luk)) {douMonsterDamageMuli = 0;}
    if(DodgeCheck(monster.dex,monster.luk)) {douPlayerDamageMuli = 0;}
	
    //Calculate damage done.
    intPlayerDamage = CalculateDamage(intBattleLevel, player.str, monster.def) * douPlayerDamageMuli;
    intMonsterDamage = CalculateDamage(intBattleLevel, monster.str, player.def) * douMonsterDamageMuli;
	
    cout<<"You are now fighting a level "<<intBattleLevel<<" "<<monster.name<<"!";
    /*cout<<endl<<"It has "<<monster.currhealth<<" out of "<<monster.maxhealth<<" HP left"<<endl;*/
	cout<<endl<<"The "<<monster.name<<" appears to be "<<StateOfBeing(monster.currhealth,monster.maxhealth)<<".";
    cout<<endl<<endl<<"You have "<<player.currhealth<<" out of "<<player.maxhealth<<" HP left."<<endl;
    PlayerChoice:
	
    cout<<endl<<"What you like to do?"<<endl;
	cout<<"[A]ttack    [H]eal"<<endl<<"E[X]it    Hel[P]"<<endl;
	cout<<"[R]un away"<<endl;
	if (blBattleDebugMode) {cout<<"[K]ill monster    [D]ebug values"<<endl;}
	
    cout<<"> ";
    cin>>chrPlayerBattleChoice;
    chrPlayerBattleChoice = CharConvertToUpper(chrPlayerBattleChoice);
	
    switch(chrPlayerBattleChoice)
    {
        case 'A' :
            cout << string(10, '\n');
			if ((monster.dex+monster.luk/5)+rand() % 5 > (player.dex+player.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first.
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				if (blPlayerDead) {return 'F';}
				if (!StunCheck(monster.luk,player.luk))
				{
					blMonsterDead = PlayerAttack(intPlayerDamage,douPlayerDamageMuli);
					if (blMonsterDead) {return 'T';}
				}
				else {cout<<endl<<"You were stunned and unable to attack.";}
			}
			else 
			{
				//Player attacks first.
				blMonsterDead = PlayerAttack(intPlayerDamage,douPlayerDamageMuli);
				if (blMonsterDead) {return 'T';}
				if (!StunCheck(player.luk,monster.luk))
				{
					blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
					if (blPlayerDead) {return 'F';}		
				}
				else {cout<<endl<<"The "<<monster.name<<" was stunned by your hit and unable to attack.";}
		
			}
            cout<<endl;
			getchar();
            goto BattleGoto;
			break;
        case 'H' :
            //Code for player healing.
			cout << string(10, '\n');
			if ((monster.dex+monster.luk/5)+rand() % 5 > (player.dex+player.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,true);
				if (blPlayerDead) {return 'F';}
				
				if (!StunCheck(monster.luk,player.luk))
				{
					if (player.currhealth+douPlayerHealAmount > player.maxhealth) {player.currhealth=player.maxhealth;}
					else {player.currhealth += douPlayerHealAmount;}
				}
				else {cout<<endl<<"You were stunned and unable to heal.";}
			}
			else
			{
				//Player heals first
				if (player.currhealth+douPlayerHealAmount > player.maxhealth) {player.currhealth=player.maxhealth;}
				else {player.currhealth += douPlayerHealAmount;}
				
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,true);
				if (blPlayerDead) {return 'F';}				
			}
			getchar();
			goto BattleGoto;
			break;
        case 'P' :
			cout << string(2, '\n');
            cout<<endl<<"Attacking means that you attack the monster and you both deal damage to each other assuming no one dodges";
            cout<<endl<<"Healing means that you heal for 10% of your maximum health, "<< douPlayerHealAmount<<" HP. While healing you also take less damage.";
			cout<<endl<<"Running away, has a small chance based on DEX and LUK to leave a battle and return to dungeon map.";
			cout<<endl<<"Exit will leave the game and lose all progress.";
            cout<<endl<<"Help brings up this menu."<<endl;
			getchar();
            goto PlayerChoice;
			break;
		case 'X' : //Exits game.
			cout << string(50, '\n');
			cout<<endl<<"Are you sure you want to exit the game?"<<endl<<"All progress will be lost."<<endl<<"Y or N"<<endl<<"> ";
			cin>>chrPlayerBattleChoice;
			chrPlayerBattleChoice = CharConvertToUpper(chrPlayerBattleChoice);
			switch (chrPlayerBattleChoice)
			{
				case 'Y' :
					return 'F';
					break;
				default :
					goto PlayerChoice;
					break;
			}
			break;
		case 'R' : //chance to run away.
			if (rand() % 101 < ((player.dex + player.luk/6) + rand() % 10)/10 ) {return 'T';}
			else 
			{
				cout<<"You failed to get away."<<endl;
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				getchar();
				if (blPlayerDead) {return 'F';}
			}
			goto BattleGoto;
			break;
		/*Debug commands & invalid choice here*/
        case 'D' : //Debug code reveal some values.
			if (blBattleDebugMode)
			{
				cout << string(2, '\n');
				cout<<endl<<"Monster current health: "<<monster.currhealth;
				cout<<endl<<"Monster max health: "<<monster.maxhealth;
				cout<<endl<<"Player crit chance: "<<douPlayerCritChance;
				cout<<endl<<"Monster crit chance: "<<douMonsterCritChance;
				cout<<endl<<"Player muli: "<<douPlayerDamageMuli;
				cout<<endl<<"Monster muli: "<<douMonsterDamageMuli;
				cout<<endl<<"Player damage: "<<intPlayerDamage;
				cout<<endl<<"Monster damage: "<<intMonsterDamage;
				getchar();
				goto BattleGoto;
			}
        case 'K' : //Debug code "kills" the current monster.
			if (blBattleDebugMode)
			{
				cout << string(50, '\n');
				return 'T';
			}
        default :
            cout<<endl<<"Invalid choice, please try again.";
            goto PlayerChoice;
			break;
	
    }
	goto BattleGoto; //Should not need this but just in case.
//End of battle scene function.
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
	cout<<endl<<"Strength (STR) - Effects how much damage you do when you attack."<<endl;
	cout<<"Constitution (CONS) - Effects how much health you have."<<endl;
	cout<<"Dexterity (DEX) - Effects if your chance to dodge, and if you attack first."<<endl;
	cout<<"Defence (DEF) - Effects how much damage you take."<<endl;
	cout<<"Luck (LUK) - The random chance things will go your way, with dodges, crits, and rare modifiers that appear on monsters."<<endl;
	int intSkillPointsLeft = 100;
	cout<<"You have "<< intSkillPointsLeft <<" points to spend however you desire on these five stats, however each stat must have at least 1 point."<<endl;

	do 
	{
		cout<<endl<<"Enter your stat for your STRENGTH: ";
		if ( !(cin >> intStr) ) //Checks that value entered is correct
		{
			cin.clear();
			cin.ignore();
			cout << "Incorrect entry. Try again: ";
		}
		intStr = floor(intStr);
	}while (intStr < 1);
	intSkillPointsLeft -= intStr;
	//A check to see if they put too many points into a stat
	//Since each stat must have at least 1 point
	if( intSkillPointsLeft < 4 )
	{
		cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
		return 'F';
	}

	cout<<endl<<"You have "<< intSkillPointsLeft <<" points left to spend.";
	do 
	{
		cout<<endl<<"Enter your stat for your CONSTITUTION: ";
		if ( !(cin >> intCons) ) //Checks that value entered is correct
		{
			cin.clear();
			cin.ignore();
			cout << "Incorrect entry. Try again: ";
		}
		intCons = floor(intCons);
	}while (intCons <1);
	intSkillPointsLeft -= intCons;
	if(intSkillPointsLeft < 3)
	{
		cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
		return 'F';
	}
	cout<<endl<<"You have "<< intSkillPointsLeft <<" points left to spend";
	do 
	{
		cout<<endl<<"Enter your stat for your DEFENCE: ";
		if ( !(cin >> intDef) ) //Checks that value entered is correct
		{
			cin.clear();
			cin.ignore();
			cout << "Incorrect entry. Try again: ";
		}
		intDef = floor(intDef);
	}while (intDef <1);
	intSkillPointsLeft -= intDef;
	if(intSkillPointsLeft < 2)
	{
		cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
		return 'F';
	}
	cout<<endl<<"You have "<< intSkillPointsLeft <<" points left to spend";
	do 
	{
		cout<<endl<<"Enter your stat for your DEXTERITY: ";
		if ( !(cin >> intDex) ) //Checks that value entered is correct
		{
			cin.clear();
			cin.ignore();
			cout << "Incorrect entry. Try again: ";
		}
		intDex = floor(intDex);
	}while (intDex < 1);
	intSkillPointsLeft -= intDex;
	if(intSkillPointsLeft < 1)
	{
		cout<<"You used too many points."<<endl<<"Each stat must have at least one point in it.";
		return 'F';
	}

	cout<<endl<< intSkillPointsLeft <<" points are placed in LUCK."<<endl;
	intLuk = intSkillPointsLeft;

	char strAnswer;
	cout << string(50, '\n');
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
			break;
		case 'N' :
			return 'F';
			break;
		default :
			cout<<endl<<"Invalid choice, try again."<<endl;
			goto AgreeWithStats;
			break;
    }

	//Make an array of the player's stats for easier referencing of them later
	RestofGame:
	player.str=intStr;
	player.cons=intCons;
	player.def=intDef;
	player.dex=intDex;
	player.luk=intLuk;
	cout << string(50, '\n');
	
	player.maxhealth = CalculateHealth(1,player.cons);
    player.currhealth = player.maxhealth;
	
	return 'T';
//End of player initialize.
}

bool startbattle(int intsLevel)
{
	intBattleLevel = intsLevel;
	char charBattleSceneEnding;
	RandomMonster(); //Generate a random monster.
	LevelUpMonster(); //Level up monster.
	RandomMonsterModifier(); //Give monster random modifier. 
	if (MonsterModifier != "") {monster.name = ConvertToLower(MonsterModifier) + " " + ConvertToLower(monster.name);} //If monster has a modifier change name to include it.
	else {monster.name = ConvertToLower(monster.name);}
    charBattleSceneEnding = BattleScene();
	switch(charBattleSceneEnding)
	{
		case 'T' :
			cout << string(50, '\n');
			cout<<"You beat the "<<monster.name<<"."<<endl;
			getchar();
            return true;
			break;
		case 'F' : 
			cout << string(50, '\n');
			cout<<"You lost..."<<endl<<" You completed "<<intBattleLevel - 1 <<" dungeons.";
            cout<<endl<<"Press enter to close this game and try again!";
            getchar();
            return false;
			break;
		default :
			cout<<endl<<"An error has occurred in the code. Sorry :( The game will exit.";
			cout<<endl<<"If you would be so kind as to report what you were doing I can try to fix it!";
			getchar();
			return false;
			break;
	}
}

int getbattlevalue(int intvalue)
{
	if (intvalue < 0) {return 0;}
	else if (intvalue == statStr) {return player.str;}
	else if (intvalue == statCons) {return player.cons;}
	else if (intvalue == statDef) {return player.def;}
	else if (intvalue == statDex) {return player.dex;}
	else if (intvalue == statLuk) {return player.luk;}
	else if (intvalue == statCurrHealth) {return player.currhealth;}
	else if (intvalue == statMaxHealth) {return player.maxhealth;}
	else if (intvalue == statStatus) {return player.status;}
	return 0;
}

void setbattlevalue(int intlocation, int intvalue)
{
	if (intlocation == statStr) {player.str = intvalue;}
	else if (intlocation == statCons) {player.cons = intvalue;}
	else if (intlocation == statDef) {player.def = intvalue;}
	else if (intlocation == statDex) {player.dex = intvalue;}
	else if (intlocation == statLuk) {player.luk = intvalue;}
	else if (intlocation == statCurrHealth) {player.currhealth = intvalue;}
	else if (intlocation == statMaxHealth) {player.maxhealth = intvalue;}
	else if (intlocation == statStatus) {player.status = intvalue;}
}

int getmonstervalue(int intlocation)
{
	if (intlocation < 0) {return 0;}
	else if (intlocation == statStr) {return monster.str;}
	else if (intlocation == statCons) {return monster.cons;}
	else if (intlocation == statDef) {return monster.def;}
	else if (intlocation == statDex) {return monster.dex;}
	else if (intlocation == statLuk) {return monster.luk;}
	else if (intlocation == statCurrHealth) {return monster.currhealth;}
	else if (intlocation == statMaxHealth) {return monster.maxhealth;}
	else if (intlocation == statStatus) {return monster.status;}
	return 0;
}

void setmonstervalue(int intlocation, int intvalue)
{
	if (intlocation == statStr) {monster.str = intvalue;}
	else if (intlocation == statCons) {monster.cons = intvalue;}
	else if (intlocation == statDef) {monster.def = intvalue;}
	else if (intlocation == statDex) {monster.dex = intvalue;}
	else if (intlocation == statLuk) {monster.luk = intvalue;}
	else if (intlocation == statCurrHealth) {monster.currhealth = intvalue;}
	else if (intlocation == statMaxHealth) {monster.maxhealth = intvalue;}
	else if (intlocation == statStatus) {monster.status = intvalue;}
}

#endif
