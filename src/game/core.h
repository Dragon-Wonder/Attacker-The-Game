#ifndef __CORE__HEADER__
#define __CORE__HEADER__
/*****************************************************************************/
#include "../global.h"
#include "rooms.h"
#include "config.h"
#include "../entities/player.h"
#include "../entities/monster.h"
#include "../ui/menu.h"
#include "save.h"
#include "calculations.h"
/*****************************************************************************/
#include <string>
/*****************************************************************************/
#include "SDL2/SDL_thread.h"
/*****************************************************************************/
class clsCore {
  public:
    clsCore();
    ~clsCore();

    void start(void);
  protected:

  private:
    Dungeon m_Map;          /**< The Dungeon object */
    clsPlayer m_player;     /**< The Player object */
    clsScreen m_screen;     /**< The Screen object */
    clsSound m_audio;       /**< The Audio object */
    clsMenu m_menu;         /**< The Menu object */
    clsSave m_save;         /**< The Save object */
    clsMonster m_monster;   /**< The Monster object */

    uint m_level;           /**< Current Level */
    bool m_quit;            /**< Boolean if game should quit */

    void MovePlayer( SDL_Event );
    void ShowInventory(void);
    void ShowConsole(void);
    void BattleScene(void);
    void doGame(void);

    void doLevelUp(void);
    void HandleEvent( SDL_Event );

    int exit_check(void* data);

    void GameOver(void);
    void Winner(void);

    SDL_Thread *exit_thread;

    std::string BarMarker(healthmana);
};
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class clsCore core.h "src/game/core.h"
/// @brief This class holds the core of the program. Almost all of the code
///        is run through this class instead of run in main.cpp.
///        It is run this way because generally it is better practice to keep
///        functions out of the global space (basically no namespace).
///        and having it as a class allows me to do that while keeping things
///        together.
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __CORE__HEADER__
