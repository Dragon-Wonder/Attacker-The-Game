#ifndef _BATTLE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BATTLE_H_INCLUDED__
/*********************************************************************************************************/
//Structure for different attacks used
struct stcAttack {
	string name; //Name of attack, kinda useless
	unsigned char element; //Element of attack, for calc multi later
	unsigned char basedamage; //Nothing at the moment, just here to try some stuff later.
	string hit; //Text that appears when the attack lands
};

//Structure for Mana and Health
struct healthmana {
	int current; //Current amount
	unsigned int max; //Max amount
};

//Structure for stats
struct stcStats {
	unsigned char str; //Strength (damage)
	unsigned char cons; //Constitution (health)
	unsigned char def; //Defence (damage taken)
	unsigned char dex; //Dexterity (speed)
	unsigned char luk; //Luck (randomness)
};

//Structure for status
struct stcStatus {
	unsigned int effect; //Effect Number based on enum
	unsigned char counter;//Keeps track of turns with effect for increased chance of it going away.
};

//Structure for items
/*
struct item {
	//Will expand as this becomes more relevant
	string name;
	unsigned char amount;
};

//Structure for inventory
struct inventory {
	item item1;
	item item2;
	item item3;
	item item4;
	item item5;
};
*/

//Structure for entities such as player and monsters
struct entity {
	string name; //Name of entity
	struct healthmana health; //Max and Current Health
	struct healthmana mana; //Max and Current Mana (only used for players atm)
	struct stcStats stats; //Entity Stats
	struct stcStatus status; //Entity status
	unsigned char element; //Element that the monster is. (for player is just physical)
	struct stcAttack attack; //Attack that it uses.
	unsigned char keys; //Currently does nothing.
};
/*********************************************************************************************************/
//Make constants of all the different attacks.
const stcAttack sword = {"sword",elementPhysical,10,"cut"};
const stcAttack claws = {"claws",elementPhysical,8,"swipe"};
const stcAttack fist = {"fist",elementEarth,5,"punched"};
const stcAttack magic = {"magic",elementWind,7,"whirlwind"};
const stcAttack murloc = {"[murloc sound]",elementWater,8,"[murloc sound]"};
const stcAttack bow = {"bow",elementPhysical,8,"shot"};
const stcAttack holy = {"holy light",elementLight,10,"shot"};
const stcAttack ghost = {"ghost touch",elementIce,7,"ghostly things"};
const stcAttack unholy = {"unholy power",elementDarkness,6,"unholy things"};
const stcAttack spark = {"spark",elementEnergy,7,"shocked"};
/*********************************************************************************************************/
/*A quick note on the base stats, a stat cannot be lower than 6, as a modifier might reduce the value by 5 points.
  The base stat point should also add up to be 100. */
const entity monsters[13] = {{"Zombie",{0,0},{0,0},{25,25,10,25,15},{effectNone,0},elementPhysical,sword,0},
							{"Skeleton",{0,0},{0,0},{35,18,6,25,6},{effectNone,0},elementPhysical,bow,0},
							{"Witch",{0,0},{0,0},{15,15,20,20,30},{effectNone,0},elementWind,magic,0},
							{"Imp",{0,0},{0,0},{15,15,15,40,15},{effectNone,0},elementFire,claws,0},
							{"Golem",{0,0},{0,0},{20,34,34,6,6},{effectNone,0},elementEarth,fist,0},
							{"Murloc",{0,0},{0,0},{20,20,20,20,20},{effectNone,0},elementWater,murloc,0},
							{"Demon",{0,0},{0,0},{25,25,20,20,10},{effectNone,0},elementDarkness,unholy,0},
							{"Angel",{0,0},{0,0},{15,15,20,20,30},{effectNone,0},elementLight,holy,0},
							{"Harpy",{0,0},{0,0},{10,10,10,35,35},{effectNone,0},elementWind,magic,0},
							{"Elf",{0,0},{0,0},{20,20,20,20,20},{effectNone,0},elementEarth,sword,0},
							{"Ghost",{0,0},{0,0},{20,20,20,20,20},{effectNone,0},elementIce,ghost,0},
							{"Undead Mutant",{0,0},{0,0},{34,34,20,6,6},{effectNone,0},elementDarkness,claws,0},
							{"Thunder Spider",{0,0},{0,0},{20,8,15,33,24},{effectNone,0},elementEnergy,spark,0}};
entity monster = {"Generic Monster",{0,0},{0,0},{6,6,6,6,6},{effectNone,0},elementNone,sword,100};
entity player = {"player",{0,0},{150,150},{6,6,6,6,6},{effectNone,0},elementPhysical,sword,5};
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
	else if (intvalue == statStr) {return player.stats.str;}
	else if (intvalue == statCons) {return player.stats.cons;}
	else if (intvalue == statDef) {return player.stats.def;}
	else if (intvalue == statDex) {return player.stats.dex;}
	else if (intvalue == statLuk) {return player.stats.luk;}
	else if (intvalue == statCurrHealth) {return player.health.current;}
	else if (intvalue == statMaxHealth) {return player.health.max;}
	else if (intvalue == statStatus) {return player.status.effect;}
	else if (intvalue == statStatusCounter) {return player.status.counter;}
	else if (intvalue == statKeys) {return player.keys;}
	else if (intvalue == statCurrMana) {return player.mana.current;}
	else if (intvalue == statMaxMana) {return player.mana.max;}
	return 0;
}

void setbattlevalue(unsigned int intlocation, int intvalue)
{
	if (intlocation == statStr) {player.stats.str = intvalue;}
	else if (intlocation == statCons) {player.stats.cons = intvalue;}
	else if (intlocation == statDef) {player.stats.def = intvalue;}
	else if (intlocation == statDex) {player.stats.dex = intvalue;}
	else if (intlocation == statLuk) {player.stats.luk = intvalue;}
	else if (intlocation == statCurrHealth) {player.health.current = intvalue;}
	else if (intlocation == statMaxHealth) {player.health.max = intvalue;}
	else if (intlocation == statStatus) {player.status.effect = intvalue;}
	else if (intlocation == statStatusCounter) {player.status.counter = intvalue;}
	else if (intlocation == statKeys) {player.keys = intvalue;}
	else if (intlocation == statCurrMana) {player.mana.current = intvalue;}
	else if (intlocation == statMaxMana) {player.mana.max = intvalue;}
}

int getmonstervalue(unsigned int intlocation)
{
	if (intlocation < 0) {return 0;}
	else if (intlocation == statStr) {return monster.stats.str;}
	else if (intlocation == statCons) {return monster.stats.cons;}
	else if (intlocation == statDef) {return monster.stats.def;}
	else if (intlocation == statDex) {return monster.stats.dex;}
	else if (intlocation == statLuk) {return monster.stats.luk;}
	else if (intlocation == statCurrHealth) {return monster.health.current;}
	else if (intlocation == statMaxHealth) {return monster.health.max;}
	else if (intlocation == statStatus) {return monster.status.effect;}
	else if (intlocation == statStatusCounter) {return monster.status.counter;}
	else if (intlocation == statKeys) {return monster.keys;}
	else if (intlocation == statCurrMana) {return monster.mana.current;}
	else if (intlocation == statMaxMana) {return monster.mana.max;}
	return 0;
}

void setmonstervalue(unsigned int intlocation, int intvalue)
{
	if (intlocation == statStr) {monster.stats.str = intvalue;}
	else if (intlocation == statCons) {monster.stats.cons = intvalue;}
	else if (intlocation == statDef) {monster.stats.def = intvalue;}
	else if (intlocation == statDex) {monster.stats.dex = intvalue;}
	else if (intlocation == statLuk) {monster.stats.luk = intvalue;}
	else if (intlocation == statCurrHealth) {monster.health.current = intvalue;}
	else if (intlocation == statMaxHealth) {monster.health.max = intvalue;}
	else if (intlocation == statStatus) {monster.status.effect = intvalue;}
	else if (intlocation == statStatusCounter) {monster.status.counter = intvalue;}
	else if (intlocation == statCurrMana) {monster.mana.current = intvalue;}
	else if (intlocation == statMaxMana) {monster.mana.max = intvalue;}
}

unsigned int CalculateDamage(unsigned char DamageLevel, unsigned char StrStat, unsigned char DefStat)
{
	//A simple function for calculating damage.
	//In its own function so future changes will be changed everywhere.
	unsigned int DamageTemp = 0;
	unsigned int intMinDamage = floor((monster.health.max+player.health.max)/20) + 1;
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

std::string getMonsterName() {return monster.name;}

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
	//Applys poison damage if player or monster is poisoned
	//Poison does 1/20 of the MAX health of player ot monster
	unsigned int PoisonDamage = 0;
	if (player.status.effect == effectPoison)
	{
		PoisonDamage = floor (player.health.max / 20);
		cout<<endl<<"You take "<<PoisonDamage<<" points of poison damage."<<endl;
		player.health.current -= PoisonDamage;
	}
	if (monster.status.effect == effectPoison)
	{
		PoisonDamage = floor (monster.health.max / 20);
		cout<<endl<<"The "<<monster.name<<" is hurt by its poison."<<endl;
		monster.health.current -= PoisonDamage;
	}
}

inline void ApplyBleedingDamage()
{
	//Applys bleeding damage if player or monster is bleeding
	//Bleeding does 1/7 of CURRENT health of player or monster
	unsigned int BleedDamage = 0;
	if (player.status.effect == effectBleeding)
	{
		BleedDamage = floor (player.health.current / 7);
		cout<<endl<<"You bleed out on the floor some more."<<endl;
		player.health.current -= BleedDamage;
	}
	if (monster.status.effect == effectBleeding)
	{
		BleedDamage = floor (monster.health.current / 7);
		cout<<endl<<"The "<<monster.name<<" bleeds out some more on the floor."<<endl;
		monster.health.current -= BleedDamage;
	}
}

bool MonsterAttack(unsigned int MonsterDamage, float MonsterMuli, bool ishealing)
{
	//Holds stuff for when monster attacks.
	//Only returns true if player died.
	//Is in its own function so I can call it a couple of different places.
	float ElementalMulti = ElementMulti(monster.attack.element,player.element);
	cout<<endl;
	MonsterDamage = floor(MonsterDamage * DamageHealthPercent(monster.health.current,monster.health.max) * ElementalMulti);//Reduce damage based on health.
	if (ishealing) {floor(MonsterDamage /= 3);} //if player is healing reduce damage.
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

	if (monster.status.effect == effectFrozen)
	{
		cout<<endl<<"The "<<monster.name<< " is stuck in a block of ice and cannot move!"<<endl;
		return false;
	}
	else if (monster.status.effect == effectBlinded)
	{
		cout<<endl<<"The "<<monster.name<<" cannot see well.";
		if(rand() % 101 > 5) {MonsterDamage = 0;}
	}

	if (MonsterDamage != 0)
	{
		if (MonsterMuli > 1){cout<<"The "<<monster.name<<" got a crit on you! ";}
		cout<<"The "<<monster.name<<" used its "<<monster.attack.name<<" and did "<<MonsterDamage<<" damage to you."<<endl;
		if (player.status.effect == effectNone) {if (rand() % 101 < 2) {
				player.status.effect = MonsterEffect;
				cout<<endl<<StartOfEffectString("player",player.status.effect)<<endl; }}
	}
	else {cout<<"You dodged the "<<monster.name<<"'s attack!"<<endl;}
	player.health.current -= MonsterDamage;
	if (player.health.current <= 0) {return true;}
	return false;
}

bool PlayerAttack(unsigned int PlayerDamage, float PlayerMuli)
{
	//Holds stuff for when player attacks.
	//Only returns true if monster died.
	//Is in its own function so I can call it a couple of different places.
	cout<<endl;
	float ElementalMulti = ElementMulti(player.attack.element,monster.element);
	PlayerDamage = floor(PlayerDamage * DamageHealthPercent(player.health.current,player.health.max) * ElementalMulti); //Reduce damage based on health.

	if (player.status.effect == effectFrozen)
	{
		cout<<endl<<"You are stuck in a block of ice and cannot move!";
		return false;
	}
	else if (player.status.effect == effectBlinded)
	{
		cout<<endl<<"You have a hard time seeing your target!";
		if (rand() % 101 > 5) {PlayerDamage = 0;}
	}
	if (PlayerDamage != 0)
	{
		if (PlayerMuli > 1){cout<<"You got a crit on the "<<monster.name<<"! ";}
		cout<<"You "<<HitName()<<" the "<<monster.name<<" for "<<PlayerDamage<<"."<<endl;
		if (monster.status.effect == effectNone) {if (rand() % 101 < 2) {
				monster.status.effect = effectBleeding;
				cout<<endl<<StartOfEffectString(monster.name,monster.status.effect)<<endl; }}
	}
	else {cout<<endl<<"The "<<monster.name<<" dodged your attack.";}
	monster.health.current -= PlayerDamage;
	if (monster.health.current<=0) {return true;}
	return false;
}

inline void RandomMonster()
{
	//Generates a number 0 - 12 representing the location of a monster in the monster name array
	//It then places the name and base stats of the monster appropriately.
	unsigned char intRandomMonsterNumber;

	intRandomMonsterNumber = rand() % 13;
	monster.name = monsters[intRandomMonsterNumber].name;
	monster.stats.str = monsters[intRandomMonsterNumber].stats.str;
	monster.stats.cons = monsters[intRandomMonsterNumber].stats.cons;
	monster.stats.def = monsters[intRandomMonsterNumber].stats.def;
	monster.stats.dex = monsters[intRandomMonsterNumber].stats.dex;
	monster.stats.luk = monsters[intRandomMonsterNumber].stats.luk;
	monster.status.effect = effectNone;
	monster.status.counter = 0;
	monster.element = monsters[intRandomMonsterNumber].element;
	monster.attack.name = monsters[intRandomMonsterNumber].attack.name;
	monster.attack.element = monsters[intRandomMonsterNumber].attack.element;
	monster.attack.basedamage = monsters[intRandomMonsterNumber].attack.basedamage;
	monster.attack.hit = monsters[intRandomMonsterNumber].attack.hit;
	monster.mana.max = monsters[intRandomMonsterNumber].mana.max;
	monster.mana.current = monster.mana.max;
	if (rand() % 101 <= 25) {monster.keys = 1;}
	else {monster.keys = 0;}
	//monster.health.max = CalculateHealth(intBattleLevel, monster.stats.cons);
	//monster.health.current = monster.health.max;
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

	if (monster.stats.luk + intMRandomNumber > player.stats.luk+intPRandomNumber)
	{
		//Monster has better chance of spawning with a positive effect
		if (intRandomNumber < 60){MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %7; //0 - 6
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {monster.stats.str+=5;}
			else if (MonsterModifier == "Large") {monster.stats.cons+=5;}
			else if (MonsterModifier == "Massive")
			{
				monster.stats.cons+=5;
				monster.stats.str+=5;
				monster.stats.dex-=5;
			}
			else if (MonsterModifier == "Fast") {monster.stats.dex+=5;}
			else if (MonsterModifier == "Lucky") {monster.stats.luk+=5;}
			else if (MonsterModifier == "Solid") {monster.stats.cons+=5;}
			else if (MonsterModifier == "Heavily-Armoured") {monster.stats.cons+=7; monster.stats.def+=5; monster.stats.luk-=2;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.stats.str-=5;}
			else if (MonsterModifier == "Small") {monster.stats.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.stats.def-=5;}
			else if (MonsterModifier == "Slow") {monster.stats.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.stats.luk-=5;}
			else if (MonsterModifier == "Spineless") {monster.stats.str -= 4; monster.stats.cons -=4; monster.stats.dex += 2;}
			else {MonsterModifier="";}
		}
		else {/*This shouldn't happen but just in case.*/MonsterModifier="";}
	}
	else if (monster.stats.luk + intMRandomNumber < player.stats.luk+intPRandomNumber)
	{
		//Monster has better chance of spawning with a negative effect
		if (intRandomNumber < 60) {MonsterModifier = "";}
		else if (intRandomNumber < 90)
		{
			intRandomModifier = rand() %6; //0 - 5
			MonsterModifier = NegMonsterModifiers[intRandomModifier];
			if(MonsterModifier == "Weak") {monster.stats.str-=5;}
			else if (MonsterModifier == "Small") {monster.stats.cons-=5;}
			else if (MonsterModifier == "Tiny") {monster.stats.def-=5;}
			else if (MonsterModifier == "Slow") {monster.stats.dex-=5;}
			else if (MonsterModifier == "Unlucky") {monster.stats.luk-=5;}
			else if (MonsterModifier == "Spineless") {monster.stats.str -= 4; monster.stats.cons -=4; monster.stats.dex += 2;}
			else {MonsterModifier="";}
		}
		else if (intRandomNumber <=100)
		{
			intRandomModifier = rand() %7; //0 - 6
			MonsterModifier = PosMonsterModifiers[intRandomModifier];
			if (MonsterModifier == "Strong") {monster.stats.str+=5;}
			else if (MonsterModifier == "Large") {monster.stats.cons+=5;}
			else if (MonsterModifier == "Massive")
			{
				monster.stats.cons+=5;
				monster.stats.str+=5;
				monster.stats.dex-=5;
			}
			else if (MonsterModifier == "Fast") {monster.stats.dex+=5;}
			else if (MonsterModifier == "Lucky") {monster.stats.luk+=5;}
			else if (MonsterModifier == "Solid") {monster.stats.cons+=5;}
			else if (MonsterModifier == "Heavily-Armoured") {monster.stats.cons+=7; monster.stats.def+=5; monster.stats.luk-=2;}
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

	StatUpgradeChance[0] = monster.stats.str;
	StatUpgradeChance[1] = monster.stats.cons + StatUpgradeChance[0];
	StatUpgradeChance[2] = monster.stats.def + StatUpgradeChance[1];
	StatUpgradeChance[3] = monster.stats.dex + StatUpgradeChance[2];
	StatUpgradeChance[4] = monster.stats.luk + StatUpgradeChance[3];

	for (unsigned char i = 0; i < intStatPoints; i++) //Random place points in the different stats.
	{
		intRandomStatChoice = rand() % 101;
		if (intRandomStatChoice < StatUpgradeChance[0]) {monster.stats.str += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[1]) {monster.stats.cons += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[2]) {monster.stats.def += 1;}
		else if (intRandomStatChoice < StatUpgradeChance[3]) {monster.stats.dex += 1;}
		else {monster.stats.luk += 1;}
	}
	if (blBattleDebugMode)
	{
		cout<<endl<<(int)monster.stats.str;
		cout<<endl<<(int)monster.stats.cons;
		cout<<endl<<(int)monster.stats.def;
		cout<<endl<<(int)monster.stats.dex;
		cout<<endl<<(int)monster.stats.luk;
		cout<<endl;
	}
	//Recalculate healths and re-heal them
    monster.health.max = floor(CalculateHealth(intBattleLevel,monster.stats.cons)/3);
    monster.health.current = monster.health.max;
}

void LevelUpFunction()
{
	//Holds function for levelling up.
	unsigned char intPlayerStatPoints = 20; //Player gets 20 skill points to spend how they would like.
	unsigned int intBattleLevelUpAmount;
	string strLevelUpChoice;
	player.status.effect = effectNone; //Get rid of effect on level up.
	player.status.counter = 0;
	cout << string(50, '\n');
	cout<<endl<<"LEVEL UP!"<<endl<<"You can put 20 points in any way you wish."<<endl;

	do
	{
		LevelUpChoice:
		cout<<"You have "<<(int)intPlayerStatPoints<<" left to spend."<<endl<<endl;
		cout<<"STR: "<<(int)player.stats.str<<endl<<"CONS: "<<(int)player.stats.cons<<endl;
		cout<<"DEF: "<<(int)player.stats.def<<endl<<"DEX: "<<(int)player.stats.dex<<endl;
		cout<<"LUK: "<<(int)player.stats.luk<<endl<<"NONE to not use any points.";
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

			if (strLevelUpChoice == "STR") {player.stats.str += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "CONS") {player.stats.cons += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "DEF") {player.stats.def += intBattleLevelUpAmount;}
			else if (strLevelUpChoice == "DEX") {player.stats.dex += intBattleLevelUpAmount;}
			else{player.stats.luk += intBattleLevelUpAmount;}

			intPlayerStatPoints -= intBattleLevelUpAmount;
		}
		else {intPlayerStatPoints = 0;} //Player chose not to use rest of points so just cause the loop to end.

	} while (intPlayerStatPoints > 0);
	//Recalculate player's health.
    player.health.max = CalculateHealth(intBattleLevel, player.stats.cons);
    player.health.current = player.health.max;
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
    unsigned int douPlayerHealAmount= floor(player.health.max/10);
	unsigned int intPlayerManaRegenAmount = floor(player.mana.max/15);
	char chrPlayerBattleChoice;
    BattleGoto:
	cout << string(10, '\n');
    float douPlayerCritChance = ((player.stats.luk)/20 + rand() %3) * 4;
    float douMonsterCritChance =((monster.stats.luk)/20 + rand() %3) * 4;
    float douMonsterDamageMuli = 0.85;
    float douPlayerDamageMuli = 1;
    unsigned int intPlayerDamage = 0;
    unsigned int intMonsterDamage = 0;
	bool blPlayerDead = false;
	bool blMonsterDead = false;
	string CastSpell;
	if (player.mana.current + intPlayerManaRegenAmount >= player.mana.max) {player.mana.current = player.mana.max;}
	else {player.mana.current += intPlayerManaRegenAmount;}
	//If player or monster has a status on them, add one to counter, and see if it is removed.
	if (player.status.effect != effectNone)
	{
		if (RemoveStatusEffect(player.stats.luk,player.status.effect,player.status.counter))
		{
			cout<<endl<<EndOfEffectString("player",player.status.effect)<<endl;
			player.status.effect = effectNone;
			player.status.counter = 0;
		}
		else {player.status.counter += 1;}
	}

	if (monster.status.effect != effectNone)
	{
		if (RemoveStatusEffect(monster.stats.luk,monster.status.effect,monster.status.counter))
		{
			cout<<endl<<EndOfEffectString(monster.name,monster.status.effect)<<endl;
			monster.status.effect = effectNone;
			monster.status.counter = 0;
		}
		else {monster.status.counter += 1;}
	}

	ApplyBleedingDamage();
	ApplyPoisonDamage();
	if (player.health.current <= 0) {return 'F';}
	if (monster.health.current <= 0) {return 'T';}
    //Check both monster and player to see if they get a crit this round.
	//Rand() % 101 generates a random number between 0 and 100.
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.275;}
	if (monster.status.effect == effectBlinded) {if(DodgeCheck(player.stats.dex+25,player.stats.luk+10)) {douMonsterDamageMuli = 0;}}
	else {if(DodgeCheck(player.stats.dex,player.stats.luk)) {douMonsterDamageMuli = 0;}}
	if (player.status.effect == effectBlinded) {if(DodgeCheck(monster.stats.dex+25,monster.stats.luk+10)) {douPlayerDamageMuli = 0;}}
    else {if(DodgeCheck(monster.stats.dex,monster.stats.luk)) {douPlayerDamageMuli = 0;}}
    //Calculate damage done.
	//If frozen add 30 to their defence.
	if (player.status.effect == effectFrozen) {intMonsterDamage = CalculateDamage(intBattleLevel, monster.stats.str, player.stats.def + 30) * douMonsterDamageMuli;}
	else {intMonsterDamage = CalculateDamage(intBattleLevel, monster.stats.str, player.stats.def) * douMonsterDamageMuli;}
	if (monster.status.effect == effectFrozen) {intPlayerDamage = CalculateDamage(intBattleLevel, player.stats.str, monster.stats.def + 30) * douPlayerDamageMuli;}
	else {intPlayerDamage = CalculateDamage(intBattleLevel, player.stats.str, monster.stats.def) * douPlayerDamageMuli;}
    cout<<"You are now fighting a level "<<(int)intBattleLevel<<" "<<monster.name<<"!";
	cout<<endl<<"The "<<monster.name<<" appears to be "<<StateOfBeing(monster.health.current,monster.health.max)<<".";
    //cout<<endl<<endl<<"You have "<<player.health.current<<" out of "<<player.health.max<<" HP left."<<endl;
	cout<<endl<<endl<<"Your health: "<<BarMarker(player.health.current,player.health.max)<<endl;
	cout<<"Your mana: "<<BarMarker(player.mana.current,player.mana.max)<<endl;
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
        case 'A' : //Attack
			cout << string(10, '\n');
			if ((monster.stats.dex+monster.stats.luk/5)+rand() % 5 > (player.stats.dex+player.stats.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first.
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				if (blPlayerDead) {return 'F';}
				if (!StunCheck(monster.stats.luk,player.stats.luk))
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
				if (!StunCheck(player.stats.luk,monster.stats.luk))
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
        case 'H' : //Code for player healing.
			cout << string(10, '\n');
			if ((monster.stats.dex+monster.stats.luk/5)+rand() % 5 > (player.stats.dex+player.stats.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,true);
				if (blPlayerDead) {return 'F';}

				if (!StunCheck(monster.stats.luk,player.stats.luk))
				{
					if (player.health.current+douPlayerHealAmount > player.health.max) {player.health.current=player.health.max;}
					else {player.health.current += douPlayerHealAmount;}
				}
				else {cout<<endl<<"You were stunned and unable to heal.";}
			}
			else
			{
				//Player heals first
				if (player.health.current+douPlayerHealAmount > player.health.max) {player.health.current=player.health.max;}
				else {player.health.current += douPlayerHealAmount;}

				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,true);
				if (blPlayerDead) {return 'F';}
			}
			getchar();
			goto BattleGoto;
			break;
        case 'P' : //Help menu
			cout << string(2, '\n');
            cout<<endl<<"Attacking means that you attack the monster and you both deal damage to each other assuming no one dodges";
            cout<<endl<<"Healing means that you heal for 10% of your maximum health, "<< douPlayerHealAmount<<" HP. While healing you also take less damage.";
			cout<<endl<<"Running away, has a small chance based on DEX and LUK to leave a battle and return to dungeon map.";
			cout<<endl<<"Exit will leave the game and lose all progress.";
			cout<<endl<<"Cast spell is a WIP function that allows you to type in a spell to cast, if the spell doesn't exist it fails to cast.";
			cout<<endl<<"Check scene will display important information such as status effects and elements";
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
			if ((rand() % 101 < ((player.stats.dex + player.stats.luk/6) + rand() % 10)/10) && (player.status.effect != effectConfused) && (player.status.effect != effectFrozen)) {return 'T';}
			else
			{
				cout<<"You failed to get away."<<endl;
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				getchar();
				if (blPlayerDead) {return 'F';}
			}
			goto BattleGoto;
			break;
		case 'S' : //Cast spell
			cout<<endl<<"Enter spell name you would like to cast."<<endl<<"> ";
			cin>>CastSpell;
			CastSpell = ConvertToLower(CastSpell);
			//init_spell(CastSpell);
			if ((monster.stats.dex+monster.stats.luk/5)+rand() % 5 > (player.stats.dex+player.stats.luk/5)+rand() % 5) //See who attacks first.
			{
				//Monster attacks first.
				blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
				if (blPlayerDead) {return 'F';}
				if (!StunCheck(monster.stats.luk,player.stats.luk))
				{
					init_spell(CastSpell);
					if(monster.health.current <= 0) {return 'T';}
				}
				else {cout<<endl<<"You were stunned and unable to attack.";}
			}
			else
			{
				//Player attacks first.
				init_spell(CastSpell);
				if(monster.health.current <= 0) {return 'T';}
				if (!StunCheck(player.stats.luk,monster.stats.luk))
				{
					blPlayerDead = MonsterAttack(intMonsterDamage,douMonsterDamageMuli,false);
					if (blPlayerDead) {return 'F';}
				}
				else {cout<<endl<<"The "<<monster.name<<" was stunned by your hit and unable to attack.";}
			}
			goto BattleGoto;
			break;
		case 'C' : //Checks scene, display information that is important
			cout<<endl<<"You are "<<StatusName(player.status.effect)<<".";
			cout<<endl<<"You have been for "<<(int)player.status.counter<<" turns.";
			cout<<endl<<"The "<<monster.name<<" is a "<<ElementName(monster.element)<<" elemental";
			cout<<endl<<"The "<<monster.name<<" is "<<StatusName(monster.status.effect)<<".";
			cout<<endl<<"The "<<monster.name<<" has been for "<<(int)monster.status.counter<<" turns.";
			goto BattleGoto;
			break;
		/*Debug commands & invalid choice here*/
        case 'D' : //Debug code reveal some values.
			if (blBattleDebugMode)
			{
				cout << string(2, '\n');
				cout<<endl<<"Monster current health: "<<monster.health.current;
				cout<<endl<<"Monster max health: "<<monster.health.max;
				cout<<endl<<"Monster element: "<<ElementName(monster.element);
				cout<<endl<<"Monster status: "<<StatusName(monster.status.effect);
				cout<<endl<<"Monster status counter: "<<(int)monster.status.counter;
				cout<<endl<<"Player current health: "<<player.health.current;
				cout<<endl<<"Player max health: "<<player.health.max;
				cout<<endl<<"Player current mana: "<<player.mana.current;
				cout<<endl<<"Player max mana: "<<player.mana.max;
				cout<<endl<<"Player status: "<<StatusName(player.status.effect);
				cout<<endl<<"Player status counter: "<<(int)player.status.counter;
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
				cin>>player.status.effect;
				cout<<endl<<StartOfEffectString("player",player.status.effect)<<endl;
				player.status.counter = 0;
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
	StatsGoto:
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
	if (intStr >= intSkillPointsLeft)
	{
		cout<<"\nYou used too many points please try again!\n";
		goto StatsGoto;
	}
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
	if (intCons >= intSkillPointsLeft)
	{
		cout<<"\nYou used too many points please try again!\n";
		goto StatsGoto;
	}
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
	if (intDef >= intSkillPointsLeft)
	{
		cout<<"\nYou used too many points please try again!\n";
		goto StatsGoto;
	}
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
	if (intDex >= intSkillPointsLeft)
	{
		cout<<"\nYou used too many points please try again!\n";
		goto StatsGoto;
	}
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
	player.stats.str=intStr;
	player.stats.cons=intCons;
	player.stats.def=intDef;
	player.stats.dex=intDex;
	player.stats.luk=intLuk;
	cout << string(50, '\n');
	player.health.max = CalculateHealth(1,player.stats.cons);
    player.health.current = player.health.max;
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
