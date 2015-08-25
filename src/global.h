#ifndef __GLOBAL_HEADER__
#define __GLOBAL_HEADER__
#include <string>
#include "version.h" //holds all the version information
/*********************************************************************************************************/
//Holds global stuff that is needed.
/*********************************************************************************************************/
class Dungeon;
/*********************************************************************************************************/
namespace Global {
    extern bool blnDebugMode;
    const std::string ProgramVerison = DEFINED_VER_FULLVERSION_STRING; //The current version of this program, stored in a save file later on.
}
/*********************************************************************************************************/
extern Dungeon d; //Define the dungeon class as 'd' so I can use functions in there anywhere later in the code.
/*********************************************************************************************************/
#endif // __DUNGEON_HEADER__
