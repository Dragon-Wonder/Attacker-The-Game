#ifndef __CONFIG__HEADER__
#define __CONFIG__HEADER__
/*****************************************************************************/
#include <cstdio>
/*****************************************************************************/
#include "global.h"
/*****************************************************************************/
/** @struct ConfigValues
    This Structure holds all of the different config values together. */
struct ConfigValues {
	uint uintScreenWidth;       /**< Screen width, only used if specifically called. */
	uint uintScreenHeight;      /**< Screen height, only used if specifically called. */
};

/** @enum configValueSpot
  * Holds all of the spots for the config values that can be used to return just one config value.
  * See clsConfig::getvalues
  */
enum configValueSpot {
	cnfgScreenWidth = 0,/**< 0: Spot for screen width value. */
	cnfgScreenHeight    /**< 1: Spot for screen height value. */
};

typedef struct ConfigValues Configures;
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class clsConfig config.h "src/config.h"
/// @brief This class will hold all of the values and functions related to the
///        config file.
/////////////////////////////////////////////////

class clsConfig {
	//public:
	private:
		//Members
		/** The config file name. */
		const char* m_FileName = DEFINED_CONFIG_FILE_NAME;

		/** Pointer to the config file open in memory. */
		FILE* m_configFile;

		/** All the config values together. */
		static Configures m_values;

		//Functions
		char verisonCheck(const char *ConfigVerison);
		bool exists(void);
		void make(void);
		void load(void);

	public:
		//Default Constructor
		clsConfig();
		//Functions
		void initialize(void);
		Configures getvalues(void); //Get all values
		uint getvalues(uchar); //Get just one value (use enum above to define which one).
};
/*****************************************************************************/
#endif
