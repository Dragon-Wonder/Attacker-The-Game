#include "menu.h"
/*****************************************************************************/
//TTF_Font* clsMenu::m_font;
/*****************************************************************************/
clsMenu::clsMenu() {
    //ctor
    clsScreen screen;
    m_window = screen.getWinAtt();
}
/*****************************************************************************/
clsMenu::~clsMenu() {
    //dtor

    //TTF_CloseFont(m_font);
}
/*****************************************************************************/
char clsMenu::MainMenu() {
  /////////////////////////////////////////////////
  /// @brief The function that holds the Main menu.
  ///
  /// @return Char for what button was pressed
  ///
  /////////////////////////////////////////////////
  SDL_SetRenderDrawColor( m_window->ren, 0xFF, 0xFF, 0xFF, 0xFF );
  std::string text = "Attacker - the Game";
  SDL_Rect dst;
  SDL_Surface* surmessage = nullptr;
  SDL_Texture* texmessage = nullptr;
  SDL_Color clrblack = {0xFF,0xFF,0xFF,0xFF};


  surmessage = TTF_RenderText_Solid(m_window->font, text.c_str(),clrblack);
  texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(m_window->ren, surmessage);

  if (texmessage == nullptr) {
    printf("Failed to convert message surface to texture.\n");
    return menuError;
  } else {
    if (Global::blnDebugMode) { printf("Surface texture successfully created\n"); }
  }


  SDL_QueryTexture(texmessage,NULL,NULL, &dst.w, &dst.h);
  dst.x = (int) ((m_window->width - dst.w)/2);
  dst.y = (int) (m_window->height * 0.1);

  SDL_RenderCopy(m_window->ren, texmessage, NULL, &dst);

  button MainButtons[5];
  MainButtons[0] = {menuQuit,"Quit",{0,0,0,0}};
  MainButtons[1] = {menuOptions,"Options (WIP)",{0,0,0,0}};
  MainButtons[2] = {menuAbout, "About (WIP)",{0,0,0,0}};
  MainButtons[3] = {menuLoad,"Load Game",{0,0,0,0}};
  MainButtons[4] = {menuNew,"New Game",{0,0,0,0}};

  for (int i = 0; i < 5; i++) { //for each button
    surmessage = TTF_RenderText_Solid(m_window->font, MainButtons[i].text.c_str(),clrblack);
    texmessage = (surmessage == nullptr) ? nullptr : SDL_CreateTextureFromSurface(m_window->ren, surmessage);

    if (texmessage == nullptr) {
      printf("Failed to convert message surface to texture.\n");
      return menuError;
    } else {
      if (Global::blnDebugMode) { printf("Surface texture successfully created\n"); }
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
  SDL_FreeSurface(surmessage);

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

  return buttonpushed;
}
/*****************************************************************************/
void clsMenu::AboutMenu() {
  /////////////////////////////////////////////////
  /// @brief Will show the about menu
  /////////////////////////////////////////////////
  /// @todo (GamerMan7799#8#) Add about menu
  return;
}
/*****************************************************************************/
void clsMenu::OptionsMenu() {
  /////////////////////////////////////////////////
  /// @brief Will show the options Menu.
  ///        Possibly unneeded. Only things I can think of are:
  ///        * Screen Size (already can with config, and would require restart)
  ///        * Controls (no idea how to do this, so likely won't be able to)
  ///        * Volume
  ///        * Quality (consider how low quality this already is, if you are having issues you need a new computer)
  /////////////////////////////////////////////////
  /// @todo (GamerMan7799#9#) Add options menu (possibly unneeded)
  return;
}
/*****************************************************************************/
bool clsMenu::clickcheck(LOC mouse, SDL_Rect box) {
  /////////////////////////////////////////////////
  /// @brief Checks if mouse click was on a button
  ///
  /// @param mouse = X/Y Coordinates of the mouse click
  /// @param box = SDL_Rect coordinates for the button we are checking
  /// @return True/False if button was clicked on
  ///
  /////////////////////////////////////////////////
  if (mouse.x < box.x ) {return false;}
  else if (mouse.x > box.x + box.w) {return false;}
  else if (mouse.y < box.y) {return false;}
  else if (mouse.y > box.y + box.h) {return false;}
  else {return true;}
}
/*****************************************************************************/
char clsMenu::GameMenu() {
    /////////////////////////////////////////////////
    /// @brief Shows In game menu, which will hold things like:
    ///        * Save Game
    ///        * Load game
    ///        * Quit
    ///        * Options
    ///
    /// @return What was clicked on
    ///
    /////////////////////////////////////////////////
    /// @todo (GamerMan7799#2#) Add in-game menu
    return menuOptions;
}
/*****************************************************************************/
char clsMenu::promptUser(char promptType, std::string message) {
  /////////////////////////////////////////////////
  /// @brief Prompts the user for some information.
  ///
  /// @param propmttype = What prompt to the user
  /// @param message = The message that appears above the prompt.
  /// @return What key is pressed by the user.
  ///
  /////////////////////////////////////////////////

  /// @todo (GamerMan7799#9#) Centralize color for this class

  if(m_window->font == nullptr) {return returnError;}
  SDL_RenderClear(m_window->ren);
  SDL_SetRenderDrawColor( m_window->ren, 0xFF, 0xFF, 0xFF, 0x00 );
  SDL_Color clrblack = {0x00, 0x00, 0x00, 0x00}; //Make the color black for font

  SDL_Surface* surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
  SDL_Texture* texmessage = nullptr;
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

  if (texmessage == nullptr) {
    printf("Message not converted to texture.\n");
    return returnError;
  }

  SDL_Rect dst;

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
  //figure out x and y so that message is in the middle
  dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
  dst.y = (uint) ((m_window->height / 2) - (dst.h / 2));
  SDL_RenderCopy(m_window->ren,texmessage, NULL, &dst);


  //add second message based on prompt type
  switch(promptType) {
  case promptYesNo :
    message = "Please hit Y for yes, or N for no.";
    break;
  case prompOkay :
    message = "Please hit any button to close.";
    break;
  default:
    message = " ";
    break;
  }

  surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(), clrblack);
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

   if (texmessage == nullptr) {
    printf("Error making message.\n");
    return returnError;
   }

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
  //figure out x and y so that message is in the middle, but below the first message
  dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
  dst.y = (uint) ((m_window->height / 2) + (dst.h / 2));

  SDL_RenderCopy(m_window->ren,texmessage,NULL,&dst);
  SDL_RenderPresent(m_window->ren);

  bool blnStopLoop = false;
  char keypress;
  SDL_Event event;



  //start looping while waiting for response.
  do {
    if(SDL_PollEvent( &event )) {
      if (event.type == SDL_QUIT) {
        //player wants to quit, leave loop
        keypress = returnNo;
        blnStopLoop = true;
      } else if (event.type == SDL_KEYDOWN) {
        switch (promptType) {
        case promptYesNo:
          switch (event.key.keysym.sym) {
          case SDLK_y:
            keypress = returnYes;
            blnStopLoop = true;
            break;
          case SDLK_n:
            keypress = returnNo;
            blnStopLoop = true;
            break;
          default:
            printf("Invalid key choice.\n");
            break;
          } //end switch YES/NO
          break;
        case prompOkay:
        default:
          keypress = returnMaybe;
          blnStopLoop = true;
          break;
        } //end switch prompt type
      } //end if event type
    } //end if poll event
  } while (!blnStopLoop);


  SDL_DestroyTexture(texmessage);
  SDL_FreeSurface(surmessage);

  return keypress;
}
/*****************************************************************************/
stats clsMenu::doLevelUp(stats currStats) {
  /////////////////////////////////////////////////
  /// @brief Have player level up with SDL menu
  ///
  /// @param currStats = Current stats
  /// @return New stats
  ///
  /////////////////////////////////////////////////

  if(m_window->font == nullptr) {
    // No font loaded, kill screen, close game.
    return {0,0,0,0,0,0};
  }

  SDL_RenderClear(m_window->ren);
  SDL_SetRenderDrawColor( m_window->ren, 0xFF, 0xFF, 0xFF, 0x00 );
  SDL_Color clrblack = {0x00, 0x00, 0x00, 0x00}; //Make the color black for font
  stats newStats = currStats;
  char upgradePoints = 20;
  bool finish_level_up = false;
  bool refresh_screen = true;
  levelupLine LevelUpBars[5];

  SDL_Rect dst;
  SDL_Surface* surmessage = nullptr;
  SDL_Texture* texmessage = nullptr;
  std::string message;


  do {
    if (refresh_screen) {
      dst.y = 60;
      message = "LEVEL UP!";
      surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
      texmessage = (surmessage == nullptr) ? nullptr :
                   SDL_CreateTextureFromSurface(m_window->ren,surmessage);
      if (texmessage == nullptr) {
        printf("Message not converted to texture.\n");
        return {0,0,0,0,0,0};
      }
      SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
      //figure out x so that message is in the middle
      dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
      SDL_RenderCopy(m_window->ren,texmessage, NULL, &dst);

      dst.y = 120;
      message = "Points left : ";
      message += std::to_string(upgradePoints);
      surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
      texmessage = (surmessage == nullptr) ? nullptr :
                   SDL_CreateTextureFromSurface(m_window->ren,surmessage);
      if (texmessage == nullptr) {
        printf("Message not converted to texture.\n");
        return {0,0,0,0,0,0};
      }
      SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
      //figure out x so that message is in the middle
      dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
      SDL_RenderCopy(m_window->ren,texmessage, NULL, &dst);

      // draw each level up bar.
      for (int i = 0; i < 6; ++i) {
        drawLevelUpBar(LevelUpBars[i]);
      }
    } // end if refresh_screen


  } while (!finish_level_up);











}
/*****************************************************************************/
void clsMenu::drawLevelUpBar(levelupLine StatLine) {
  /////////////////////////////////////////////////
  /// @brief Finish this later
  ///
  /// @param currStats = Current stats
  /// @return New stats
  ///
  /////////////////////////////////////////////////

  SDL_SetRenderDrawColor(m_window->ren,0x00, 0x00, 0x00, 0x00);
  SDL_Color clrblack = {0x00, 0x00, 0x00, 0x00}; //Make the color black for font
  SDL_Rect dst;
  std::string message = "+";

  dst = StatLine.plus;
  SDL_Surface* surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
  SDL_Texture* texmessage = nullptr;
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

  if (texmessage == nullptr) { return; }

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
  SDL_RenderDrawRect(m_window->ren,&dst);
  SDL_RenderCopy(m_window->ren,texmessage,NULL,&dst);

  message = "-";
  dst = StatLine.minus;
  surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
  texmessage = nullptr;
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

  if (texmessage == nullptr) { return; }

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
  SDL_RenderDrawRect(m_window->ren,&dst);
  SDL_RenderCopy(m_window->ren,texmessage,NULL,&dst);

  switch (StatLine.type) {
  case statStr:
    message = "Strength";
    break;
  case statCons:
    message = "Constitution";
    break;
  case statDef:
    message = "Defense";
    break;
  case statDex:
    message = "Dexterity";
    break;
  case statLuk:
    message = "Luck";
    break;
  default:
    message = "ERROR!";
    break;
  }

  surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                                 clrblack);
  texmessage = nullptr;
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

  if (texmessage == nullptr) { return; }

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);

  dst.y = (uint) (dst.y - dst.h);
  dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
  SDL_RenderCopy(m_window->ren,texmessage,NULL,&dst);

  message = std::to_string(StatLine.value);
  dst = StatLine.text;
  surmessage = TTF_RenderText_Solid(m_window->font, message.c_str(),
                                               clrblack);
  texmessage = nullptr;
  texmessage = (surmessage == nullptr) ? nullptr :
               SDL_CreateTextureFromSurface(m_window->ren,surmessage);

  if (texmessage == nullptr) { return; }

  SDL_QueryTexture(texmessage, NULL, NULL, &dst.w, &dst.h);
  dst.x = (uint) ((m_window->width / 2) - (dst.w / 2));
  SDL_RenderCopy(m_window->ren,texmessage,NULL,&dst);

  SDL_DestroyTexture(texmessage);
  SDL_FreeSurface(surmessage);
}
/*****************************************************************************/
