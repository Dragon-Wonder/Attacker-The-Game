#ifndef __GLOBAL_H_INCLUDED__
#define __GLOBAL_H_INCLUDED__
/*****************************************************************************/
//This file will hold the global references that are need in one place
/*****************************************************************************/
//global typedefs
typedef unsigned char uchar;
/**< Rename unsigned char to uchar because I'm lazy. */

typedef unsigned int uint;
/**< Rename unsigned int to uint because I'm lazy. */

typedef unsigned long ulong;
/**< Rename unsigned long to ulong because I'm lazy. */

/*****************************************************************************/
struct stcLocation {
    int x;
    int y;
};

struct stcStats {
    uchar str;
    uchar cons;
    uchar def;
    uchar dex;
    uchar luk;
};

struct stcCurrMax {
    int curr;
    int max;
};

struct stcInv {
    int keys;
    int gold;
};

enum {
    tileUnused = 0x0, //0
    tileDirtWall = 0x1, //1
    tileDirtFloor = 0x2, //2
    tileStoneWall = 0x3, //3
    tileCorridor = 0x4, //4
    tileDoor = 0x5, //5
    tileUpStairs = 0x6, //6
    tileDownStairs = 0x7, //7
    tileChest = 0x8, //8
    tilePlayer = 0x9, //9
    tileLockedDoor = 0xA //10
};

enum {
    dirNone = 0,
    dirUp,
    dirDown,
    dirLeft,
    dirRight
};

enum {
    statStr = 0,
    statCons,
    statDef,
    statDex,
    statLuk
};

enum {
    elementNone = 0,
    elementPhysical,
    elementFire,
    elementIce,
    elementLight,
    elementDark,
    elementEarth,
    elementWind,
    elementEnergy,
    elementWater
};

typedef struct stcLocation LOC;
typedef struct stcStats stats;
typedef struct stcCurrMax healthmana;
typedef struct stcInv INV;
/*****************************************************************************/
/** This defines the Map height, unless a map you are trying to load is more than
    this it should be kept at 20 */
#define DEFINED_MAP_HEIGHT 20

/** This defines the Map width, unless a map you are trying to load is more than
    this it should be kept at 80 */
#define DEFINED_MAP_WIDTH 80

/** This defines the Map object limit, should try at 100 unless you are testing
    something*/
#define DEFINED_MAP_OBJECT_LIMIT 100

/** How many steps out of 100 will spawn a monster */
#define DEFINED_MONSTER_SPAWN_CHANCE 15
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup ChangeableDefines Easily Changeable Defines
/// @brief These are defines that can be changed easily and without much issues.
/// @{
/////////////////////////////////////////////////
/** How many different map tiles there are (used to make the array for clipping). */
#define DEFINED_NUM_MAP_TILES 11

/** Size of each tile in pixels. */
#define DEFINED_PIC_SIZE 24

/** The name of the config file that will be made / read from. */
#define DEFINED_CONFIG_FILE_NAME "Config.ini"

/// @}
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup ConfigReturns Returns for the Config
/// @brief These are defines that just allow returns from clsConfig::verisonCheck
///        to be more human readable.
/// @{
/////////////////////////////////////////////////

/** Return to make a new config file. */
#define NEWCONFIG 'N'

/** Return to use the current config file. */
#define USECONFIG 'U'

/** Return to prompt the user if they should use / make new config file. */
#define PROMPTUSER 'P'
/// @}
/*****************************************************************************/
//Global namespace
namespace Global {
    extern const bool blnDebugMode;
} //end global namespace
/*****************************************************************************/
#endif // __GLOBAL_H_INCLUDED__
