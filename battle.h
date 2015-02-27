#ifndef _BATTLE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _BATTLE_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold all the functions related to battling, levelling up and player stats.
Current Revision: 1.4
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2/23/15	1.0			Patrick Rye			-Original
=============================================================================================================================================================
2/24/15	1.1			Patrick Rye			-Changed system("cls") to cout << string(50, '\n');
=============================================================================================================================================================
2/24/15	1.2			Patrick Rye			-Moved level up to happen when you change levels.
										-Fixed bug that would cause endless loop is you entered non integer numbers for starting stats
											-Bug has been there since the start I just didn't know how to fix it till now.
										-Fixed bug where player could enter values below 1 for stats.
										-Fixed bug where player could enter decimal places for stats.
=============================================================================================================================================================
2/25/15	1.3			Patrick Rye			-Improved look of the code by adding separators.
										-Reduced chance for dodges and crits (cut by half).
										-Grammar and spelling fixes. (Whelp back to the old grim I guess).
										-Added breaks to case switches (kinda surprised it worked before).
=============================================================================================================================================================
2/26/15	1.4			Patrick Rye			-General code improvement.
										-Fixed losing message to better represent changes to objectives.
										-Grammar and spelling fixes.
											(┬──┬ ノ( ゜-゜ノ))
											((╯°□°)╯︵ ┻━┻)
=============================================================================================================================================================		
*/

/*
For Stat Arrays 
0 = STR
1 = CONS
2 = DEF
3 = DEX
4 = LUK
*/
/*********************************************************************************************************/
int MonsterBaseStats[5] = {25,25,10,25,10}; //A base array for the monsters 
const int ZombieBaseStats[5] = {25,25,10,25,10};
const int SkeletonBaseStats[5] = {20,35,15,35,6};
const int WitchBaseStats[5] = {15,15,20,40,30};
const int ImpBaseStats[5] = {10,10,10,40,10};
/*********************************************************************************************************/
const string MonsterNames[4] = {"Zombie","Skeleton","Witch","Imp"};
const string PosMonsterModifiers[7] = {"Strong","Large","Massive","Fast","Lucky","Powerful","Solid"};
const string NegMonsterModifiers[5] = {"Weak","Small","Tiny","Slow","Unlucky"};
/*********************************************************************************************************/
string MonsterName;
string MonsterModifier;
/*********************************************************************************************************/
double PlayerHealth[2]; //An array 0 is current health 1 is max
double MonsterHealth[2]; //An array 0 is current health 1 is max
int MonsterStats[5];
int PlayerStats[5];
/*********************************************************************************************************/
int intBattleLevel;
/*********************************************************************************************************/

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
	//Adds a random modifier onto a monster it can boost or reduce the stats of the monster.
	//Varies a bit with a player's LUK
	MonsterModifier = "";
	//Two random numbers that are added onto player and monster stats
	int intMRandomNumber;
	int intPRandomNumber;
	//Two more random numbers for further randomization of the effects.
	int intRandomNumber;
	int intRandomModifier;
	intMRandomNumber = rand() % 20;
	intPRandomNumber = rand() % 20;
	intRandomNumber = rand() % 100 + 1;
	
	if (MonsterStats[4] + intMRandomNumber > PlayerStats[4]+intPRandomNumber)
	{
		//Monster has better chance of spawning with a positive effect
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
		//Monster has better chance of spawning with a negative effect
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
	else {/*The two stats are equal therefore the monster is a normal monster without any other checks*/MonsterModifier = "";}
//End of random monster modifier.	
}

void LevelUpFunction()
{
	//Holds function for levelling up
	int intPlayerStatPoints = 20; //Player gets 20 skill points to spend how they would like.
	int intBattleLevelUpChoice;
	int intBattleLevelUpAmount;
	string strLevelUpChoice;
	cout << string(50, '\n');
	cout<<endl<<"LEVEL UP!"<<endl<<"You can put 20 points in any way you wish."<<endl;
	
	do
	{
		LevelUpChoice:
		cout<<"You have "<<intPlayerStatPoints<<" left to spend."<<endl<<endl;
		cout<<"STR: "<<PlayerStats[0]<<endl<<"CONS: "<<PlayerStats[1]<<endl;
		cout<<"DEF: "<<PlayerStats[2]<<endl<<"DEX: "<<PlayerStats[3]<<endl;
		cout<<"LUK: "<<PlayerStats[4]<<endl<<"NONE to not use any points.";
		cout<<endl<<"Enter the stat you wish to improve."<<endl;
		
		cout<<"> ";
		
		cin>>strLevelUpChoice;
		strLevelUpChoice = ConvertToUpper(strLevelUpChoice); //Capitalize all letters in the string.
		
		if (strLevelUpChoice == "STR") {intBattleLevelUpChoice = 0;}
		else if (strLevelUpChoice == "CONS") {intBattleLevelUpChoice = 1;}
		else if (strLevelUpChoice == "DEF") {intBattleLevelUpChoice = 2;}
		else if (strLevelUpChoice == "DEX") {intBattleLevelUpChoice = 3;}
		else if (strLevelUpChoice == "LUK") {intBattleLevelUpChoice = 4;}
		else if (strLevelUpChoice == "NONE") {intBattleLevelUpChoice = 9999;}
		else 
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
			if (intBattleLevelUpAmount > intPlayerStatPoints) 
			{
				cout << string(50, '\n');
				cout<<endl<<"You have entered too many points, please try again with less points.";
				goto LevelUpAmount;
			}
		
			if (intBattleLevelUpAmount < 0)
			{
				cout << string(50, '\n');
				cout<<endl<<"You have entered an invalid number, please try again.";
				goto LevelUpAmount;
			}
			
			PlayerStats[intBattleLevelUpChoice] = PlayerStats[intBattleLevelUpChoice] + intBattleLevelUpAmount;
			intPlayerStatPoints = intPlayerStatPoints - intBattleLevelUpAmount;
		}
		else {intPlayerStatPoints = 0;} //Player chose not to use rest of points so just cause the loop to end.
		
	} while (intPlayerStatPoints > 0);
//End of level up function
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
	//Recalculate all of the stats needed
    //Update monster stats to new level
	for (int i=0; i<5; i++) {MonsterStats[i] = floor((intBattleLevel*4)+MonsterBaseStats[i]);/*cout<<endl<<MonsterStats[i];*/ /*Debugging line*/}
    //Recalculate healths and re-heal them
    PlayerHealth[1] = floor((23*((5.25+0.5625*intBattleLevel+0.00375*pow(intBattleLevel,2))+(1+0.066*intBattleLevel)*(PlayerStats[1]/16))));
    PlayerHealth[0] = PlayerHealth[1];
    MonsterHealth[1] = floor((23*((5.25+0.5625*intBattleLevel+0.00375*pow(intBattleLevel,2))+(1+0.066*intBattleLevel)*(MonsterStats[1]/16))/3));
    MonsterHealth[0] = MonsterHealth[1];
    //Recalculate amount player heals for
    douPlayerHealAmount = floor(PlayerHealth[1]/10);
    BattleGoto:
	cout << string(10, '\n');
	//The way I worked out this dodge calc is that if the Dex and Luk both equal 150 (which isn't possible under the current levelling up system),
	//then they have a 25% chance to dodge. I also wanted Dex to factor into 75% of the chance and Luk only 25%
    double douPlayerDodgeChance = ((PlayerStats[3]/2)+(PlayerStats[4]/6)/4);
    double douMonsterDodgeChance = ((MonsterStats[3]/2)+(MonsterStats[4]/6)/4);
    double douPlayerCritChance = ((PlayerStats[4])/20 + rand() %3) * 4; 
    double douMonsterCritChance =((MonsterStats[4])/20 + rand() %3) * 4;
    double douMonsterDamageMuli = 1;
    double douPlayerDamageMuli = 1;
    int intPlayerDamage = 0;
    int intMonsterDamage = 0;
    //Check both monster and player to see if they get a crit this round
	//Rand() % 101 generates a random number between 0 and 100.
    if (rand() % 101 <= douPlayerCritChance) {douPlayerDamageMuli = 1.375;}
    if (rand() % 101 <= douMonsterCritChance) {douMonsterDamageMuli = 1.375;}
    //Check to see if Monster or Player dodges
    if(rand() % 101 <= douPlayerDodgeChance) {douMonsterDamageMuli = 0;} //Player dodges set monster damage to 0
    if(rand() % 101 <= douMonsterDodgeChance) {douPlayerDamageMuli = 0;} // Monster dodges
    //Calculate damage done
    intPlayerDamage = floor(((((2 * (intBattleLevel/5) + 2) * ((10*intBattleLevel)/MonsterStats[2]))*(PlayerStats[0]/8))+5)*douPlayerDamageMuli);
    intMonsterDamage = floor(((((2 * (intBattleLevel/5) + 2) * ((10*intBattleLevel)/PlayerStats[2]))*(MonsterStats[0]/8))+5)*douMonsterDamageMuli);
    cout<<"You are now fighting a level "<<intBattleLevel<<" "<<MonsterName<<"!";
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
            cout << string(10, '\n');
			
            if (intPlayerDamage != 0) //Check to see if monster manages to dodge the player
            {
                if(douPlayerDamageMuli > 1) {cout<<"You got a crit on the "<<MonsterName<<"! ";}
                cout<<"You hit at the "<<MonsterName<<" for "<<intPlayerDamage<<".";
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

            cout<<endl;
            goto HealthCheck;
			break;
        case 'H' :
            //Code for player healing
			cout << string(10, '\n');
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
			break;
        case 'Q' :
			cout << string(2, '\n');
            cout<<endl<<"Attacking means that you attack the monster and you both deal damage to each other assuming no one dodges";
            cout<<endl<<"Healing means that you heal for 10% of your maximum health, "<< douPlayerHealAmount<<" HP. While healing you also take less damage.";
			cout<<endl<<"Exit will leave the game and lose all progress.";
            cout<<endl<<"Help brings up this menu."<<endl;
            goto PlayerChoice;
			break;
        case 'D' : //Debug code reveal some values
			cout << string(2, '\n');
            cout<<endl<<"Player crit chance: "<<douPlayerCritChance;
            cout<<endl<<"Monster crit chance: "<<douMonsterCritChance;
            cout<<endl<<"Player dodge chance: "<<douPlayerDodgeChance;
            cout<<endl<<"Monster dodge chance: "<<douMonsterDodgeChance;
            cout<<endl<<"Player muli: "<<douPlayerDamageMuli;
            cout<<endl<<"Monster muli: "<<douMonsterDamageMuli;
            cout<<endl<<"Player damage: "<<intPlayerDamage;
            cout<<endl<<"Monster damage: "<<intMonsterDamage;
            goto PlayerChoice;
			break;
        case 'K' : //Debug code "kills" the current monster
			cout << string(50, '\n');
            return 'T';
			break;
        case 'E' : //exits game
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
        default :
            cout<<endl<<"Invalid choice, try again";
            goto PlayerChoice;
			break;
	
    }
	//Check if player is dead
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
	cout<<endl<<"Strength (STR) - Effects how much damage you do when you attack."<<endl;
	cout<<"Constitution (CONS) - Effects how much health you have."<<endl;
	cout<<"Dexterity (DEX) - Effects if your chance to dodge."<<endl;
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
	intSkillPointsLeft = intSkillPointsLeft - intStr;
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
	intSkillPointsLeft = intSkillPointsLeft - intCons;
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
	intSkillPointsLeft = intSkillPointsLeft - intDef;
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
	intSkillPointsLeft = intSkillPointsLeft - intDex;
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
	PlayerStats[0]=intStr;
	PlayerStats[1]=intCons;
	PlayerStats[2]=intDef;
	PlayerStats[3]=intDex;
	PlayerStats[4]=intLuk;
	cout << string(50, '\n');

	return 'T';
//End of player initialize
}

char startbattle(int intsLevel)
{
	intBattleLevel = intsLevel;
	char charBattleSceneEnding;
	RandomMonster(); //Generate a random monster
	RandomMonsterModifier(); //Give monster random modifier 
	if (MonsterModifier != "") {MonsterName = ConvertToLower(MonsterModifier) + " " + ConvertToLower(MonsterName);} //If monster has a modifier change name to include it
	else {MonsterName = ConvertToLower(MonsterName);}
    charBattleSceneEnding = BattleScene();
	switch(charBattleSceneEnding)
	{
		case 'T' :
			cout << string(50, '\n');
			cout<<"You beat the "<<MonsterName<<endl;
            return 'T';
			break;
		case 'F' : 
			cout << string(50, '\n');
			cout<<"You lost..."<<endl<<" You defeated "<<intBattleLevel - 1 <<" levels.";
            cout<<endl<<"Press enter to close this game and try again!";
            system("pause");
            return 'F';
			break;
		default :
			cout<<endl<<"An error has occurred in the code. Sorry :( The game will exit.";
			system("pause");
			return 'F';
			break;
	}
}


#endif
