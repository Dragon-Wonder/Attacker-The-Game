#ifndef __CORE__HEADER__
#define __CORE__HEADER__
/*****************************************************************************/
#include "global.h"
#include "screen.h"
#include "rooms.h"
#include "config.h"
#include "player.h"
#include "sound.h"
/*****************************************************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
        //clsMonster monster;

        uint m_level;
        bool m_quit;

        void MovePlayer( SDL_Event );
        void ShowInventory(void);
        void ShowMenu(void);
        void ShowConsole(void);
        void BattleScene(void);

        void doLevelUp(void);
        void HandleEvent( SDL_Event );
};
/*****************************************************************************/
#endif // __CORE__HEADER__
