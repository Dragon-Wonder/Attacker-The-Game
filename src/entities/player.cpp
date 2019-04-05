#include "player.h"
#include "../game/calculations.h"
#include <cstdio>
#include <ctype.h>
#include <string>
/*****************************************************************************/
LOC clsPlayer::m_loc;
stats clsPlayer::m_stats;
healthmana clsPlayer::m_health;
healthmana clsPlayer::m_mana;
INV clsPlayer::m_inv;
/*****************************************************************************/
clsPlayer::clsPlayer() {
    //ctor
}
/*****************************************************************************/
clsPlayer::~clsPlayer() {
    //dtor
}
/*****************************************************************************/
void clsPlayer::setLocation(LOC newloc) {
    /////////////////////////////////////////////////
    /// @brief Sets player location
    ///
    /// @param newloc = new location
    ///
    /////////////////////////////////////////////////
    m_loc = newloc;
    return;
}
/*****************************************************************************/
LOC clsPlayer::getLocation() {
    /////////////////////////////////////////////////
    /// @brief Gets player location
    ///
    /// @return Location
    ///
    /////////////////////////////////////////////////
    return m_loc;
}
/*****************************************************************************/
void clsPlayer::initialize() {
    /////////////////////////////////////////////////
    /// @brief Has user initialization their player stats
    /////////////////////////////////////////////////
    /// @todo (GamerMan7799#7#) Make initialize SDL supported
    stats tempstats;
    tempstats.level = 1;



    /*
    bool loop = false;
    bool done = false;
    bool valid = false;
    char Answer;
    do {
        printf("In this game there are five stats that effect different elements of the game.\n");
        printf("Strength (STR) - Effects how much damage you do when you attack.\n");
        printf("Constitution (CON) - Effects how much health you have.\n");
        printf("Dexterity (DEX) - Effects if your chance to dodge, and if you attack first.\n");
        printf("Defense (DEF) - Effects how much damage you take.\n");
        printf("Luck (LUK) - The random chance things will go your way, with dodges, crits, and rare modifiers that appear on monsters.\n");

        int chrSkillPointsLeft = 100;
        int tempvalue;

        printf("You have %i points to spend however you desire on these five stats\n",chrSkillPointsLeft);
        printf("however each stat must have at least 1 point.\n");

        do {
            printf("You have %i points to spend left.\n",chrSkillPointsLeft);
            printf("\nEnter your stat for your STRENGTH: ");
            scanf("%i",&tempvalue);
            if (Global::blnDebugMode) {printf("\nFound: %i\n",tempvalue);}

            if(tempvalue < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                loop = true;
            } else if (tempvalue > chrSkillPointsLeft - 4) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
            } else {
                loop = false;
                tempstats.str = tempvalue;
                chrSkillPointsLeft -= tempvalue;
            } //end if value valid
        }while (loop);

        do {
            printf("You have %i points to spend left.\n",chrSkillPointsLeft);
            printf("\nEnter your stat for your CONSTITUTION: ");
            scanf("%i",&tempvalue);
            if (Global::blnDebugMode) {printf("\nFound: %i\n",tempvalue);}

            if(tempvalue < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                loop = true;
            } else if (tempvalue > chrSkillPointsLeft - 3) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
            } else {
                loop = false;
                tempstats.con = tempvalue;
                chrSkillPointsLeft -= tempvalue;
            } //end if value valid
        }while (loop);

        do {
            printf("You have %i points to spend left.\n",chrSkillPointsLeft);
            printf("\nEnter your stat for your DEXTERITY: ");
            scanf("%i",&tempvalue);
            if (Global::blnDebugMode) {printf("\nFound: %i\n",tempvalue);}

            if(tempvalue < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                loop = true;
            } else if (tempvalue > chrSkillPointsLeft - 2) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
            } else {
                loop = false;
                tempstats.dex = tempvalue;
                chrSkillPointsLeft -= tempvalue;
            } //end if value valid
        }while (loop);

        do {
            printf("You have %i points to spend left.\n",chrSkillPointsLeft);
            printf("\nEnter your stat for your DEFENSE: ");
            scanf("%i",&tempvalue);
            if (Global::blnDebugMode) {printf("\nFound: %i\n",tempvalue);}

            if(tempvalue < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                loop = true;
            } else if (tempvalue > chrSkillPointsLeft - 1) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
            } else {
                loop = false;
                tempstats.def = tempvalue;
                chrSkillPointsLeft -= tempvalue;
            } //end if value valid
        }while (loop);

        tempstats.luk = chrSkillPointsLeft;
        do {

            printf("Your current stats are as follows:\n");
            printf("Strength: %i\n",tempstats.str);
            printf("Constitution: %i\n",tempstats.con);
            printf("Defense: %i\n",tempstats.def);
            printf("Dexterity: %i\n",tempstats.dex);
            printf("Luck: %i\n",tempstats.luk);
            printf("Do you agree with these stats?\n");
            printf("Y or N? > ");

            scanf("\n%c",&Answer);
            //getchar();
            Answer = toupper(Answer);
            switch(Answer) {
                case 'Y' :
                    done = true;
                    valid = true;
                    break;
                case 'N' :
                    done = false;
                    valid = true;
                    break;
                default :
                    printf("Invalid choice, try again.\n");
                    done = false;
                    valid = false;
                    break;
            } //end switch
        } while (!valid);
    } while(!done);
  m_stats = tempstats;
  */

  m_health.max = m_health.curr = Calculations::CalculateHealth(tempstats);
  m_mana.max = m_mana.curr = Calculations::CalculateMana(tempstats);


} //end player initialize
/*****************************************************************************/
void clsPlayer::doHeal() {
    /////////////////////////////////////////////////
    /// @brief Heals the Player, 1/10 of Max health
    /////////////////////////////////////////////////
    int temp;
    temp = (int) m_health.max / 10.0;

    m_health.curr = (temp + m_health.curr > m_health.max) ? m_health.max :
                    temp + m_health.curr;

    printf("You healed for %i.\n",temp);
    return;
}
/*****************************************************************************/
void clsPlayer::doLevelup() {
  /////////////////////////////////////////////////
  /// @brief Holds all the stuff related to leveling up the player
  /////////////////////////////////////////////////
  m_stats.level++;
  uchar PlayerStatPoints = 20;
  int Amount;
  char selection[5];
  bool done = false;
  bool valid = false;
  std::string sel;

  printf("LEVEL UP!\n You have 20 points you can spend to upgrade.\n");

  do {
    printf("You are now level: %i\n",m_stats.level);
    printf("You have %i points left to spend.\n", PlayerStatPoints);
    printf("STR: %i\nCON: %i\nDEF: %i\nDEX: %i\nLUK: %i\n",m_stats.str,m_stats.con,
           m_stats.def,m_stats.dex,m_stats.luk);
    printf("NONE to not use any points.\n");
    printf("Enter the stat you wish to improve.\n");
    printf("> ");
    scanf("%5s",&selection);
    //convert the selection to uppercase
    for(int i = 0; i < 5; i++) {selection[i] = toupper(selection[i]);} //end for
    sel = "";
    for(int i = 0; i < 3; i++) {sel += selection[i];}


    if(!(sel == "STR" || sel == "CON" ||
         sel == "DEF" || sel == "DEX" ||
         sel == "LUK" || sel == "NON")) {

        printf("\n\nInvalid choice, please try again.\n");
        done = false;
    } else {
      valid = false;
      if(selection != "NON") {
          do {
            printf("You have chosen to upgrade %s please enter the points you wish to add\n",&selection);
            printf("You have %i left to spend\n",PlayerStatPoints);
            printf("If you chose the wrong stat just enter 0 to not give it any points.\n\n");
            printf("> ");
            scanf("%i",&Amount);

            if (Amount < 0 || Amount > PlayerStatPoints) {
              printf("\nYou have entered an invalid number, please try again.\n");
              valid = false;
            } else {
              PlayerStatPoints -= Amount;
              if (selection == "STR" ) {m_stats.str += Amount;}
              else if (selection == "CON" ){m_stats.con += Amount;}
              else if (selection == "DEF" ){m_stats.def += Amount;}
              else if (selection == "DEX" ){m_stats.dex += Amount;}
              else if (selection == "LUK" ){m_stats.luk += Amount;}
              else {if(Global::blnDebugMode){printf("ERROR!\n");}}
              valid = true;
            }
          } while (!valid);
        } else {
          PlayerStatPoints = 0;
        } //end if not none
    } //end if valid selection
    if (PlayerStatPoints == 0) {done = true;}
  } while (!done);

  return;
}
/*****************************************************************************/
void clsPlayer::showStatus() {
  /////////////////////////////////////////////////
  /// @brief Show Status Menu. Will show:
  ///        * Level
  ///        * Status Effects
  ///        * Health/mana
  /////////////////////////////////////////////////
  //add later
  /// @todo (GamerMan7799#2#) Add status menu
  return;
}
/*****************************************************************************/
stats clsPlayer::getStats() {
  /////////////////////////////////////////////////
  /// @brief gets player stats
  /// @return stats of the player
  /////////////////////////////////////////////////
  return m_stats;
}
/*****************************************************************************/
void clsPlayer::setStats(stats newstats) {
  /////////////////////////////////////////////////
  /// @brief Sets player stats
  /// @param newstats
  /////////////////////////////////////////////////
  m_stats = newstats;
  //Recalculate Mana & health Max's
  m_health.max = Calculations::CalculateHealth(m_stats);
  m_mana.max = Calculations::CalculateMana(m_stats);
  return;
}
/*****************************************************************************/
healthmana clsPlayer::getHealth() {
  /////////////////////////////////////////////////
  /// @brief gets player health
  /// @return Player health
  /////////////////////////////////////////////////
  return m_health;
}
/*****************************************************************************/
healthmana clsPlayer::getMana() {
  /////////////////////////////////////////////////
  /// @brief gets player health
  /// @return Player health
  /////////////////////////////////////////////////
  return m_mana;
}
/*****************************************************************************/
void clsPlayer::setHealth(healthmana newhealth) {
  /////////////////////////////////////////////////
  /// @brief sets player health
  /// @param newhealth
  /////////////////////////////////////////////////
  m_health = newhealth;
  return;
}
/*****************************************************************************/
void clsPlayer::setMana(healthmana newmana) {
  /////////////////////////////////////////////////
  /// @brief sets player mana
  /// @param newmana
  /////////////////////////////////////////////////
  m_mana = newmana;
  return;
}
/*****************************************************************************/
void clsPlayer::regenMana() {
  /////////////////////////////////////////////////
  /// @brief Regen some mana
  /////////////////////////////////////////////////
  int amount = (int)(m_mana.max / 15.0);

  if(m_mana.curr + amount > m_mana.max) {m_mana.curr = m_mana.max;}
  else {m_mana.curr += amount;}
}
/*****************************************************************************/
