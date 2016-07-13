/*****************************************************************************/
#include "core.h"
#include "chest.h"
#include "door.h"
#include "save.h"
/*****************************************************************************/
clsCore::clsCore() {
    //ctor
}
/*****************************************************************************/
clsCore::~clsCore() {
    //dtor
}
/*****************************************************************************/
void clsCore::start() {
    char menuselection;
    m_quit = false;
    SDL_Event event;
    m_level = 1;

    m_screen.start();
    //Show start up splash
    if (!Global::blnDebugMode) {m_screen.ShowStartUp();}
    //do menu loop

    while (!m_quit) {
        menuselection = m_menu.MainMenu();

        switch (menuselection){
        case menuAbout:
            m_menu.AboutMenu();
            break;
        case menuLoad :
            m_save.doLoad();
            doGame();
            break;
        case menuNew:
            //New game
            m_player.initialize();
            //new dungeon
            m_Map.cmain();
            doGame();
            break;
        case menuOptions:
            m_menu.OptionsMenu();
            break;
        case menuError:
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
    //This will be added later
    return;
}
/*****************************************************************************/
void clsCore::ShowInventory() {
    //this will be added later
    return;
}
/*****************************************************************************/
void clsCore::ShowMenu() {
    //this will be added later
    return;
}
/*****************************************************************************/
void clsCore::MovePlayer(SDL_Event dirpress ) {
    //convert key press to enum dir
    char direction;
    LOC temploc, playerloc;
    temploc = playerloc = m_player.getLocation();

    switch ( dirpress.key.keysym.sym ) {
    case SDLK_UP:
    case SDLK_w:
        if (Global::blnDebugMode) {printf("Going up!\n");}
        direction = dirUp;
        temploc.y--;
        break;
    case SDLK_DOWN :
    case SDLK_s:
        if (Global::blnDebugMode) {printf("Going down!\n");}
        direction = dirDown;
        temploc.y++;
        break;
    case SDLK_LEFT:
    case SDLK_a :
        if (Global::blnDebugMode) {printf("Going left!\n");}
        direction = dirLeft;
        temploc.x--;
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        if (Global::blnDebugMode) {printf("Going right!\n");}
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

    /** @todo (GamerMan7799#1#) Get it so tiles return to what they
        were instead of just Dirt Floor */

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
        m_Map.setCell(temploc, tilePlayer);
        m_Map.setCell(playerloc, tileDirtFloor);
        m_player.setLocation(temploc);

        //check if run into monster
        if (rand() % 101 <= DEFINED_MONSTER_SPAWN_CHANCE) {
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
    //battle scence
    //add later

    return;
}
/*****************************************************************************/
void clsCore::HandleEvent(SDL_Event event) {

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
            ShowMenu();
            break;
        case SDLK_TAB:
            ShowConsole();
            break;
        case SDLK_h:
            m_player.doHeal();
            break;
        case SDLK_n:
            m_player.showStatus();
            break;
        } //end switch
    } //end if event
}
/*****************************************************************************/
void clsCore::doLevelUp() {
    //add later

    return;
}
/*****************************************************************************/
void clsCore::doGame() {
    SDL_Event event;

    while (!m_quit) {
        m_screen.DrawMap();
        m_screen.update();
        if (SDL_PollEvent( &event ) ) { HandleEvent(event); }
    } //end while not quit
}
/*****************************************************************************/
