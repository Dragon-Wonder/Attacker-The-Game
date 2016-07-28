#ifndef __GLOBAL_H_INCLUDED__
#define __GLOBAL_H_INCLUDED__
/*****************************************************************************/
/////////////////////////////////////////////////
/// @file global.h
/// @brief  This holds many items that need to be referenced by several different
///         files, therefore it is easier to just put them here.
/////////////////////////////////////////////////
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup TypeDefs Type Definitions
/// @brief These are defines are just to change type defs.
/// @{
/////////////////////////////////////////////////
typedef unsigned char uchar; /**< Rename unsigned char to uchar because I'm lazy. */
typedef unsigned int uint; /**< Rename unsigned int to uint because I'm lazy. */
typedef unsigned long ulong; /**< Rename unsigned long to ulong because I'm lazy. */
/// @}
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup Structs Structures
/// @brief These are all the different structures that are used throughout the code.
/// @{
/////////////////////////////////////////////////
/** @struct stcXY
    This Structure holds an X and Y location, used for several things */
struct stcXY {
    int x; /**< X direction */
    int y; /**< Y direction */
};

/** @struct stcStats
    This Structure holds all the player and monster stats */
struct stcStats {
	uchar level;    /**< Level from 1 to 10*/
    uchar str;      /**< Effects how much damage you do when you attack.*/
    uchar cons;     /**< Effects how much health you have.*/
    uchar dex;      /**< Effects if your chance to dodge, and if you attack first.*/
    uchar def;      /**< Effects how much damage you take.*/
    uchar luk;      /**< The random chance things will go your way, with dodges, crits, and rare modifiers that appear on monsters.*/
};

/** @struct stcCurrMax
    Holds the current vs max value of something. Used for health and mana */
struct stcCurrMax {
    int curr;       /**< Current */
    int max;        /**< Max*/
};

/** @struct stcInv
    This Structure holds a really simplified inventory of just keys and gold.
    Will likely be expanded into another class later on. */
struct stcInv {
    int keys;       /**< Keys. Used to open locked doors. Can be found on monsters */
    int gold;       /**< Gold. Currently does nothing. */
};
//End of struct group
/// @}
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup enum Enumerators
/// @brief These are all the different enums that are used throughout the code.
/// @{
/////////////////////////////////////////////////
/** Holds all the different tiles that are in tiles.png. */
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
    tileLockedDoor, //10
};

/** Holds all of the directions. */
enum enumDirection {
    dirNone = 0,
    dirUp,
    dirDown,
    dirLeft,
    dirRight
};

/** Holds all of the stats */
enum enumStats {
    statStr = 0,
    statCons,
    statDef,
    statDex,
    statLuk
};

/** Holds all of the different elements (not implemented yet) */
/// @todo (GamerMan7799#4#) Implement elements
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

/** Holds all the different status effects (not implements yet) */
/// @todo (GamerMan7799#4#) Implement status effects
enum enumEffects {
    effectNone = 0,
	effectBlinded,
	effectFrozen,
	effectBurned,
	effectWet,
	effectPoison,
	effectBleeding,
	effectConfused,
	effectParalyzed,
	effectConcussion
};

/** Holds the different menu selections. */
enum enumMenu {
    menuQuit = 0,
    menuNew,
    menuLoad,
    menuSave,
    menuAbout,
    menuOptions,
    menuError
};

/** Holds the different prompt types */
enum promptTypes {
    promptYesNo = 0,
    prompOkay,
    promptNew,
    promptPrompt,
    promptUse
};

/** Holds the different returns from a prompt*/
enum promptReturns {
    returnYes = 0,
    returnNo,
    returnError,
    returnMaybe
};
// end enum groups
/// @}
/*****************************************************************************/
/// @addtogroup TypeDefs
/// @{
typedef struct stcXY LOC;
typedef struct stcStats stats;
typedef struct stcCurrMax healthmana;
typedef struct stcInv INV;
/// @}
/*****************************************************************************/
/////////////////////////////////////////////////
/// @defgroup ChangeableDefines Easily Changeable Defines
/// @brief These are defines that can be changed easily and without much issues.
/// @{
/////////////////////////////////////////////////
/** This defines the Map height, unless a map you are trying to load is more than
    this it should be kept at 35 */
#define DEFINED_MAP_HEIGHT 35

/** This defines the Map width, unless a map you are trying to load is more than
    this it should be kept at 60 */
#define DEFINED_MAP_WIDTH 60

/** This defines the Map object limit, should try at 100 unless you are testing
    something*/
#define DEFINED_MAP_OBJECT_LIMIT 100

/** How many steps out of 100 will spawn a monster */
#define DEFINED_MONSTER_SPAWN_CHANCE 15

/** Chance for a room to spawn when making the map*/
#define DEFINED_MAP_ROOM_CHANCE 75

/** Chance for a corridor to spawn when making the map*/
#define DEFINED_MAP_CORRIDOR_CHANCE 25

/** How many different map tiles there are (used to make the array for clipping). */
#define DEFINED_NUM_MAP_TILES 12

/** Size of each tile in pixels. */
#define DEFINED_PIC_SIZE 16

/** The name of the config file that will be made / read from. */
#define DEFINED_CONFIG_FILE_NAME "Config.ini"

/** Chance for a key on the monster */
#define DEFINED_KEY_SPAWN_CHANCE 25
/// @}
/*****************************************************************************/
//Global namespace
namespace Global {
    extern const bool blnDebugMode;
} //end global namespace
/*****************************************************************************/
#endif // __GLOBAL_H_INCLUDED__
