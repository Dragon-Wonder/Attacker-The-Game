/*****************************************************************************/
#include "config.h"
#include "version.h"
/*****************************************************************************/
/////////////////////////////////////////////////
/// @file config.cpp
/// @brief Holds all of the functions for the Config Class
/////////////////////////////////////////////////
/*****************************************************************************/
Configures clsConfig::m_values;
/*****************************************************************************/
clsConfig::clsConfig() {
  /////////////////////////////////////////////////
  /// @brief This is the default constructor for the Config Class, set values as
  ///        the following defaults before loaded from the file.
  ///        * Screen Height = 0
  ///        * Screen Width = 0
  /////////////////////////////////////////////////

	//Set the values as some default value.
	m_values.uintScreenHeight = 0;
	m_values.uintScreenWidth = 0;
	if (Global::blnDebugMode) {printf("Config Constructor called.\n");}
}
/*****************************************************************************/
bool clsConfig::exists(void) {
  /////////////////////////////////////////////////
  /// @brief Checks if Config.ini already exists
  /// @return TRUE / FALSE Config file exists
  /////////////////////////////////////////////////

	//Returns true or false if config file exists
	FILE* pTempFile = fopen(m_FileName, "r");
	if (pTempFile == NULL) {return false;}
	else {return true;}
}
/*****************************************************************************/
void clsConfig::make(void) {
  /////////////////////////////////////////////////
  /// @brief Will create a new config file, with all of the defaults set in the
  ///        constructor.
  /// @return void
  /////////////////////////////////////////////////

	//Makes the config file
	m_configFile = fopen(m_FileName,"w");
	printf("Config File will now be created!\n");

	fprintf(m_configFile,"Config File for the program.\n");
	fprintf(m_configFile,"%s\n",DEFINED_VER_FULLVERSION_STRING);

    //Write the config with the default values defined when the object was created.
	fprintf(m_configFile, "Only define these if the default screen size doesn't work for you, otherwise leave blank.\n");
	fprintf(m_configFile, "Screen Height: 0\n");
	fprintf(m_configFile, "Screen Width: 0\n");
	fclose(m_configFile);
}
/*****************************************************************************/
char clsConfig::verisonCheck(const char *ConfigVerison) {
    /////////////////////////////////////////////////
    /// @brief 	This checks the version number written at the top of the config file
	///         against the internal version number of the program.
	///         If it finds a difference in Software status or a Major revision change the config HAS to be replaced.
	///         A Minor revision will result in a prompt to the user about if it should be replaced.
	///         And if only a patch change is found then it will just use the old config
	///         Lastly if no change is found then use the config of course.
    ///
    /// @param ConfigVersion = The Version number loaded from the config file
    /// @return NEWCONFIG / USECONFIG / PROMPTUSER
    /////////////////////////////////////////////////

	uint C_MajorNum, C_MinorNum, C_PatchNum;
	char C_SoftwareStatus[15], P_SoftwareStatus[15];
	sscanf(ConfigVerison,"%u.%u.%u-%s",&C_MajorNum,&C_MinorNum,&C_PatchNum,&C_SoftwareStatus);
	sscanf(DEFINED_VER_FULLVERSION_STRING,"%*u.%*u.%*u-%s", &P_SoftwareStatus);
	if (Global::blnDebugMode) {
        printf("Config: v %u %u %u %s\n",C_MajorNum,C_MinorNum,C_PatchNum,C_SoftwareStatus);
        printf("Program: v %u %u %u %s\n",DEFINED_VER_MAJOR, DEFINED_VER_MINOR, DEFINED_VER_PATCH, P_SoftwareStatus);
    }

    if (DEFINED_VER_STATUS == "Release"){
        //Since the release doesn't have any any ending in the string we have to check this differently
        if (C_SoftwareStatus[0] != ')') {
            if (Global::blnDebugMode) {printf("Software Status not outdated.\n");}
            return promptUse;
        }
    } else {
        if ( P_SoftwareStatus[0] != C_SoftwareStatus[0]) {
            if (Global::blnDebugMode) {printf("Software Status outdated.\n");}
            return promptNew;
        }
    }

    if (DEFINED_VER_MAJOR != C_MajorNum) {
        if (Global::blnDebugMode) {printf("Major number outdated.\n");}
        return promptNew;
    } else if (DEFINED_VER_MINOR != C_MinorNum) {
        if (Global::blnDebugMode) {printf("Minor number outdated.\n");}
        return promptPrompt;
    } else {
        if (Global::blnDebugMode) {printf("Nothing outdated.\n");}
        return promptUse;
    }
    return promptUse;
}
/*****************************************************************************/
void clsConfig::load(void) {
    /////////////////////////////////////////////////
    /// @brief Loads all of the values from the config file and places them where
    ///        they need to go. Will also check these values can if they are not what they
    ///        should be (A floating point on an int value) it will set them back to default.
    /// @return void
    /////////////////////////////////////////////////
    int intValuesScanned;
	char chrTempString[50];

	//Get blank line explaining screen sizes
	//Need two fgets because the line is more than 50 characters long.
	fgets(chrTempString,50,m_configFile);
	fgets(chrTempString,50,m_configFile);

	//Get Screen Height
	fgets(chrTempString,50,m_configFile);
    intValuesScanned = sscanf(chrTempString, "%*s %*s %u", &m_values.uintScreenHeight);
    if (intValuesScanned < 1) {printf("ERROR!"); m_values.uintScreenHeight = 0;}
    if (Global::blnDebugMode) {printf("Screen Height \t \t \t %u\n", m_values.uintScreenHeight);}

    //Get Screen Width
    fgets(chrTempString,50,m_configFile);
    intValuesScanned = sscanf(chrTempString, "%*s %*s %u", &m_values.uintScreenWidth);
    if (intValuesScanned < 1) {printf("ERROR!"); m_values.uintScreenWidth = 0;}
    if (Global::blnDebugMode) {printf("Screen Width \t \t \t %u\n", m_values.uintScreenWidth);}


	fclose(m_configFile);
	printf("\n\n");
}
/*****************************************************************************/
void clsConfig::initialize(void) {
    /////////////////////////////////////////////////
    /// @brief This is the main function that should be called to check the
    ///        config file. It will check if the config exists, (create one if it doesn't).
    ///        If it does check the version number and do what needs to be done there. Then
    ///        finally load all the values if safe to do so.
    /// @return void
    /////////////////////////////////////////////////

	char chrTempString[50], chrConfigVerison;
	bool blnAnswered = false; //this is used for a fix for an issue I was facing.
                              //I'll figure out a better method later.

	if (exists() != true) {
		printf("Config file was not found; creating now one\n");
		make();
	} else {
		m_configFile = fopen(DEFINED_CONFIG_FILE_NAME,"r");
		printf("Config file found; loading values\n");
		fgets(chrTempString,50,m_configFile);
		fgets(chrTempString,50,m_configFile);
		chrConfigVerison = verisonCheck(chrTempString);

		if (chrConfigVerison == promptNew) {
			printf("Current config file out of date. Making new one.\n");
			fclose(m_configFile);
			make();
		}
		else if (chrConfigVerison == promptPrompt) {
			printf("\nThe config file you are using has a different Minor Version than the program.\n");
			printf("The config file should in theory still work with this version but I can't say for sure.\n");
			printf("Would you like to replace the config file with a new one?\n");
			do {
				printf("Y or N\n> ");
				scanf("%c",&chrConfigVerison);
				switch (chrConfigVerison) {
					case 'Y' :
					case 'y' :
						//Replace the config file
						fclose(m_configFile);
						make();
						blnAnswered = true;
						break;
					case 'n' :
					case 'N' :
						//Load the config file
						load();
						blnAnswered = true;
						break;
					default :
						printf("\nUnknown answer; try again.\n");
						break;
				}; //end switch
			} while (!blnAnswered);
		} else { load();}
	} //end if exists
}
/*****************************************************************************/
Configures clsConfig::getvalues(void) {
    /////////////////////////////////////////////////
    /// @brief Returns all the config values in the structure.
    /// @return clsConfig::values
    /////////////////////////////////////////////////

	return m_values;
}
/*****************************************************************************/
uint clsConfig::getvalues(uchar Spot) {
    /////////////////////////////////////////////////
    /// @brief Returns a specific config values.
    /// @param Spot = Number from configValueSpot that references a specific config
    ///               value.
    /// @return Unsigned int from that specifc config value (the boolean will return a 1
    ///         if true or a 0 if false). It will also return a 9999 if the spot entered doesn't
    ///         match a value.
    /////////////////////////////////////////////////

	//Returns just one value from the config.
	//Useful when I don't need ALL the values.
	switch (Spot) {
        case cnfgScreenHeight :
            return m_values.uintScreenHeight;
            break;
        case cnfgScreenWidth :
            return m_values.uintScreenWidth;
            break;
		default :
			return 9999;
			break;
	}; //end switch

	return 9999;
}
/*****************************************************************************/
