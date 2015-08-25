/*********************************************************************************************************/
#include "save.h"
#include "global.h"
/*********************************************************************************************************/
unsigned char SanityChecker(unsigned int intValueLocation, int intValueCheck) {
	/*Checks sanity of load.
	If load is trying to call a room that doesn't exist, stats that should not be possible
	or a level that is too high return a 1 for an error, otherwise return 0 for no error.*/
	if (intValueLocation < 0) {return 1;}
	else if (intValueLocation <= 4) {if (intValueCheck < 1 || intValueCheck > 254) {return 1;}}
	/* 255 is the highest possible value for stats as they are all unsigned char and that is the max value*/
	else if (intValueLocation <= 6) {return 0;} //Don't bother checking health values since they are just going to be recalculated later.
	else if (intValueLocation == 7) {if (intValueCheck < 0 || intValueCheck > 7) {return 1;}} //Check the current status
	else if (intValueLocation == 8) {if (intValueCheck < 0 || intValueCheck > 7) {return 1;}} //Checks status counter
	else if (intValueLocation == 9) {if (intValueCheck < 0 || intValueCheck > 254) {return 1;}} //Check number of keys
	else if (intValueLocation <= 11) {return 0;} //Don't bother checking mana values since they are just going to be recalculated later.
	else if (intValueLocation == 12) {if (intValueCheck < 1 || intValueCheck > 10) {return 1;}} //Check the level.
	else if (intValueLocation < 1613) {if (intValueCheck < 0 || intValueCheck > 10) {return 1;}} //Check the dungeon.
	else {return 1;} //Invalid number on array.
	return 0; //Value is okay, return 0 for no error found.
}
/*********************************************************************************************************/
char savefunction() {
	/*
	Testing a possible save function.
	2 Return values possible.
	T = True, save succeeded.
	F = False, save failed.
	*/
	int intCheckSum = 0;
	int arrbattlesave[12];
	int arrmainsave[1]; //An array of all the values needed to be saved from main.cpp, its an array in the case that later I add more stuff to be saved.
	arrmainsave[0] = getmainvalue(0);
	int arrroomsave[80][20];
	for (unsigned char i = 0; i < 12; i++) {arrbattlesave[i] = getbattlevalue(i);} //Build array of player stats, and player health.
	for (unsigned char y = 0; y < 20; y++) {for (unsigned char x = 0; x < 80; x++) {arrroomsave[x][y] = d.getCell(x,y);}} //Build array of the dungeon.
	ofstream savefile;
	savefile.open ("save.bif");
	for (unsigned char i = 0; i < 12; i++) {savefile << arrbattlesave[i] << "\n";}
	for (unsigned char i = 0; i < 1; i++) {savefile << arrmainsave[i] << "\n";}
	for (unsigned char y = 0; y < 20; y++) {for (unsigned char x = 0; x < 80; x++) {savefile << arrroomsave[x][y] << "\n";}}
	savefile << Global::ProgramVerison; //Writes version number at the very bottom of save.
	if (fileexists("main.cpp") || Global::blnDebugMode) {savefile <<"\n"<<"DEBUG";} //Check if source code is present and write DEBUG at end of save if it does.
	savefile.close();
	//Save will now attempt to "load" the save it just made and compare it to the data available.
	//Checks to see if save is correct or not.
	ifstream loadfile("save.bif");
	int arrloadnumbers[1613];
	for(unsigned int i = 0; i < 1613; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	for (unsigned char i = 0; i < 13; i++) {
		if(i < 12) {if (arrloadnumbers[i]==arrbattlesave[i]){intCheckSum++;}}
		else {if (arrloadnumbers[i]==getmainvalue(0)) {intCheckSum++;}}
	}
	unsigned int num = 12;
	for (unsigned char y = 0; y < 20; y++) {
		for (unsigned char x = 0; x < 80; x++) {
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	if (Global::blnDebugMode) {cout<<endl<<endl<<intCheckSum;}
	if(intCheckSum >= 1613) {return 'T';} //All of the saved values are correct if it equals 1608.
	else {return 'F';} //Some of the values are wrong, say that the save failed.
}
/*********************************************************************************************************/
bool loadfunction() {
	ifstream loadfile("save.bif");
	int arrloadnumbers[1613];
	for(unsigned int i = 0; i < 1613; i++) {loadfile>>arrloadnumbers[i];}
	loadfile.close();
	//Floor all the values in the array.
	for (unsigned int i = 0; i < 1613; i++ ) {arrloadnumbers[i]=floor(arrloadnumbers[i]);}
	unsigned int intNumOfErrors = 0; //Keeps track of how many errors it find, if greater than 1 cancel load.
	for (unsigned int i = 0; i < 1613; i++) {intNumOfErrors += SanityChecker(i,arrloadnumbers[i]);} //Checks sanity of the load.
	if (intNumOfErrors > 0) {return false;} //If any errors found, cancel load with a false.
	for (unsigned char i = 0; i < 13; i++) {
		if(i < 12) {setbattlevalue(i,arrloadnumbers[i]);}
		else {setmainvalue(0, arrloadnumbers[i]);}
	}
	unsigned int num = 12;
	for (unsigned char y = 0; y < 20; y++) {
		for (unsigned char x = 0; x < 80; x++) {
			num ++;
			d.setCell(x,y,arrloadnumbers[num]);
		}
	}
	//Double check that all the values loaded are correct.
	ifstream checkfile("save.bif");
	for(unsigned int i = 0; i < 1613; i++) {checkfile>>arrloadnumbers[i];} //Rebuild the array.
	checkfile.close();
	unsigned int intCheckSum = 0;
	for (unsigned char i = 0; i < 13; i++) {
		if(i < 12) {if (arrloadnumbers[i]==getbattlevalue(i)){intCheckSum++;}}
		else if (i == 12) {if (arrloadnumbers[i]==getmainvalue(1)) {intCheckSum++;}}
	}
	num = 12;
	for (unsigned char y = 0; y < 20; y++) {
		for (unsigned char x = 0; x < 80; x++) {
			num ++;
			if (arrloadnumbers[num]==d.getCell(x,y)) {intCheckSum++;}
		}
	}
	if (Global::blnDebugMode) {cout<<endl<<endl<<intCheckSum;}
	if(intCheckSum >= 1613) {return true;} //All of the saved values are correct if it equals 1613.
	else {return false;} //Some of the values are wrong, say that the load failed.
	return false;
}
/*********************************************************************************************************/
bool LoadOldSave() {
	bool blLoadSuccess = false;
	char chrPlayerChoice;
	string SaveVerison;
	string DebugModeLine;
	ifstream checkfileverison;
	checkfileverison.open ("save.bif");
	for(unsigned int i = 0; i < 1613; ++i)
		getline(checkfileverison, SaveVerison);
	getline(checkfileverison, SaveVerison);
	getline(checkfileverison, DebugModeLine);
	checkfileverison.close();
	SaveDetected:
	cout<<"Previous save has been detected, would you like to load?"<<endl<<"Y or N"<<endl;
	cout<<"> ";
	cin>>chrPlayerChoice;
	chrPlayerChoice = CharConvertToUpper(chrPlayerChoice);
	switch (chrPlayerChoice) {
		case 'Y' :
			//Program does a quick check if the save is the same version as the game.
			if ((SaveVerison != Global::ProgramVerison)) {
				DifferentVersion:
				cout <<endl<<"Save version does not match the game version."<<endl;
				cout<<"I recommend using the same save version as the game, as things could break."<<endl;
				cout<<"Game version: "<<Global::ProgramVerison<<endl<<"Save version: "<<SaveVerison<<endl;
				cout<<"Do you wish to continue with the loading?"<<endl<<"Y or N"<<endl<<"> ";
				cin>>chrPlayerChoice;
				chrPlayerChoice = CharConvertToUpper(chrPlayerChoice);
				switch (chrPlayerChoice) {
					case 'Y' :
						if (DebugModeLine == "DEBUG") {Global::blnDebugMode = true;}
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
			else {if (DebugModeLine == "DEBUG") {Global::blnDebugMode = true;} blLoadSuccess = loadfunction();}
			if (blLoadSuccess) {return true;}
			else {
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
/*********************************************************************************************************/
