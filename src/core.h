#ifndef __CORE__HEADER__
#define __CORE__HEADER__
/*****************************************************************************/
#include "global.h"
#include "screen.h"
#include "rooms.h"
#include "config.h"
#include "player.h"
#include "sound.h"
#include "menu.h"
#include "save.h"
/*****************************************************************************/
class clsCore {
    public:
        clsCore();
        ~clsCore();

        void start(void);
    protected:

    private:
        Dungeon m_Map;
        clsPlayer m_player;
        clsScreen m_screen;
        clsSound m_audio;
        clsMenu m_menu;
        clsSave m_save;
        //clsMonster monster;

        uint m_level;
        bool m_quit;

        void MovePlayer( SDL_Event );
        void ShowInventory(void);
        void ShowConsole(void);
        void BattleScene(void);
        void doGame(void);

        void doLevelUp(void);
        void HandleEvent( SDL_Event );
};
/*****************************************************************************/
#endif // __CORE__HEADER__
