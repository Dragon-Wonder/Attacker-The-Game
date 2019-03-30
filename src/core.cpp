/*****************************************************************************/
#include "core.h"
#include "chest.h"
#include "door.h"
#include "save.h"
/*****************************************************************************/
//General Todos
/** \todo (Gamerman7799#9#): Finish Doxygen support */
/** \todo (Gamerman7799#9#): Add music */
/*****************************************************************************/
clsCore::clsCore() {
    //ctor
}
/*****************************************************************************/
clsCore::~clsCore() {
    //dtor

   //SDL_KillThread(exit_thread);
}
/*****************************************************************************/
void clsCore::start() {
    /////////////////////////////////////////////////
    /// @brief The "main" function. Handles all of the starting and most of the
    ///        core functions.
    /////////////////////////////////////////////////
    char menuselection;
    m_quit = false;
    //SDL_Event event;
    m_level = 1;

    m_screen.start();
    //Show start up splash
    //m_screen.ShowStartUp();

    //int data = 101;
    //exit_thread = SDL_CreateThread(exit_check, "Exit", NULL);

    while (!m_quit) {
        menuselection = m_menu.MainMenu();

        switch (menuselection){
        case menuAbout:
            m_menu.AboutMenu();
            if (Global::blnDebugMode) {printf("About shown.\n");}
            break;
        case menuLoad :
            if (Global::blnDebugMode) {printf("Loading Save\n");}
            m_save.doLoad();
            m_Map.playerfind();
            doGame();
            break;
        case menuNew:
            if (Global::blnDebugMode) {printf("New Game.\n");}
            //New game
            m_menu.promptUser(prompOkay, "Press any button then use the terminal to initialize the player.");
            m_player.initialize();
            //new dungeon
            m_Map.cmain();
            doGame();
            break;
        case menuOptions:
            m_menu.OptionsMenu();
            if (Global::blnDebugMode) {printf("Options shown.\n");}
            break;
        case menuError:
            if (Global::blnDebugMode) {printf("Menu Error returned.\n");}
        default:
            printf("ERROR!!! Now closing everything!\n");
            m_screen.showErrors();
        case menuQuit:
            m_quit = true;
            break;
        } //end switch
    } //end loop

    m_screen.~clsScreen();
	printf("\nDone\n");
} //end Core Start
/*****************************************************************************/
void clsCore::ShowConsole() {
    /////////////////////////////////////////////////
    /// @brief Shows the debug console that will allow commands to be entered.
    ///        Currently unimplemented, possibly will never be implemented. I
    ///        have an idea on how to do this, but I'm not sure it will work,
    ///        and since other stuff is more important I haven't tested it yet.
    /////////////////////////////////////////////////
    /// @todo (GamerMan7799#9#) Add debugging console
    return;
}
/*****************************************************************************/
void clsCore::ShowInventory() {
    /////////////////////////////////////////////////
    /// @brief Shows the inventory system. Currently unimplemented.
    /////////////////////////////////////////////////
    /// @todo (GamerMan7799#8#) Add inventory support
    return;
}
/*****************************************************************************/
void clsCore::MovePlayer(SDL_Event dirpress ) {
    /////////////////////////////////////////////////
    /// @brief Handles moving the player, making sure they can move to that spot
    ///        and other related functions.
    ///
    /// @param dirpress = The event that holds the direction that was pressed
    /////////////////////////////////////////////////
    char direction;
    static char lasttile = tileUpStairs;
    LOC temploc, playerloc;
    temploc = playerloc = m_player.getLocation();

    switch ( dirpress.key.keysym.sym ) {
    case SDLK_UP:
    case SDLK_w:
        //if (Global::blnDebugMode) {printf("Going up!\n");}
        direction = dirUp;
        temploc.y--;
        break;
    case SDLK_DOWN :
    case SDLK_s:
        //if (Global::blnDebugMode) {printf("Going down!\n");}
        direction = dirDown;
        temploc.y++;
        break;
    case SDLK_LEFT:
    case SDLK_a :
        //if (Global::blnDebugMode) {printf("Going left!\n");}
        direction = dirLeft;
        temploc.x--;
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        //if (Global::blnDebugMode) {printf("Going right!\n");}
        direction = dirRight;
        temploc.x++;
        break;
    default:
        if (Global::blnDebugMode) {printf("Going nowhere!\n");}
        direction = dirNone;
        m_audio.playSound(soundBump,1);
        return;
        break;
    } //end case

    //check if player stepping in valid place
    clsDoor door;
    clsChest chest;

    switch ( m_Map.getCell(temploc) ) {
        //Any of the floor tiles that can be walked on
    case tileDirtFloor:
    case tileCorridor:
    case tileDoor:
    case tileUpStairs:
        m_audio.playSound(soundStep,1);
        m_Map.setCell(playerloc, lasttile);
        lasttile = m_Map.getCell(temploc);
        m_Map.setCell(temploc, tilePlayer);
        m_player.setLocation(temploc);

        //check if run into monster
        if (rand() % 101 <= DEFINED_MONSTER_SPAWN_CHANCE) {
            m_menu.promptUser(prompOkay,"You encountered a monster! Use the terminal to fight it.");
            BattleScene();
            if ( m_quit ) {return;} //if player dies in battle
        } //end if monster
        break;

        //special tiles
    case tileChest:
        m_audio.playSound(soundChing,1);

        chest.activate();

        m_audio.playSound(soundStep,1);
        m_Map.setCell(temploc, tilePlayer);
        m_Map.setCell(playerloc, tileDirtFloor);
        m_player.setLocation(temploc);

        break;
    case tileLockedDoor:
        door.activate();

        m_audio.playSound(soundStep,1);
        m_Map.setCell(temploc, tilePlayer);
        m_Map.setCell(playerloc, tileDirtFloor);
        m_player.setLocation(temploc);
        break;

    case tileDownStairs :
        m_audio.playSound(soundLevelUp,1);
        doLevelUp();
        return;
        break;

    //Tiles you can't walk through
    case tileDirtWall:
    case tileStoneWall:
    case tileUnused:
        m_audio.playSound(soundBump,2);
        break;
    } //end switch tile

    door.~clsDoor();
    chest.~clsChest();
    return;
}
/*****************************************************************************/
void clsCore::BattleScene() {
    /////////////////////////////////////////////////
    /// @brief Will handle everything related to battling
    /////////////////////////////////////////////////
    m_monster.makeMonster(m_level);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    bool done = false;

    char choice;
    stats mstats = m_monster.getStats();
    stats pstats = m_player.getStats();

    float pCritChance, mCritChance = 0.0;
    float mDamMuli = 0.85;
    float pDamMuli = 1.0;

    uint pDamage, mDamage;
    std::string mob;
    mob = m_monster.getName();

    healthmana phealth, pmana, mhealth;

    do {
        m_player.regenMana();
        phealth = m_player.getHealth();
        pmana = m_player.getMana();
        mhealth = m_monster.getHealth();
        pCritChance = ((pstats.luk)/20.0 + rand()%3) *4.0;
        mCritChance = ((mstats.luk)/20.0 + rand()%3) *4.0;

        if(rand()%101 <= pCritChance) {pDamMuli += 0.375;}
        if(rand()%101 <= mCritChance) {mDamMuli += 0.375;}

        if(Calculations::DodgeCheck(pstats)) {mDamMuli = 0;}
        if(Calculations::DodgeCheck(mstats)) {pDamMuli = 0;}

        /// @todo (gamerMan7799#3#) Implement element damages

        pDamage = (uint)(pDamMuli * Calculations::CalculateDamage(pstats,mstats,25));
        mDamage = (uint)(mDamMuli * Calculations::CalculateDamage(mstats,pstats,25));

        printf("You are fighting a level %i %s\n",m_level,mob.c_str());
        ///@todo (GamerMan7799#1#) add state of being
        printf("It appears to be (WIP)\n\n");
        printf("Your health: %s\n",BarMarker(phealth).c_str());
        printf("Your mana: %s\n\n",BarMarker(pmana).c_str());
        bool valid = false;
        do {
            choice = 'e';
            printf("What would you like to do?\n");
            printf("[A]ttack \t [H]eal \n");
            printf("E[X]it \t Hel[P] \n");
            printf("[R]un away \t Cast [S]pell (WIP!)\n");
            printf("[C]heck scene\n");
            if (Global::blnDebugMode) {printf("[K]ill monster    [D]ebug values\n");}
            printf("> ");
            scanf("\n%c",&choice);
            printf("\n");
            choice = toupper(choice);
            switch(choice) {
            case 'A':
            case 'H':
            case 'X':
            case 'P':
            case 'R':
            case 'S':
            case 'C':
                valid = true;
                break;
            case 'K':
            case 'D':
                if(Global::blnDebugMode) {valid = true;}
                else {printf("You are not in debug mode, and cannot use these commands.\n");}
                break;
            default :
                valid = false;
                printf("Invalid choice, please try again.\n");
                break;
            } //end switch valid
        } while (!valid); // repeat until valid selection
        switch(choice) {
        case 'A':
            //ATTACK!
            /// @todo (GamerMan7799#5#) allow player or monster to attack first based on dex
            /// @todo (GamerMan7799#6#) add stuns
            /// @todo (GamerMan7799#9#) allow monster to do more than just attack
            mhealth.curr -= pDamage;
            phealth.curr -= mDamage;

            /// @todo (GamerMan7799#7#) add better wording for stuff
            if (pDamage > 0) {printf("You hit the %s for %i damage!\n",mob.c_str(),pDamage);}
            else {printf("The %s dodged your attack!\n",mob.c_str());}

            if (pDamMuli > 1.0) {printf("You got a crit!\n");}

            if (mDamage > 0) {printf("The %s hits you for %i damage!\n",mob.c_str(),mDamage);}
            else {printf("You dodged the %s's attack!\n",mob.c_str());}

            if (mDamMuli > 0.85) {printf("The %s got a crit on you!\n",mob.c_str());}

            //check if anyone died.
            if (phealth.curr <= 0) {
                //player died
                GameOver();
                done = true;
                m_quit = true;
            } else if (mhealth.curr <= 0) {
                //Monster dead
                done = true;
            } else {
                //nobody died set new health amounts
                m_monster.setHealth(mhealth);
                m_player.setHealth(phealth);
            }
            break;
        case 'H':
            m_player.doHeal();
            break;






        } //end switch case





        //done = true;
    } while (!done);
    return;
}
/*****************************************************************************/
void clsCore::HandleEvent(SDL_Event event) {
    /////////////////////////////////////////////////
    /// @brief Handles all events to determine what to do.
    ///
    /// @param event = Event that occurred
    /////////////////////////////////////////////////
    if (event.type == SDL_QUIT) {m_quit = true;}
    else if (event.type == SDL_KEYDOWN) {
        //Key has been pressed figure out what to do
        switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_w:
        case SDLK_DOWN:
        case SDLK_s:
        case SDLK_RIGHT:
        case SDLK_d:
        case SDLK_LEFT:
        case SDLK_a:
            MovePlayer(event);
            break;
        case SDLK_q:
            m_quit = true;
            break;
        case SDLK_i:
            ShowInventory();
            break;
        case SDLK_m:
        case SDLK_ESCAPE:
            m_menu.GameMenu();
            break;
        case SDLK_v:
            m_save.doSave();
            break;
        case SDLK_TAB:
            ShowConsole();
            break;
        case SDLK_h:
            m_player.doHeal();
            break;
        case SDLK_l:
            if(Global::blnDebugMode) {doLevelUp();}
            break;
        case SDLK_n:
            m_player.showStatus();
            break;
        } //end switch
    } //end if event
}
/*****************************************************************************/
void clsCore::doLevelUp() {
    /////////////////////////////////////////////////
    /// @brief Handles leveling up, ensures the right functions are run together.
    /////////////////////////////////////////////////
    m_menu.promptUser(prompOkay,"Level up! Use the terminal to apply points.");
    m_screen.clearRen();
    m_player.doLevelup();
    m_Map.cmain();
    m_screen.DrawMap();
    m_screen.update();
    return;
}
/*****************************************************************************/
void clsCore::doGame() {
    /////////////////////////////////////////////////
    /// @brief The main game loop. Draws Map, Updates SDL Screen, and
    ///        polls for events
    /////////////////////////////////////////////////
    SDL_Event event;
    if(Global::blnDebugMode) {printf("Game started.\n");}

    while (!m_quit) {
        m_screen.DrawMap();
        m_screen.update();
        if (SDL_PollEvent( &event ) ) { HandleEvent(event); }
    } //end while not quit
}
/*****************************************************************************/
std::string clsCore::BarMarker(healthmana a) {
	std::string TempHealthBar = "<";
	int HealthPercent = (int)((a.curr * 100)/a.max);
	for (unsigned char Bar = 0; Bar < 20; Bar++) {
		if (HealthPercent >= 5) {TempHealthBar += "=";}
		else {TempHealthBar += " ";}
		HealthPercent -= 5;
	}
	TempHealthBar += ">";
	//cout<<TempHealthBar<<endl;
	return TempHealthBar;
}
/*****************************************************************************/
void clsCore::GameOver() {
    /// @todo (GamerMan7799#9#) Add better losing message, (add score?)
    printf("\n\n\n\n\nYou died, thanks for playing.\n");
}
/*****************************************************************************/
void clsCore::Winner() {
    /// @todo (GamerMan7799#9#) Add better winning message, (add score?)
    printf("\n\n\n\n\n\n\nYou WIN!\n");
}
/*****************************************************************************/
int clsCore::exit_check(void* data) {
    SDL_Event event;
    do {
        //While there's events to handle
        while( SDL_PollEvent( &event ) ) {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT ) {
                //Quit the program
                m_quit = true;
            }
        }
    } while ( !m_quit );

    return 1;
}
/*****************************************************************************/
