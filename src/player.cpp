#include "player.h"
#include <cstdio>
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
    do {
        printf("In this game there are five stats that effect different elements of the game.\n");
        printf("Strength (STR) - Effects how much damage you do when you attack.\n");
        printf("Constitution (CONS) - Effects how much health you have.\n");
        printf("Dexterity (DEX) - Effects if your chance to dodge, and if you attack first.\n");
        printf("Defence (DEF) - Effects how much damage you take.\n");
        printf("Luck (LUK) - The random chance things will go your way, with dodges, crits, and rare modifiers that appear on monsters.\n");

        char chrSkillPointsLeft = 100;

        printf("You have %i points to spend however you desire on these five stats\n",chrSkillPointsLeft);
        printf("however each stat must have at least 1 point.\n");

        do {
            printf("\nEnter your stat for your STRENGTH: ");
            scanf("%i",&tempstats.str);

            chrSkillPointsLeft -= tempstats.str;

            if(tempstats.str < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                chrSkillPointsLeft += tempstats.str;
                loop = true;
            } else if (chrSkillPointsLeft < 4) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
                chrSkillPointsLeft += tempstats.str;
            } else {loop = false;}
        }while (loop);

        do {
            printf("\nEnter your stat for your CONSTITUTION: ");
            scanf("%i",&tempstats.cons);

            chrSkillPointsLeft -= tempstats.cons;

            if(tempstats.cons < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                chrSkillPointsLeft += tempstats.cons;
                loop = true;
            } else if (chrSkillPointsLeft < 3) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
                chrSkillPointsLeft += tempstats.cons;
            } else {loop = false;}
        }while (loop);

        do {
            printf("\nEnter your stat for your DEXTERITY: ");
            scanf("%i",&tempstats.dex);

            chrSkillPointsLeft -= tempstats.dex;

            if(tempstats.dex < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                chrSkillPointsLeft += tempstats.dex;
                loop = true;
            } else if (chrSkillPointsLeft < 2) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
                chrSkillPointsLeft += tempstats.dex;
            } else {loop = false;}
        }while (loop);

        do {
            printf("\nEnter your stat for your DEFENCE: ");
            scanf("%i",&tempstats.def);

            chrSkillPointsLeft -= tempstats.def;

            if(tempstats.def < 1) {
                printf("\nYou did not enter enough points. Please try again.\n");
                chrSkillPointsLeft += tempstats.def;
                loop = true;
            } else if (chrSkillPointsLeft < 1) {
                printf("\nYou used too many points. Please try again.\n");
                loop = true;
                chrSkillPointsLeft += tempstats.def;
            } else {loop = false;}
        }while (loop);

        tempstats.luk = chrSkillPointsLeft;
        do {

            printf("Your current stats are as follows:\n");
            printf("Strength: %i\n",tempstats.str);
            printf("Constitution: %i\n",tempstats.cons);
            printf("Defence: %i\n",tempstats.def);
            printf("Dexterity: %i\n",tempstats.dex);
            printf("Luck: %i\n",tempstats.luk);
            printf("Do you agree with these stats?\n");
            printf("Y or N? > ");

            char Answer;

            sscanf("%c",&Answer);
            switch(Answer) {
                case 'Y' :
                case 'y' :
                    done = true;
                    valid = true;
                    break;
                case 'N' :
                case 'n' :
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
