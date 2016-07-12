/*****************************************************************************/
#include "screen.h"
#include "rooms.h"
#include "config.h"
#include "image_error.xpm"
/*****************************************************************************/
#include <time.h>
#include <cstdlib>
/*****************************************************************************/
/** \todo (GamerMan7799#5#): Get better images for the game. (Currently just using placeholders)
                           Consider hiring someone? */
/*****************************************************************************/
/////////////////////////////////////////////////
/// @file screen.cpp
/// @brief Holds all of the functions for the Screen Class
/////////////////////////////////////////////////
/*****************************************************************************/
clsScreen::clsScreen() {

}
/*****************************************************************************/
clsScreen::~clsScreen() {
    /////////////////////////////////////////////////
    /// @brief This is the default deconstructor, it will just call
    ///        clsScreen::cleanup to ensure everything is cleared from memory,
    ///        and then quit SDL.
    /////////////////////////////////////////////////
    cleanup();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    if (Global::blnDebugMode) {printf("SDL quit\n");}
}
/*****************************************************************************/
void clsScreen::ShowMap() {
    /////////////////////////////////////////////////
    /// @brief Will update the SDL screen based on the map and player / monster locations.
    /// @return void
    /////////////////////////////////////////////////
    //clear renderer
    SDL_RenderClear(window.ren);
    //copy sky to cover entire screen.
    SDL_RenderCopy(window.ren,textures.maptiles,&clips[tileUnused],NULL);
    SDL_Rect dst;
    //Set the pic size
    dst.w = dst.h = pic_size;

    Dungeon Map;

    //BPLYR tempPlayer = Global::Enty.getPlayerBase();
    LOC offset; //how much the screen is offset by
    LOC place;
    //offset.x = (uint) (round( tempPlayer.location.x / window.width ) * window.width);
    //offset.y = (uint) (round( tempPlayer.location.y / window.height) * window.height);

    //Place the map parts where they belong.
    for (uint y = 0; (y < DEFINED_MAP_HEIGHT); y++) {
        for (uint x = 0; (x < DEFINED_MAP_WIDTH); x++) {
            //update where we're trying to put the texture.
            dst.x = (x * pic_size);
            dst.y = (y * pic_size);

            place.x = x;
            place.y = y;

            //Load the map.
            switch( Map.getCell(place) ) { //Use this to make sure we aren't try to load a non-existing part
            case tileDirtWall :
            case tileDirtFloor :
            case tileStoneWall :
            case tileCorridor :
            case tileDoor :
            case tileUpStairs :
            case tileDownStairs :
            case tileChest :
            case tilePlayer :
            case tileLockedDoor :
                SDL_RenderCopy(window.ren, textures.maptiles, &clips[Map.getCell(place)], &dst);
                break;
            default:
                //Don't know what this is so display an error texture.
                SDL_RenderCopy(window.ren, textures.errortex, NULL, &dst);
                break;
            } //end switch
        } //end for x
    } //end for y

    //dst.x = tempPlayer.location.x - offset.x; //Fix this later, doesn't account for screen shifts but I want to work on getting velocity working
    //dst.y = tempPlayer.location.y - offset.y;
    SDL_RenderCopy(window.ren, textures.maptiles, &clips[tilePlayer], &dst);

    //Write messages only if Message font is loaded.
    if (blnloaded.blnMessageFont) {
        writemessage();
    }
    //show renderer
    SDL_RenderPresent(window.ren);
}
/*****************************************************************************/
void clsScreen::cleanup(void) {
    /////////////////////////////////////////////////
    /// @brief This will attempt to delete Textures, and the Window / Renderer
    ///        from memory if their representative loaded boolean is true. Will delete
    ///        * Map tile textures
    ///        * Error textures
    ///        * Message Font
    ///        * Message texture
    ///        * Renderer
    ///        * Window
    ///
    /// @return void
    /////////////////////////////////////////////////
    if (blnloaded.blnMapTiles) {
        SDL_DestroyTexture(textures.maptiles);
        blnloaded.blnMapTiles = false;
        if (Global::blnDebugMode) {printf("Tiles texture destroyed\n");}
    }

    if (blnloaded.blnErrortex) {
        SDL_DestroyTexture(textures.errortex);
        blnloaded.blnErrortex = false;
        if (Global::blnDebugMode) {printf("Error texture destroyed\n");}
    }

    if (blnloaded.blnMessageFont) {
        TTF_CloseFont(MessageFont);
        blnloaded.blnMessageFont = false;
        if (Global::blnDebugMode) {printf("Message font destroyed\n");}
    }

    if (blnloaded.blnMessage) {
        SDL_DestroyTexture(textures.texmessage);
        blnloaded.blnMessage = false;
        if (Global::blnDebugMode) {printf("Message texture destroyed\n");}
    }

	if (blnloaded.blnRenderer) {
        SDL_DestroyRenderer(window.ren);
        blnloaded.blnRenderer = false;
        if (Global::blnDebugMode) {printf("Renderer destroyed\n");}
    }
	if (blnloaded.blnWindow) {
        SDL_DestroyWindow(window.win);
        blnloaded.blnWindow = false;
        if (Global::blnDebugMode) {printf("Window destroyed\n");}
    }
}
/*****************************************************************************/
void clsScreen::error(void) {
    /////////////////////////////////////////////////
    /// @brief Will print out the error generated by SDL if something goes wrong
    /// @return void
    /////////////////////////////////////////////////
    cleanup();
    //Global::blnError = true;
    printf("SDL error: %s\n", SDL_GetError());
    printf("TTF error: %s\n", TTF_GetError());
    printf("IMG error: %s\n", IMG_GetError());
    bln_SDL_started = false;
	getchar();
}
/*****************************************************************************/
void clsScreen::loadTextures() {
    /////////////////////////////////////////////////
    /// @brief Will load all the images that will be needed.
    /// @return void
    ////////////////////////////////////////////////

    std::string path = DEFINED_DEFAULT_IMAGE_PATH;
    path += "tiles.png";

    //Load the error texture first.
    SDL_Surface* temp = IMG_ReadXPMFromArray(image_error_xpm);
    textures.errortex = (temp == nullptr) ? nullptr : SDL_CreateTextureFromSurface(window.ren,temp);
	if (textures.errortex == nullptr) {
        printf("Failed to create texture.\n");
        error();
	} else {
	    if (Global::blnDebugMode) {printf("Surface to texture successful\n");}
	    blnloaded.blnErrortex = true;
    }

    //Now load the tiles
    temp = IMG_Load(path.c_str());
	textures.maptiles = (temp == nullptr) ? nullptr : SDL_CreateTextureFromSurface(window.ren,temp);
	SDL_FreeSurface(temp);
	if (textures.maptiles == nullptr) {
        //Cannot make texture; replace the clips to be all 0,0
        //and set it to use the error texture instead.
        printf("Tiles could not be converted to texture.\n");
        textures.maptiles = textures.errortex;
        for (uchar i = 0; i < DEFINED_NUM_MAP_TILES; i++) {
            clips[i].x = clips[i].y = 0;
        }
        blnloaded.blnMapTiles = true;
        return;
	} else {
	    if (Global::blnDebugMode) {printf("Tiles converted to texture successful\n");}
	    blnloaded.blnMapTiles = true;
    }
}
/*****************************************************************************/
void clsScreen::writemessage(void) {
    /////////////////////////////////////////////////
    /// @brief Now work on Making the messages that will appear on the screen
    ///
    ///        I imagine that I am doing terrible programing things
    ///        With how I'm switch between char's and strings but whatever
    /// @return void
    /////////////////////////////////////////////////

    // These are char arrays that will act as "Strings" for building the messages to appear
    /*char strClock[8];
    char strGenNum[5];
    char strPlayerNum[4];
    char strFitness[7];

    std::string message;
    sprintf(strClock, "%8u", Global::Tick.getClockTime());

    SDL_Surface* surmessage = TTF_RenderText_Solid(MessageFont, strClock, colors.Black);
    textures.texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(window.ren, surmessage);
    if (textures.texmessage == nullptr) {
        printf("Failed to convert message surface to texture.\n");
        error();
        return;
    } else {
        if (Global::blnDebugMode) {printf("Surface texture successfully created\n");}
        blnloaded.blnMessage = true;
    }

    SDL_Rect dst;
    SDL_QueryTexture(textures.texmessage,NULL,NULL, &dst.w, &dst.h);
    dst.y = 0;
    dst.x = width - dst.w;
    SDL_RenderCopy(window.ren, textures.texmessage, NULL, &dst);
    if (Global::blnDebugMode) {printf("Clock placed.\n");}

    PLYR tempPlayer = Global::Enty.getPlayer();

    //Covert all the values into their char arrays
    int valuesscanned;

    //Make the status string
    //Also make sure that each values has at least 1 values scanned in to avoid an error
    message = "Generation: ";
    valuesscanned = sprintf(strGenNum, "%2u", Global::Enty.uchrGenNum);
    if (valuesscanned >= 1) {
        strGenNum[4] = '\0'; //Make sure that the char is null terminated or the program crashes.
        message += std::string(strGenNum);
    }
    message += "     Player: ";
    valuesscanned = sprintf(strPlayerNum, "%3u", Global::Enty.uchrPlayerNum);
    if (valuesscanned >= 1) {
        strPlayerNum[3] = '\0'; //Make sure that the char is null terminated or the program crashes.
        message += std::string(strPlayerNum);
    }
    message += "     Fitness: ";
    valuesscanned = sprintf(strFitness, "%3.2f", tempPlayer.fitness);
    if (valuesscanned >= 1) {
        strFitness[6] = '\0'; //Make sure that the char is null terminated or the program crashes.
        message += std::string(strFitness);
    }
    if (Global::blnDebugMode) {printf("Status message made.\n");}

    surmessage = TTF_RenderText_Solid(MessageFont, message.c_str(),colors.Black);
    textures.texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(window.ren, surmessage);
    if (textures.texmessage == nullptr) {
        printf("Failed to convert message surface to texture.\n");
        blnloaded.blnMessage = false;
        error();
        return;
    } else {
        if (Global::blnDebugMode) {printf("Surface texture successfully created\n");}
        blnloaded.blnMessage = true;
    }

    SDL_QueryTexture(textures.texmessage,NULL,NULL, &dst.w, &dst.h);
    dst.x = (int)(width - dst.w);
    dst.y = height - 30;

    SDL_RenderCopy(window.ren, textures.texmessage, NULL, &dst);
    SDL_FreeSurface(surmessage); */
}
/*****************************************************************************/
void clsScreen::set_clips() {
    /////////////////////////////////////////////////
    /// @brief Set all the locations of the specific tiles in the tiles.png
    ///        Since all of the sizes are the same we will do this all together to save space
    /// @return void
    /////////////////////////////////////////////////

     for (uchar i = 0; i < DEFINED_NUM_MAP_TILES; i++) {
        clips[i].w = clips[i].h = pic_size;
     }

    /*     The Picture Coordinates (x,y)
     *     we multiply this by the pic size to get the clip
     *     +-----+-----+-----+
     *     |(0,0)|(1,0)|(2,0)|
     *     +-----+-----+-----+
     *     |(0,1)|(1,1)|(2,1)|
     *     +-----+-----+-----+
     *     |(0,2)|(1,2)|(2,2)|
     *     +-----+-----+-----+
     *     |(0,3)|(1,3)|(2,3)|
     *     +-----+-----+-----+
     */

     //First Row (Space, Wall, Player)
     clips[tileUnused].x = 0 * pic_size;
     clips[tileUnused].y = 0 * pic_size;

     clips[tileStoneWall].x = 1 * pic_size;
     clips[tileStoneWall].y = 0 * pic_size;

     clips[tilePlayer].x = 2 * pic_size;
     clips[tilePlayer].y = 0 * pic_size;

     //Second Row (Pole, Monster, Coin)
     clips[tileDoor].x = 0 * pic_size;
     clips[tileDoor].y = 1 * pic_size;

     clips[tileLockedDoor].x = 1 * pic_size;
     clips[tileLockedDoor].y = 1 * pic_size;

     clips[tileChest].x = 2 * pic_size;
     clips[tileChest].y = 1 * pic_size;

     //Third Row (Bricks Small, bricks Gray, bricks Green)
     clips[tileCorridor].x = 0 * pic_size;
     clips[tileCorridor].y = 2 * pic_size;

     clips[tileDirtFloor].x = 1 * pic_size;
     clips[tileDirtFloor].y = 2 * pic_size;

     clips[tileDirtWall].x = 2 * pic_size;
     clips[tileDirtWall].y = 2 * pic_size;

     //Fourth Row (Bricks Orange, Bricks Red
     clips[tileDownStairs].x = 0 * pic_size;
     clips[tileDownStairs].y = 3 * pic_size;

     clips[tileUpStairs].x = 1 * pic_size;
     clips[tileUpStairs].y = 3 * pic_size;


}
/*****************************************************************************/
void clsScreen::ShowStartUp() {
    //opening sequence for the game
    //will show the splash image
    /// @todo (GamerMan7799#1#): Add splash
    /// @todo (GamerMan7799#1#): Make splash fade, add splash for company

    SDL_Surface* temp;
    SDL_Texture* splash;

    std::string path = DEFINED_DEFAULT_IMAGE_PATH;
    path += "splash.png";


    //Now load the tiles
    temp = IMG_Load(path.c_str());
	splash = (temp == nullptr) ? nullptr : SDL_CreateTextureFromSurface(window.ren,temp);
	SDL_FreeSurface(temp);
	if (splash == nullptr) {
        //Cannot make texture; show error instead
        printf("Splash could not be converted to texture.\n");
        splash = textures.errortex;
	} else {
	    if (Global::blnDebugMode) {printf("Splash converted to texture successful\n");}
    }

    SDL_RenderClear(window.ren);
    //copy splash to cover entire screen.
    SDL_RenderCopy(window.ren,splash,NULL,NULL);
    SDL_RenderPresent(window.ren);

    //Wait so user can see screen
    wait(5000);

    //clean stuff up

    SDL_RenderClear(window.ren);

    SDL_DestroyTexture(splash);
}
/*****************************************************************************/
void clsScreen::wait(ulong waittime) {
    /////////////////////////////////////////////////
    /// @brief 	Since sleep is usually an OS specific command I made this function
	///         to work as a "sleep" but it doesn't function as a true sleep because the
	///         CPU is still being used, but whatever. It "stops" the program for a bit
	///         which was its point so its gonna stay until I find something better.
    /// @return void
    /////////////////////////////////////////////////

	clock_t now;
	clock_t timerStart;
    ulong pause;

	pause = waittime * (CLOCKS_PER_SEC/1000);
	now = timerStart = clock();

    if ((uint)abs(now - timerStart) < pause) {
        while ( (uint)abs(now - timerStart) < pause) {now = clock();}
    }
}
/*****************************************************************************/
void clsScreen::ShowMenu() {
    //This will have the code for the main menu when I add it
    /// @todo (GamerMan7799#1#): Add main menu

    return;
}
/*****************************************************************************/
void clsScreen::start() {
    /////////////////////////////////////////////////
    /// @brief The default constructor for the SDL screen
    ///        it will try start SDL, and create and window and a renderer,
    ///        then try to load the textures it will need, if any of these fail
    ///        it will set bln_SDL_Started to false and return void, when main in main.cpp
    ///        checks bln_SDL_Started and ends the entire program will it is false.
    ///        If, however, bln_SDL_Started is true it will continue on with the rest of the program.
    /////////////////////////////////////////////////
    //Figure out screen size

    clsConfig cnfg;

    window.width = (cnfg.getvalues(cnfgScreenWidth) == 0) ? 35 * pic_size : cnfg.getvalues(cnfgScreenWidth);
    window.height = (cnfg.getvalues(cnfgScreenHeight) == 0) ? DEFINED_MAP_HEIGHT * pic_size : cnfg.getvalues(cnfgScreenHeight);

    //Set all the booleans to false
    blnloaded.blnWindow = blnloaded.blnRenderer = false;
    blnloaded.blnMapTiles = blnloaded.blnErrortex = false;
    bln_SDL_started = false;

    set_clips();

    //Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        error();
        return;
    } else {
        bln_SDL_started = true;
        if (Global::blnDebugMode) {printf("SDL init successful\n");}
    }

    //Start TTF
    if (TTF_Init() != 0) {
        error();
        return;
    } else {
        if (Global::blnDebugMode) {printf("TTF init successful\n");}
    }

    //Start Image (with only png)
    if (!(IMG_Init( IMG_INIT_PNG )) & IMG_INIT_PNG) {
        error();
        return;
    } else {
        if (Global::blnDebugMode) {printf("IMG init successful\n");}
    }

    window.win = SDL_CreateWindow("Attacker The Game",100, 100, window.width,
                                  window.height, SDL_WINDOW_SHOWN);
    window.ren = (window.win == nullptr) ? nullptr :
                    SDL_CreateRenderer(window.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (window.ren == nullptr) {
        printf("SDL Failed to create renderer.\n");
        error();
        return;
    } else {
        blnloaded.blnRenderer = true;
        if (Global::blnDebugMode) {printf("Renderer creation successful\n");}
    }

    loadTextures();
    if ( !bln_SDL_started ) {return;}

    MessageFont = TTF_OpenFont(DEFINED_MESSAGE_FONT,16); //Opens font and sets size
    if (MessageFont == nullptr) {
        printf("Font failed to load, messages will not appear.");
        blnloaded.blnMessageFont = false;
    } else {
        if(Global::blnDebugMode) {printf("Message font created\n");}
       blnloaded.blnMessageFont = true;
    }

    colors.Black = {0, 0, 0, 0}; //Make the color black for fonts
    colors.White = {255, 255, 255, 0}; //Make the color white for fonts

    //update();
}
/*****************************************************************************/


