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
struct stcXY {
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

enum enumTiles {
    tileUnused = 0, //0
    tileDirtWall, //1
    tileDirtFloor, //2
    tileStoneWall, //3
    tileCorridor, //4
    tileDoor, //5
    tileUpStairs, //6
    tileDownStairs, //7
    tileChest, //8
    tilePlayer, //9
    tileLockedDoor //10
};

enum enumDirection {
    dirNone = 0,
    dirUp,
    dirDown,
    dirLeft,
    dirRight
};

enum enumStats {
    statStr = 0,
    statCons,
    statDef,
    statDex,
    statLuk
};

enum enumElements {
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

enum enumMenu {
    menuQuit = 0,
    menuNew,
    menuLoad,
    menuSave,
    menuAbout,
    menuOptions,
    menuError
};

typedef struct stcXY LOC;
typedef struct stcStats stats;
typedef struct stcCurrMax healthmana;
typedef struct stcInv INV;
/*****************************************************************************/
/** This defines the Map height, unless a map you are trying to load is more than
    this it should be kept at 20 */
#define DEFINED_MAP_HEIGHT 22

/** This defines the Map width, unless a map you are trying to load is more than
    this it should be kept at 80 */
#define DEFINED_MAP_WIDTH 40

/** This defines the Map object limit, should try at 100 unless you are testing
    something*/
#define DEFINED_MAP_OBJECT_LIMIT 100

/** How many steps out of 100 will spawn a monster */
#define DEFINED_MONSTER_SPAWN_CHANCE 15

#define DEFINED_MAP_ROOM_CHANCE 75

#define DEFINED_MAP_CORRIDOR_CHANCE 25
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
