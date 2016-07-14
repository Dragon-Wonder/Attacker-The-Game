#ifndef __MENU__HEADER__
#define __MENU__HEADER__
/*****************************************************************************/
#include "screen.h"
#include <string.h>
/*****************************************************************************/
struct stcButton {
    char type;
    std::string text;
    SDL_Rect cords;
};

typedef struct stcButton button;
/*****************************************************************************/
class clsMenu {
    public:
        clsMenu();
        ~clsMenu();

        char MainMenu(void);

        void AboutMenu(void);
        void OptionsMenu(void);

        char GameMenu(void);

    protected:

    private:
        stcWinAtt* m_window;
        bool clickcheck(LOC,SDL_Rect);


        //SDL_Texture* MakeMessage(std::string, SDL_Color);
};
/*****************************************************************************/
#endif // __MENU__HEADER__
