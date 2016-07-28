#include "save.h"
#include "player.h"
#include "rooms.h"
#include "version.h"
#include "menu.h"
#include <cstdio>
/*****************************************************************************/
clsSave::clsSave() {
    //ctor
}
/*****************************************************************************/
clsSave::~clsSave() {
    //dtor
}
/*****************************************************************************/
void clsSave::doLoad() {

    /// @todo (GamerMan7799#6#) Add Sanity checker to inputs
    /// @todo (GamerMan7799#9#) Add checksum?


    clsMenu menu;
    char userprompt;
    //check if file exists
    if (!exists()) {
        userprompt = menu.promptUser(prompOkay,"No save found!");
        return;
    }

    //check version numbering
    uint S_MajorNum, S_MinorNum, S_PatchNum;
    char S_SoftwareStatus[15], P_SoftwareStatus[15];
    int intValuesScanned;
    char chrTempString[50];
    FILE* loadfile;
    loadfile = fopen(DEFINED_SAVE_FILE_NAME,"r");

    fgets(chrTempString,50,loadfile);
    sscanf(chrTempString,"%u.%u.%u-%s",&S_MajorNum,&S_MinorNum,&S_PatchNum,&S_SoftwareStatus);
    sscanf(DEFINED_VER_FULLVERSION_STRING,"%*u.%*u.%*u-%s", &P_SoftwareStatus);
    if (Global::blnDebugMode) {
        printf("Save: v %u %u %u %s\n",S_MajorNum,S_MinorNum,S_PatchNum,S_SoftwareStatus);
        printf("Program: v %u %u %u %s\n",DEFINED_VER_MAJOR, DEFINED_VER_MINOR, DEFINED_VER_PATCH, P_SoftwareStatus);
    }

    stats player_stats;
    healthmana health;
    healthmana mana;
    clsPlayer player;

    /// @todo (GamerMan7799#9#) Add save converter into new versions as needed

    //Get level
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.level);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.level = 1;}
    if (Global::blnDebugMode) {printf("Level\t \t \t %u\n", player_stats.level);}

    //Get STR
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.str);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.str = 20;}
    if (Global::blnDebugMode) {printf("STR\t \t \t %u\n", player_stats.str);}

    //Get CONS
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.cons);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.dex = 20;}
    if (Global::blnDebugMode) {printf("CONS\t \t \t %u\n", player_stats.cons);}

    //Get DEX
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.dex);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.dex = 20;}
    if (Global::blnDebugMode) {printf("DEX\t \t \t %u\n", player_stats.dex);}

    //Get DEF
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.def);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.def = 20;}
    if (Global::blnDebugMode) {printf("DEF\t \t \t %u\n", player_stats.def);}

    //Get LUK
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &player_stats.luk);
    if (intValuesScanned < 1) {printf("ERROR!"); player_stats.luk = 20;}
    if (Global::blnDebugMode) {printf("LUK\t \t \t %u\n", player_stats.luk);}

    //get Health
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &health.curr);
    if (intValuesScanned < 1) {printf("ERROR!"); health.curr = 255;}
    if (Global::blnDebugMode) {printf("Health\t \t \t %u\n", health.curr);}

    //get mana
    fgets(chrTempString,5,loadfile);
    intValuesScanned = sscanf(chrTempString, "%X", &mana.curr);
    if (intValuesScanned < 1) {printf("ERROR!"); mana.curr = 255;}
    if (Global::blnDebugMode) {printf("Mana\t \t \t %u\n", mana.curr);}

    char tempTile;
    Dungeon d;
    //get rooms
    for (int x = 0; x < DEFINED_MAP_WIDTH; x++) {
        for (int y = 0; y < DEFINED_MAP_HEIGHT; y++) {
            fgets(chrTempString,5,loadfile);
            intValuesScanned = sscanf(chrTempString, "%X", &tempTile);
            if (intValuesScanned < 1) {printf("ERROR!"); tempTile = tileUnused;}
            d.setCell(x,y,tempTile);
        }
    }
    if (Global::blnDebugMode) {printf("Room tiles loaded.\n");}
    /// @todo (GamerMan7799#9#) Allow program debug set from file?
    fclose(loadfile);
    return;
}
/*****************************************************************************/
void clsSave::doSave() {
    char userprompt;
    clsMenu menu;
    //check if save exists
    if (exists()) {
        userprompt = menu.promptUser(promptYesNo,"Save already exists. Overwrite?");
        switch (userprompt) {
        case returnYes:
            break;
        case returnNo:
        case returnError:
        default:
            return;
            break;
        }
    }

    FILE* savefile = fopen(DEFINED_SAVE_FILE_NAME,"w");

    stats player_stats;
    healthmana health;
    healthmana mana;
    clsPlayer player;
    player_stats = player.getStats();
    health = player.getHealth();
    mana = player.getMana();

    Dungeon d;

    fprintf(savefile,DEFINED_VER_FULLVERSION_STRING);
    fprintf(savefile,"\n");
    //Add Stats + level
    fprintf(savefile, "%X\n",player_stats.level);
    fprintf(savefile, "%X\n",player_stats.str);
    fprintf(savefile, "%X\n",player_stats.cons);
    fprintf(savefile, "%X\n",player_stats.dex);
    fprintf(savefile, "%X\n",player_stats.def);
    fprintf(savefile, "%X\n",player_stats.luk);

    //Save current mana and health
    //don't need to save max because we will just recalc it
    fprintf(savefile,"%X\n",health.curr);
    fprintf(savefile,"%X\n",mana.curr);

    uchar level;
    for (int x = 0; x < DEFINED_MAP_WIDTH; x++) {
        for (int y = 0; y < DEFINED_MAP_HEIGHT; y++) {
            fprintf(savefile,"%X\n",d.getCell(x,y));
        }
    }

    if (Global::blnDebugMode) { fprintf(savefile,"DEBUG"); }
    fclose(savefile);
    if(exists() && Global::blnDebugMode) {printf("Save created.\n");}
    return;
}
/*****************************************************************************/
bool clsSave::exists() {
	FILE* pTempFile = fopen(DEFINED_SAVE_FILE_NAME, "r");
	if (pTempFile == NULL) {return false;}
	else {return true;}
}
/*****************************************************************************/
