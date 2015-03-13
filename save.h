#ifndef _SAVE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SAVE_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions related to saving and loading.
Current Revision: 1.0
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM BETA TO GAMMA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	

=============================================================================================================================================================		
*/


string ProgramVerison;
bool blSaveDebugMode = false;


//This function is needed to pass the version of the program (a constant string in main.cpp)
//and place it in the variable here called ProgramVerison for purposes of calling it in this header.
void PassProgramVerison(const string Verison) {ProgramVerison = Verison;}

int SanityChecker(int intValueLocation, int intValueCheck)
{
	/*Checks sanity of load.
	If load is trying to call a room that doesn't exist, stats that should not be possible
	or a level that is too high return a 1 for an error, otherwise return 0 for no error.*/
	if (intValueLocation < 0) {return 1;}
	else if (intValueLocation <= 4) {if (intValueCheck < 1 || intValueCheck > 256) {return 1;}} 
	/* 256 is the highest value a stat can have assuming that they put 96 points when they created the character, 
	   and put all 20 points in that stat for the 8 level ups.*/
	else if (intValueLocation <= 6) {return 0;} //Don't bother checking health values since they are just going to be recalculated later.
		else if (intValueLocation == 7) {if (intValueCheck < 0 || intValueCheck > 4) {return 1;}} //Check the current status
	else if (intValueLocation == 8) {if (intValueCheck < 1 || intValueCheck > 10) {return 1;}} //Check the level.
	else if (intValueLocation < 1609) {if (intValueCheck < 0 || intValueCheck > 9) {return 1;}} //Check the dungeon.
	else {return 1;} //Invalid number on array.
	
	return 0; //Value is okay, return 0 for no error found.	
}

char savefunction()
{
	/*
	Testing a possible save function.
	2 Return values possible.
	T = True, save succeeded.
	F = False, save failed.
	*/
	int intCheckSum = 0;
	int arrbattlesave[8];
	int arrmainsave[1]; //An array of all the values needed to be saved from main.cpp, its an array in the case that later I add more stuff to be saved.
	arrmainsave[0] = getmainvalue(0);
	int arrroomsave[80][20];
	for (int i = 0; i < 8; i++) {arrbattlesave[i] = getbattlevalue(i);} //Build array of player stats, and player health.
	for (int y = 0; y < 20; y++) {for (int x = 0; x < 80; x++) {arrroomsave[x][y] = d.getCell(x,y);}} //Build array of the dungeon.
	ofstream savefile;
	savefile.open ("save.bif");
	
	for (int i = 0; i < 8; i++) {savefile << arrbattlesave[i] << "\n";} 

	for (int i = 0; i < 1; i++) {savefile << arrmainsave[i] << "\n";}

	for (int y = 0; y < 20; y++) {for (int x = 0; x < 80; x++) {savefile << arrroomsave[x][y] << "\n";}}
	
	savefile << ProgramVerison; //Writes version number at the very bottom of save.
	if (fileexists("main.cpp") || blSaveDebugMode) {savefile <<"\n"<<"DEBUG";} //Check if source code is present and write DEBUG at end of save if it does.
	savefile.close();
	
	//Save will now attempt to "load" the save it just made and compare it to the data available.
	//Checks to see if save is correct or not.
	ifstream loadfile("save.bif");
	int arrloadnumbers[1609];
	for(int i = 0; i < 1609; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	for (int i = 0; i < 9; i++)
	{
		if(i < 8) {if (arrloadnumbers[i]==arrbattlesave[i]){intCheckSum++;}}
		else {if (arrloadnumbers[i]==getmainvalue(0)) {intCheckSum++;}}
	} 
	int num = 8;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	if (blSaveDebugMode) {cout<<endl<<endl<<intCheckSum;}
	if(intCheckSum >= 1609) {return 'T';} //All of the saved values are correct if it equals 1608.
	else {return 'F';} //Some of the values are wrong, say that the save failed.
}

bool loadfunction()
{
	ifstream loadfile("save.bif");
	int arrloadnumbers[1609];
	for(int i = 0; i < 1609; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	
	//Floor all the values in the array.
	for (int i = 0; i < 1609; i++ ) {arrloadnumbers[i]=floor(arrloadnumbers[i]);}
	
	int intNumOfErrors = 0; //Keeps track of how many errors it find, if greater than 1 cancel load.
	
	for (int i = 0; i < 1609; i++) {intNumOfErrors += SanityChecker(i,arrloadnumbers[i]);} //Checks sanity of the load.
	
	if (intNumOfErrors > 0) {return false;} //If any errors found, cancel load with a false.
	
	for (int i = 0; i < 9; i++)
	{
		if(i < 8) {setbattlevalue(i,arrloadnumbers[i]);/*cout<<arrloadnumbers[i]<<endl;*/}
		else {setmainvalue(0, arrloadnumbers[i]);/*cout<<intLevelStart<<endl;*/}
	}
	int num = 8;
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
	for(int i = 0; i < 1609; i++) {checkfile>>arrloadnumbers[i];} //Rebuild the array.
	checkfile.close();
	int intCheckSum = 0;
	for (int i = 0; i < 9; i++)
	{
		if(i < 8) {if (arrloadnumbers[i]==getbattlevalue(i)){intCheckSum++;}}
		else if (i == 8) {if (arrloadnumbers[i]==getmainvalue(1)) {intCheckSum++;}}
	} 
	num = 8;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	if (blSaveDebugMode) {cout<<endl<<endl<<intCheckSum;}
	if(intCheckSum >= 1609) {return true;} //All of the saved values are correct if it equals 1609.
	else {return false;} //Some of the values are wrong, say that the load failed.
	return false;
}

bool LoadOldSave()
{
	bool blLoadSuccess = false;
	char chrPlayerChoice;
	
	string SaveVerison;
	string DebugModeLine;
	
	ifstream checkfileverison;
	checkfileverison.open ("save.bif");
	for(int i = 0; i < 1609; ++i)
		getline(checkfileverison, SaveVerison);
	getline(checkfileverison, SaveVerison);
	getline(checkfileverison, DebugModeLine);
	checkfileverison.close();

	
	
	SaveDetected:
	cout<<"Previous save has been detected, would you like to load?"<<endl<<"Y or N"<<endl;
	cout<<"> ";
	cin>>chrPlayerChoice;
	chrPlayerChoice = CharConvertToUpper(chrPlayerChoice);
	switch (chrPlayerChoice)
	{
		case 'Y' :
			//Program does a quick check if the save is the same version as the game.
			if ((SaveVerison != ProgramVerison))
			{
				DifferentVersion:
				cout <<endl<<"Save version does not match the game version."<<endl;
				cout<<"I recommend using the same save version as the game, as things could break."<<endl;
				cout<<"Game version: "<<ProgramVerison<<endl<<"Save version: "<<SaveVerison<<"."<<endl;
				cout<<"Do you wish to continue with the loading?"<<endl<<"Y or N"<<endl<<"> ";
				cin>>chrPlayerChoice;
				chrPlayerChoice = CharConvertToUpper(chrPlayerChoice);
				switch (chrPlayerChoice)
				{
					case 'Y' :
						if (DebugModeLine == "DEBUG") {setdebugmode(true); blSaveDebugMode = true;}
						blLoadSuccess = loadfunction();
						break;
					case 'N' :
						return false;
						break;
					default :
						cout<<endl<<"Invalid choice, please try again."<<endl;
						goto DifferentVersion;
						break;
				}
			}
			else {if (DebugModeLine == "DEBUG") {setdebugmode(true); blSaveDebugMode = true;} blLoadSuccess = loadfunction();}
			
			if (blLoadSuccess) {return true;}
			else 
			{
				cout<<endl<<"Unable to load save, possibly corrupted."<<endl;
				getchar();
				return false;
			}
			break;
		case 'N' :
			return false;
			break;
		default :
			cout<<endl<<"Invalid choice, please try again."<<endl;
			goto SaveDetected;
			break;
	//End of switch
	}
	return false;
}

#endif
