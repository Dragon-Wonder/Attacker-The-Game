#include "player.h"
#include <cstdio>
#include <ctype.h>
/*****************************************************************************/
LOC clsPlayer::m_loc;
stats clsPlayer::m_stats;
healthmana clsPlayer::m_health;
healthmana clsPlayer::m_mana;
INV clsPlayer::m_inv;
/*****************************************************************************/
clsPlayer::clsPlayer()
{
    //ctor
}
/*****************************************************************************/
clsPlayer::~clsPlayer()
{
    //dtor
}
/*****************************************************************************/
void clsPlayer::setLocation(LOC newloc) {
    m_loc = newloc;
    return;
}
/*****************************************************************************/
LOC clsPlayer::getLocation() {return m_loc;}
/*****************************************************************************/
void clsPlayer::initialize() {
    stats tempstats;
    bool loop = false;
    bool done = false;
    bool valid = false;
    char Answer;
    do {
        printf("In this game there are five stats that effect different elements of the game.\n");
        printf("Strength (STR) - Effects how much damage you do when you attack.\n");
        printf("Constitution (CONS) - Effects how much health you have.\n");
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
                tempstats.cons = tempvalue;
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
            printf("Constitution: %i\n",tempstats.cons);
            printf("Defense: %i\n",tempstats.def);
            printf("Dexterity: %i\n",tempstats.dex);
            printf("Luck: %i\n",tempstats.luk);
            printf("Do you agree with these stats?\n");
            printf("Y or N? > ");

            scanf("%c",&Answer);
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
} //end player initazile
/*****************************************************************************/
void clsPlayer::doHeal() {
    //add later
    return;
}
/*****************************************************************************/
void clsPlayer::doLevelup() {
    //add later
    return;
}
/*****************************************************************************/
void clsPlayer::showStatus() {
    //add later
    return;
}
/*****************************************************************************/
