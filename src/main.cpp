/*****************************************************************************/
/////////////////////////////////////////////////
/// @file       Main.cpp
/// @brief      Holds all the main functions.
/// @author     GamerMan7799
/// @author     xPUREx
/// @version    0.9.5-Alpha
/// @date       2015-2016
/// @copyright  Public Domain Unlicense.
/////////////////////////////////////////////////
/*****************************************************************************/
#include "version.h"
#include "config.h"
#include "core.h"
/*****************************************************************************/
namespace Global {
    /** Holds if build is in debug mode, this can happen if
        DEFINED_BUILD_MODE_PRIVATE is defined in the complier */
#ifdef DEFINED_BUILD_MODE_PRIVATE
    const bool blnDebugMode = true;
#else
    const bool blnDebugMode = false;
#endif
} //end namespace Global
/*****************************************************************************/
int main(int argc, char *argv[]) {
    /////////////////////////////////////////////////
    /// @brief The main function. Just runs clsCore.start
    ///
    /// @param argc = Something required by SDL
    /// @param argv = Something required by SDL
    /// @return 0 for successfully ran, or 1 for an error happened.
    ///
    /////////////////////////////////////////////////

    if ( DEFINED_VER_STATUS_SHORT == "a" ) {
        printf("This version is an Alpha, meaning that we cannot be sure that it works correctly. ");
        printf("Any features that you see may or may not be changed/removed later in the developmental cycle.\n\n");
    } else if ( DEFINED_VER_STATUS_SHORT == "b" ) {
        printf("This version is a Beta, meaning that while it should work very closely to how we intend it to work, ");
        printf("there may still be some bugs that can cause the program to crash.\n\n");
    } else if ( DEFINED_VER_STATUS_SHORT == "rc" ) {
        printf("This version is a Release Candidate, meaning that it is only a few items away from being an Official ");
        printf("Release. There shouldn't be very many bugs but let us know if you find any.\n\n");
    } else if ( DEFINED_VER_STATUS_SHORT == "r" ) {
        printf("This version is the official release for the game. There should not be any bugs, so if you find any ");
        printf("please let us know right away so we can work to fix them.\n\n");
    } else {
        printf("This version is not properly labeled. There is a mistake in the version.h file.\n\n");
    }


    //Run config stuff
    clsConfig cnfg;
    cnfg.initialize();

    clsCore CCore;
    CCore.start();

	return 0;
}
/*****************************************************************************/
