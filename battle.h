#ifndef _BATTLE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BATTLE_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold all the functions related to battling, levelling up and player stats.
Current Revision: 1.0
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM BETA TO GAMMA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================
2015/03/16	1.0			Patrick Rye		-Move from beta revisions to gamma revisions.
										-Changed some int to smaller variables because they don't need to be that big.
										-Added simple spell casting.
											-It is currently quite unbalanced will work to improve later.
=============================================================================================================================================================
2015/03/16	1.0.1		Patrick Rye		-Change equation to see if status effect is removed.
										-Increase status effects turn cut off from 5 to 8.
=============================================================================================================================================================
2015/03/17	1.0.2		Patrick Rye		-Shows health as a bar now.
										-More damage for elements that are farther apart.
										-Added option to check monster.
=============================================================================================================================================================					
*/
/*********************************************************************************************************/
struct attack {
	string name;
	unsigned char element;
	unsigned char basedamage; //Nothing at the moment, just here to try some stuff later.
	string hit;
};

struct entity {
	string name;
	int currhealth;
	unsigned int maxhealth;
	unsigned char str;
	unsigned char cons;
	unsigned char def;
	unsigned char dex;
	unsigned char luk;
	unsigned char status;
	unsigned char statuscounter; //Keeps track of turns with effect for increased chance of it going away.
	unsigned char element; //Element that the monster is. (for player is just physical)
	attack attack; //Attack that it uses.
};
/*********************************************************************************************************/
//Make constants of all the different attacks.
const attack sword = {"sword",elementPhysical,10,"cut"};
const attack claws = {"claws",elementPhysical,8,"swipe"};
const attack fist = {"fist",elementEarth,5,"punched"};
const attack magic = {"magic",elementWind,7,"whirlwind"};
const attack murloc = {"murloc",elementWater,8,"[murloc sound]"};
const attack bow = {"bow",elementPhysical,8,"shot"};
const attack holy = {"holy light",elementLight,10,"shot"};
const attack ghost = {"ghost",elementIce,7,"ghostly things"};
const attack unholy = {"unholy power",elementDarkness,6,"unholy things"};
const attack spark = {"spark",elementEnergy,7,"shocked"};
/*********************************************************************************************************/
/*A quick note on the base stats, a stat cannot be lower than 6, as a modifier might reduce the value by 5 points.
  The base stat point should also add up to be 100. */
const entity monsters[13] = {{"Zombie",0,0,25,25,10,25,15,effectNone,0,elementPhysical,sword},
							{"Skeleton",0,0,35,18,6,25,6,effectNone,0,elementPhysical,bow},
							{"Witch",0,0,15,15,20,20,30,effectNone,0,elementWind,magic},
							{"Imp",0,0,15,15,15,40,15,effectNone,0,elementFire,claws},
							{"Golem",0,0,20,34,34,6,6,effectNone,0,elementEarth,fist},
							{"Murloc",0,0,20,20,20,20,20,effectNone,0,elementWater,murloc},
							{"Demon",0,0,25,25,20,20,10,effectNone,0,elementDarkness,unholy},
							{"Angel",0,0,15,15,20,20,30,effectNone,0,elementLight,holy},
							{"Harpy",0,0,10,10,10,35,35,effectNone,0,elementWind,magic},
							{"Elf",0,0,20,20,20,20,20,effectNone,0,elementEarth,sword},
							{"Ghost",0,0,20,20,20,20,20,effectNone,0,elementIce,ghost},
							{"Undead Mutant",0,0,34,34,20,6,6,effectNone,0,elementDarkness,claws},
							{"Thunder Spider",0,0,20,8,15,33,24,effectNone,0,elementEnergy,spark}};
entity monster = {"Generic",0,0,20,20,20,20,20,effectNone,0,elementNone,sword};
entity player = {"Player",0,0,20,20,20,20,20,effectNone,0,elementPhysical,sword};
/*********************************************************************************************************/
const string MonsterNames[13] = {"Zombie","Skeleton","Witch","Imp","Golem","Murloc","Demon","Angel","Harpy","Elf","Ghost","Undead Mutant","Thunder Spider"};
const string PosMonsterModifiers[7] = {"Strong","Large","Massive","Fast","Lucky","Solid","Heavily-Armoured"};
const string NegMonsterModifiers[6] = {"Weak","Small","Tiny","Slow","Unlucky","Spineless"};
/*********************************************************************************************************/
string MonsterModifier;
/*********************************************************************************************************/
unsigned char intBattleLevel = 1;
bool blBattleDebugMode = false;
/*********************************************************************************************************/
void SetBattleDebugMode(bool isDebug) {blBattleDebugMode = isDebug;}
/*********************************************************************************************************/
//These functions are here so that they can be referenced in the spells.h
int getbattlevalue(unsigned int intvalue)
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
	else if (intvalue == statStatusCounter) {return player.statuscounter;}
	return 0;
}

void setbattlevalue(unsigned int intlocation, int intvalue)
{
	if (intlocation == statStr) {player.str = intvalue;}
	else if (intlocation == statCons) {player.cons = intvalue;}
	else if (intlocation == statDef) {player.def = intvalue;}
	else if (intlocation == statDex) {player.dex = intvalue;}
	else if (intlocation == statLuk) {player.luk = intvalue;}
	else if (intlocation == statCurrHealth) {player.currhealth = intvalue;}
	else if (intlocation == statMaxHealth) {player.maxhealth = intvalue;}
	else if (intlocation == statStatus) {player.status = intvalue;}
	else if (intlocation == statStatusCounter) {player.statuscounter = intvalue;}
}

int getmonstervalue(unsigned int intlocation)
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
	else if (intlocation == statStatusCounter) {return monster.statuscounter;}
	return 0;
}

void setmonstervalue(unsigned int intlocation, int intvalue)
{
	if (intlocation == statStr) {monster.str = intvalue;}
	else if (intlocation == statCons) {monster.cons = intvalue;}
	else if (intlocation == statDef) {monster.def = intvalue;}
	else if (intlocation == statDex) {monster.dex = intvalue;}
	else if (intlocation == statLuk) {monster.luk = intvalue;}
	else if (intlocation == statCurrHealth) {monster.currhealth = intvalue;}
	else if (intlocation == statMaxHealth) {monster.maxhealth = intvalue;}
	else if (intlocation == statStatus) {monster.status = intvalue;}
	else if (intlocation == statStatusCounter) {monster.statuscounter = intvalue;}
}

unsigned int CalculateDamage(unsigned char DamageLevel, unsigned char StrStat, unsigned char DefStat)
{
	//A simple function for calculating damage.
	//In its own function so future changes will be changed everywhere.
	unsigned int DamageTemp = 0;
	unsigned int intMinDamage = floor((monster.maxhealth+player.maxhealth)/20) + 1;
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

/*********************************************************************************************************/
#include "spells.h"
/*********************************************************************************************************/

bool RemoveStatusEffect(unsigned char TargetLuk, unsigned char CurrentEffect, unsigned char EffectTurns)
{
	//Check if status effect should be removed based on turns and luck.
	if (EffectTurns >= 8) {return true;} //Get rid of effect if it has been there for more than 5 turns.
	if (rand() % 101 <= (EffectTurns * 12.5) + (TargetLuk / 3)) {return true;}
	return false;
}

inline void ApplyPoisonDamage()
{
	unsigned int PoisonDamage = 0;
	if (player.status == effectPoison)
	{
		PoisonDamage = floor (player.maxhealth / 20);
		cout<<endl<<"You take "<<PoisonDamage<<" points of poison damage."<<endl;
		player.currhealth -= PoisonDamage;
	}
	if (monster.status == effectPoison)
	{
		PoisonDamage = floor (monster.maxhealth / 20);
		cout<<endl<<"The "<<monster.name<<" is hurt by its poison."<<endl;
		monster.currhealth -= PoisonDamage;
	}
}

inline void ApplyBleedingDamage()
{
	unsigned int BleedDamage = 0;
	if (player.status == effectBleeding)
	{
		BleedDamage = floor (player.currhealth / 7);
		cout<<endl<<"You bleed out on the floor some more."<<endl;
		player.currhealth -= BleedDamage;
	}
	if (monster.status == effectBleeding)
	{
		BleedDamage = floor (monster.currhealth / 7);
		cout<<endl<<"The "<<monster.name<<" bleeds out some more on the floor."<<endl;
		monster.currhealth -= BleedDamage;
	}
}

bool MonsterAttack(unsigned int MonsterDamage, float MonsterMuli, bool ishealing)
{
	//Holds stuff for when monster attacks.
	//Only returns true if player died.
	//Is in its own function so I can call it a couple of different places.
	float ElementalMulti = ElementMulti(monster.attack.element,player.element);
	cout<<endl;
	MonsterDamage = floor(MonsterDamage * DamageHealthPercent(monster.currhealth,monster.maxhealth) * ElementalMulti);//Reduce damage based on health.
	if (ishealing) {floor(MonsterDamage /= 2);} //if player is healing reduce damage.
	unsigned char MonsterEffect;
	switch (monster.attack.element)
	{
		case elementFire :
			MonsterEffect = effectBurned;
			break;
		case elementIce :
			MonsterEffect = effectFrozen;
			break;
		case elementLight :
			MonsterEffect = effectBlinded;
			break;
		case elementDarkness :
			MonsterEffect = effectPoison;
			break;
		case elementWater :
			MonsterEffect = effectWet;
			break;
		case elementWind :
			MonsterEffect = effectConfused;
			break;
		case elementEnergy :
			//Don't have an effect atm
		case elementEarth :
			//Don't have an effect atm
		default :
			MonsterEffect = effectBleeding;
			break;
	};
	
	if (monster.status == effectFrozen)
	{
		cout<<endl<<"The "<<monster.name<< " is stuck in a block of ice and cannot move!"<<endl;
		return false;
	}
	else if (monster.status == effectBlinded)
	{
		cout<<endl<<"The "<<monster.name<<" cannot see well.";
		if(rand() % 101 > 5) {MonsterDamage = 0;}
	}
	
	if (MonsterDamage != 0)
	{
		if (MonsterMuli > 1){cout<<"The "<<monster.name<<" got a crit on you! ";}
		cout<<"The "<<monster.name<<" hit you for "<<MonsterDamage<<"."<<endl;
		if (player.status == effectNone) {if (rand() % 101 < 2) {
				player.status = MonsterEffect;
				cout<<endl<<StartOfEffectString("player",player.status)<<endl; }}
	}
	else {cout<<"You dodged the "<<monster.name<<"'s attack!"<<endl;}
	player.currhealth -= MonsterDamage;
	if (player.currhealth <= 0) {return true;}
	return false;
}

bool PlayerAttack(unsigned int PlayerDamage, float PlayerMuli)
{
	//Holds stuff for when player attacks.
	//Only returns true if monster died.
	//Is in its own function so I can call it a couple of different places.
	cout<<endl;
	float ElementalMulti = ElementMulti(player.attack.element,monster.element);
	PlayerDamage = floor(PlayerDamage * DamageHealthPercent(player.currhealth,player.maxhealth) * ElementalMulti); //Reduce damage based on health.
	
	if (player.status == effectFrozen)
	{
		cout<<endl<<"You are stuck in a block of ice and cannot move!";
		return false;
	}
	else if (player.status == effectBlinded)
	{
		cout<<endl<<"You have a hard time seeing your target!";
		if (rand() % 101 > 5) {PlayerDamage = 0;}
	}
	if (PlayerDamage != 0)
	{
		if (PlayerMuli > 1){cout<<"You got a crit on the "<<monster.name<<"! ";}
		cout<<"You "<<HitName()<<" the "<<monster.name<<" for "<<PlayerDamage<<"."<<endl;
		if (monster.status == effectNone) {if (rand() % 101 < 2) {
				monster.status = effectBleeding;
				cout<<endl<<StartOfEffectString(monster.name,monster.status)<<endl; }}
	}
	else {cout<<endl<<"The "<<monster.name<<" dodged your attack.";}
	monster.currhealth -= PlayerDamage;
	if (monster.currhealth<=0) {return true;}
	return false;
}

unsigned int CalculateHealth(unsigned char HealthLevel, unsigned char ConsStat)
{
	//A simple function for calculating health.
	//In its own function so future changes will be changed everywhere.
	float HealthTemp = 0;
	HealthTemp = (0.9722 * pow(HealthLevel, 2) )+( 0.4167 * HealthLevel) + 48.611;
	HealthTemp += 23.979*exp(0.01414 * ConsStat);
	return floor(HealthTemp);
}

inline void RandomMonster()
{
	//Generates a number 0 - 12 representing the location of a monster in the monster name array
	//It then places the name and base stats of the monster appropriately. 
	unsigned char intRandomMonsterNumber;
	
	intRandomMonsterNumber = rand() % 13;
	monster.name = monsters[intRandomMonsterNumber].name;
	monster.str = monsters[intRandomMonsterNumber].str;
	monster.cons = monsters[intRandomMonsterNumber].cons;
	monster.def = monsters[intRandomMonsterNumber].def;
	monster.dex = monsters[intRandomMonsterNumber].dex;
	monster.luk = monsters[intRandomMonsterNumber].luk;
	monster.status = effectNone;
	monster.statuscounter = 0;
	monster.element = monsters[intRandomMonsterNumber].element;
	monster.attack.name = monsters[intRandomMonsterNumber].attack.name;
	monster.attack.element = monsters[intRandomMonsterNumber].attack.element;
	monster.attack.basedamage = monsters[intRandomMonsterNumber].attack.basedamage;
	monster.attack.hit = monsters[intRandomMonsterNumber].attack.hit;
	//monster.maxhealth = CalculateHealth(intBattleLevel, monster.cons);
	//monster.currhealth = monster.maxhealth;
}

inline void RandomMonsterModifier()
{
	//Adds a random modifier onto a monster it can boost or reduce the stats of the monster.
	//Varies a bit with a player's LUK
	MonsterModifier = "";
	//Two random numbers that are added onto player and monster stats
	unsigned char intMRandomNumber;
	unsigned char intPRandomNumber;
	//Two more random numbers for further randomization of the effects.
	unsigned char intRandomNumber;
	unsigned char intRandomModifier;
	intMRandomNumber = rand() % 20; //0 - 19
	intPRandomNumber = rand() % 20; //0 - 19
	intRandomNumber = rand() % 100 + 1; //1 - 100
	
	if (monster.luk + intMRandomNumber > player.luk+intPRandomNumber)
	{
		//Monster has better chance of spawning with a positive effect
		if (intRandomNumber < 60){MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %7; //0 - 6
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
			else if (MonsterModifier == "Heavily-Armoured") {monster.cons+=7; monster.def+=5; monster.luk-=2;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.str-=5;}
			else if (MonsterModifier == "Small") {monster.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.def-=5;}
			else if (MonsterModifier == "Slow") {monster.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.luk-=5;}
			else if (MonsterModifier == "Spineless") {monster.str -= 4; monster.cons -=4; monster.dex += 2;}
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
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.str-=5;}
			else if (MonsterModifier == "Small") {monster.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.def-=5;}
			else if (MonsterModifier == "Slow") {monster.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.luk-=5;}
			else if (MonsterModifier == "Spineless") {monster.str -= 4; monster.cons -=4; monster.dex += 2;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %7; //0 - 6
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
			else if (MonsterModifier == "Heavily-Armoured") {monster.cons+=7; monster.def+=5; monster.luk-=2;}
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
	char StatUpgradeChance[5] = {0,0,0,0,0};
	unsigned char intStatPoints = (intBattleLevel - 1) *18; //How many stat points the monster gets.
	unsigned char intRandomStatChoice = 0;
	
	StatUpgradeChance[0] = monster.str;
	StatUpgradeChance[1] = monster.cons + StatUpgradeChance[0];
	StatUpgradeChance[2] = monster.def + StatUpgradeChance[1];
	StatUpgradeChance[3] = monster.dex + StatUpgradeChance[2];
	StatUpgradeChance[4] = monster.luk + StatUpgradeChance[3];
	
	for (unsigned char i = 0; i < intStatPoints; i++) //Random place points in the different stats.
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
		cout<<endl<<(int)monster.str;
		cout<<endl<<(int)monster.cons;
		cout<<endl<<(int)monster.def;
		cout<<endl<<(int)monster.dex;
		cout<<endl<<(int)monster.luk;
		cout<<endl;
	}
	//Recalculate healths and re-heal them
    monster.maxhealth = floor(CalculateHealth(intBattleLevel,monster.cons)/2);
    monster.currhealth = monster.maxhealth;
}

void LevelUpFunction()
{
	//Holds function for levelling up.
	unsigned char intPlayerStatPoints = 20; //Player gets 20 skill points to spend how they would like.
	unsigned char intBattleLevelUpAmount;
	string strLevelUpChoice;
	player.status = effectNone; //Get rid of effect on level up.
	player.statuscounter = 0;
	cout << string(50, '\n');
	cout<<endl<<"LEVEL UP!"<<endl<<"You can put 20 points in any way you wish."<<endl;
	
	do
	{
		LevelUpChoice:
		cout<<"You have "<<(int)intPlayerStatPoints<<" left to spend."<<endl<<endl;
		cout<<"STR: "<<(int)player.str<<endl<<"CONS: "<<(int)player.cons<<endl;
		cout<<"DEF: "<<(int)player.def<<endl<<"DEX: "<<(int)player.dex<<endl;
		cout<<"LUK: "<<(int)player.luk<<endl<<"NONE to not use any points.";
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
			cout<<"You have "<<(int)intPlayerStatPoints<<" left to spend."<<endl;
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
	
    unsigned int douPlayerHealAmount;
	char chrPlayerBattleChoice;
	
    //Recalculate amount player heals for.
    douPlayerHealAmount = floor(player.maxhealth/10);
    BattleGoto:
	cout << string(10, '\n');
    float douPlayerCritChance = ((player.luk)/20 + rand() %3) * 4; 
    float douMonsterCritChance =((monster.luk)/20 + rand() %3) * 4;
    float douMonsterDamageMuli = 0.9;
    float douPlayerDamageMuli = 1;
    unsigned int intPlayerDamage = 0;
    unsigned int intMonsterDamage = 0;
	bool blPlayerDead = false;
	bool blMonsterDead = false;
	string CastSpell;
	
	//If player or monster has a status on them, add one to counter, and see if it is removed.
	if (player.status != effectNone)
	{
		if (RemoveStatusEffect(player.luk,player.status,player.statuscounter))
		{
			cout<<endl<<EndOfEffectString("player",player.status)<<endl;
			player.status = effectNone;
			player.statuscounter = 0;
		}
		else {player.statuscounter += 1;}
	}
	
	if (monster.status != effectNone)
	{
		if (RemoveStatusEffect(monster.luk,monster.status,monster.statuscounter))
		{
			cout<<endl<<EndOfEffectString(monster.name,monster.status)<<endl;
			monster.status = effectNone;
			monster.statuscounter = 0;
		}
		else {monster.statuscounter += 1;}
	}
	
	ApplyBleedingDamage();
	ApplyPoisonDamage();
	if (player.currhealth <= 0) {return 'F';}
	if (monster.currhealth <= 0) {return 'T';}
    //Check both monster and player to see if they get a crit this round.
	//Rand() % 101 generates a random number between 0 and 100.
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.275;}
	if (monster.status == effectBlinded) {if(DodgeCheck(player.dex+25,player.luk+10)) {douMonsterDamageMuli = 0;}}
	else {if(DodgeCheck(player.dex,player.luk)) {douMonsterDamageMuli = 0;}}
	if (player.status == effectBlinded) {if(DodgeCheck(monster.dex+25,monster.luk+10)) {douPlayerDamageMuli = 0;}}
    else {if(DodgeCheck(monster.dex,monster.luk)) {douPlayerDamageMuli = 0;}}
    //Calculate damage done.
	//If frozen add 30 to their defence.
	if (player.status == effectFrozen) {intMonsterDamage = CalculateDamage(intBattleLevel, monster.str, player.def + 30) * douMonsterDamageMuli;}
	else {intMonsterDamage = CalculateDamage(intBattleLevel, monster.str, player.def) * douMonsterDamageMuli;}
	if (monster.status == effectFrozen) {intPlayerDamage = CalculateDamage(intBattleLevel, player.str, monster.def + 30) * douPlayerDamageMuli;}
	else {intPlayerDamage = CalculateDamage(intBattleLevel, player.str, monster.def) * douPlayerDamageMuli;}
    cout<<"You are now fighting a level "<<(int)intBattleLevel<<" "<<monster.name<<"!";
    /*cout<<endl<<"It has "<<monster.currhealth<<" out of "<<monster.maxhealth<<" HP left"<<endl;*/
	cout<<endl<<"The "<<monster.name<<" appears to be "<<StateOfBeing(monster.currhealth,monster.maxhealth)<<".";
    cout<<endl<<endl<<"You have "<<player.currhealth<<" out of "<<player.maxhealth<<" HP left."<<endl;
    PlayerChoice:
    cout<<endl<<"What you like to do?"<<endl;
	cout<<"[A]ttack    [H]eal"<<endl<<"E[X]it    Hel[P]"<<endl;
	cout<<"[R]un away     Cast [S]pell (WIP!)"<<endl;
	cout<<"[C]heck scene"<<endl;
	if (blBattleDebugMode) {cout<<"[K]ill monster    [D]ebug values   [F]orce Effect"<<endl;}
	
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
			if ((rand() % 101 < ((player.dex + player.luk/6) + rand() % 10)/10) && (player.status != effectConfused) && (player.status != effectFrozen)) {return 'T';}
			else 
			{
				cout<<"You failed to get away."<<endl;
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				getchar();
				if (blPlayerDead) {return 'F';}
			}
			goto BattleGoto;
			break;
		case 'S' :
			cout<<endl<<"Enter spell name you would like to cast."<<endl<<"> ";
			cin>>CastSpell;
			CastSpell = ConvertToLower(CastSpell);
			//init_spell(CastSpell);
			if ((monster.dex+monster.luk/5)+rand() % 5 > (player.dex+player.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first.
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				if (blPlayerDead) {return 'F';}
				if (!StunCheck(monster.luk,player.luk))
				{
					init_spell(CastSpell);
					if(monster.currhealth <= 0) {return 'T';}
				}
				else {cout<<endl<<"You were stunned and unable to attack.";}
			}
			else 
			{
				//Player attacks first.
				init_spell(CastSpell);
				if(monster.currhealth <= 0) {return 'T';}
				if (!StunCheck(player.luk,monster.luk))
				{
					blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
					if (blPlayerDead) {return 'F';}		
				}
				else {cout<<endl<<"The "<<monster.name<<" was stunned by your hit and unable to attack.";}
		
			}
			goto BattleGoto;
			break;
		case 'C' :
			cout<<endl<<"You are "<<StatusName(player.status)<<".";
			cout<<endl<<"You have been for "<<(int)player.statuscounter<<" turns.";
			cout<<endl<<"The monster is a "<<ElementName(monster.element)<<" elemental";
			cout<<endl<<"The monster is "<<StatusName(monster.status)<<".";
			cout<<endl<<"The monster has been for "<<(int)monster.statuscounter<<" turns.";
			goto BattleGoto;
			break;
		/*Debug commands & invalid choice here*/
        case 'D' : //Debug code reveal some values.
			if (blBattleDebugMode)
			{
				cout << string(2, '\n');
				cout<<endl<<"Monster current health: "<<monster.currhealth;
				cout<<endl<<"Monster max health: "<<monster.maxhealth;
				cout<<endl<<"Monster element: "<<ElementName(monster.element);
				cout<<endl<<"Monster status: "<<StatusName(monster.status);
				cout<<endl<<"Monster status counter: "<<(int)monster.statuscounter;
				cout<<endl<<"Player status: "<<StatusName(player.status);
				cout<<endl<<"Player status counter: "<<(int)player.statuscounter;
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
		case 'F' : //Force an effect.
			if (blBattleDebugMode)
			{
				cout<<endl<<endl<<"> ";
				cin>>player.status;
				cout<<endl<<StartOfEffectString("player",player.status)<<endl;
				player.statuscounter = 0;
				goto BattleGoto;
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
	unsigned int intStr = 0;
	unsigned int intCons = 0;
	unsigned int intDef = 0;
	unsigned int intDex = 0;
	unsigned int intLuk = 0;

	cout<<"In this game there are five stats that effect different elements of the game.";
	cout<<endl<<"Strength (STR) - Effects how much damage you do when you attack."<<endl;
	cout<<"Constitution (CONS) - Effects how much health you have."<<endl;
	cout<<"Dexterity (DEX) - Effects if your chance to dodge, and if you attack first."<<endl;
	cout<<"Defence (DEF) - Effects how much damage you take."<<endl;
	cout<<"Luck (LUK) - The random chance things will go your way, with dodges, crits, and rare modifiers that appear on monsters."<<endl;
	unsigned char intSkillPointsLeft = 100;
	cout<<"You have "<< (int)intSkillPointsLeft <<" points to spend however you desire on these five stats, however each stat must have at least 1 point."<<endl;

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

	cout<<endl<<"You have "<< (int)intSkillPointsLeft <<" points left to spend.";
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
	cout<<endl<<"You have "<< (int)intSkillPointsLeft <<" points left to spend";
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
	cout<<endl<<"You have "<< (int)intSkillPointsLeft <<" points left to spend";
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

	cout<<endl<< (int)intSkillPointsLeft <<" points are placed in LUCK."<<endl;
	intLuk = intSkillPointsLeft;

	char strAnswer;
	cout << string(50, '\n');
	AgreeWithStats:
	cout<<"Your current stats are as follows:"<<endl;
	cout<<"Strength: "<<(int)intStr<<endl;
	cout<<"Constitution: "<<(int)intCons<<endl;
	cout<<"Defence: "<<(int)intDef<<endl;
	cout<<"Dexterity: "<<(int)intDex<<endl;
	cout<<"Luck: "<<(int)intLuk<<endl;
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

bool startbattle(unsigned char intsLevel)
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
			cout<<"You lost..."<<endl<<"You completed "<<(int)(intBattleLevel - 1) <<" dungeons.";
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

#endif
