#ifndef _SAVE_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SAVE_H_INCLUDED__

/*
Made By: Patrick J. Rye
Purpose: A header to hold functions related to saving and loading.
Current Revision: 1.0.1
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
3/2/15	1.0			Patrick Rye			-Original
=============================================================================================================================================================
3/2/15	1.0.1		Patrick Rye			-Quick fix for version not being applied properly.
=============================================================================================================================================================
*/


string ProgramVerison;

void PassProgramVerison(const string Verison)
{
	ProgramVerison = Verison;
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
	int arrbattlesave[7];
	int arrmainsave[1]; //An array of all the values needed to be saved from main.cpp
	arrmainsave[0] = getmainvalue(0);
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
	savefile << ProgramVerison; //Writes version number at the very bottom of save.
	if (fileexists("main.cpp")) {savefile <<"\n"<<"DEBUG";} //Check if this source file is present and write DEBUG at end of save if it does.
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
		else if (i == 7) {if (arrloadnumbers[i]==getmainvalue(0)) {intCheckSum++;}}
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
		else if (i == 7) {x = setmainvalue(0, arrloadnumbers[i]);/*cout<<intLevelStart<<endl;*/}
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
	int intCheckSum = 0;
	for (int i = 0; i < 8; i++)
	{
		if(i<7) {if (arrloadnumbers[i]==getbattlevalue(i)){intCheckSum++;}}
		else if (i == 7) {if (arrloadnumbers[i]==getmainvalue(1)) {intCheckSum++;}}
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
	else {return false;} //Some of the values are wrong, say that the load failed.
}

bool LoadOldSave()
{
	bool blLoadSuccess = false;
	char chrPlayerChoice;
	
	string SaveVerison;
	ifstream checkfileverison;
	checkfileverison.open ("save.bif");
	for(int i = 0; i < 1608; ++i)
		getline(checkfileverison, SaveVerison);
	getline(checkfileverison, SaveVerison);
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
				cout<<"Do you wish to continue with the loading?"<<endl<<"> ";
				cin>>chrPlayerChoice;
				chrPlayerChoice = CharConvertToUpper(chrPlayerChoice);
				switch (chrPlayerChoice)
				{
					case 'Y' :
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
			else {blLoadSuccess = loadfunction();}
			
			if (blLoadSuccess) {return true;}
			else 
			{
				cout<<endl<<"Unable to load save, possibly corrupted."<<endl;
				system("pause");
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
}




#endif
