#include "menu.h"
/*****************************************************************************/
clsMenu::clsMenu() {
    //ctor

    clsScreen screen;

    m_window = screen.getWinAtt();
}
/*****************************************************************************/
clsMenu::~clsMenu() {
    //dtor
}
/*****************************************************************************/
char clsMenu::MainMenu() {
    SDL_SetRenderDrawColor( m_window->ren, 0xFF, 0xFF, 0xFF, 0x00 );
    std::string text;
    SDL_Rect dst;

    SDL_Surface *surmessage = nullptr;
    SDL_Texture *texmessage = nullptr;
    TTF_Font *font;

    font = TTF_OpenFont(DEFINED_MESSAGE_FONT,32); //Opens font and sets size
    if (font == nullptr) {
        printf("Font failed to load.");
        return menuError;
    } else {
        if(Global::blnDebugMode) {printf("Message font created\n");}
    }

    SDL_Color clrblack = {0x00, 0x00, 0x00, 0x00}; //Make the color black for font
    SDL_RenderClear(m_window->ren);

    text = "Attacker - the Game";
    surmessage = TTF_RenderText_Solid(font, text.c_str(),clrblack);
    texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(m_window->ren, surmessage);

    if (texmessage == nullptr) {
        printf("Failed to convert message surface to texture.\n");
        return menuError;
    } else {
        if (Global::blnDebugMode) {printf("Surface texture successfully created\n");}
    }


    SDL_QueryTexture(texmessage,NULL,NULL, &dst.w, &dst.h);
    dst.x = (int) ((m_window->width - dst.w)/2);
    dst.y = (int) (m_window->height * 0.1);

    SDL_RenderCopy(m_window->ren, texmessage, NULL, &dst);

    button MainButtons[5];
    MainButtons[0] = {menuQuit,"Quit",{0,0,0,0}};
    MainButtons[1] = {menuOptions,"Options (WIP)",{0,0,0,0}};
    MainButtons[2] = {menuAbout, "About (WIP)",{0,0,0,0}};
    MainButtons[3] = {menuLoad,"Load Game (WIP)",{0,0,0,0}};
    MainButtons[4] = {menuNew,"New Game",{0,0,0,0}};

    for (int i = 0; i < 5; i++) {
        surmessage = TTF_RenderText_Solid(font, MainButtons[i].text.c_str(),clrblack);
        texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(m_window->ren, surmessage);

        if (texmessage == nullptr) {
            printf("Failed to convert message surface to texture.\n");
            return menuError;
        } else {
            if (Global::blnDebugMode) {printf("Surface texture successfully created\n");}
        }

        SDL_QueryTexture(texmessage,NULL,NULL, &dst.w, &dst.h);
        dst.x = (int) ((m_window->width - dst.w)/2);
        dst.y = (i==0) ? (m_window->height - dst.h - 30) :
                          (MainButtons[i-1].cords.y -dst.h - 30);

        SDL_SetRenderDrawColor( m_window->ren, 0x33, 0x66, 0x99, 0xFF );
        SDL_RenderDrawRect( m_window->ren, &dst );
        SDL_RenderCopy(m_window->ren, texmessage, NULL, &dst);
        MainButtons[i].cords = dst;
    }
    SDL_DestroyTexture(texmessage);

    SDL_Event event;
    char buttonpushed = menuError;

    bool done = false;
    do {
        SDL_RenderPresent(m_window->ren);
        SDL_PollEvent(&event);
        if ( event.type == SDL_MOUSEBUTTONUP ){
            LOC mouse_click;
            SDL_GetMouseState(&mouse_click.x, &mouse_click.y);
            for (int i = 0; i < 5; i++ ) {
                if ( clickcheck(mouse_click, MainButtons[i].cords)) {
                    done = true;
                    buttonpushed = MainButtons[i].type;
                } //end check if button
            } //end for menu buttons
        } //end if event
    } while (!done);

    SDL_FreeSurface(surmessage);
    TTF_CloseFont(font);

    return buttonpushed;
}
/*****************************************************************************/
void clsMenu::AboutMenu() {
    return;
}
/*****************************************************************************/
void clsMenu::OptionsMenu() {
    return;
}
/*****************************************************************************/
bool clsMenu::clickcheck(LOC mouse, SDL_Rect box) {
    if (mouse.x < box.x ) {return false;}
    else if (mouse.x > box.x + box.w) {return false;}
    else if (mouse.y < box.y) {return false;}
    else if (mouse.y > box.y + box.h) {return false;}
    else {return true;}
}
/*****************************************************************************/
