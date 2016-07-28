/*****************************************************************************/
#include "monster.h"
#include "calculations.h"
#include "player.h"
/*****************************************************************************/
#include <cstdio>
#include <cstdlib>
/*****************************************************************************/
std::string clsMonster::m_name      = "Generic Monster";
std::string clsMonster::m_modifier  = "";
stats       clsMonster::m_stats     = {1,6,6,6,6,6};
healthmana  clsMonster::m_health    = {100,100};
healthmana  clsMonster::m_mana      = {0,0};
float       clsMonster::m_goldLean  = 0.0;
INV         clsMonster::m_inv       = {25,1};
/*****************************************************************************/
/*A quick note on the base stats, a stat cannot be lower than 6, as a modifier might reduce the value by 5 points.
  The base stat point should also add up to be 100. */
const Mons monsters[DEFINED_NUM_OF_MONSTERS] = {
    {"Zombie",          {1,25,25,10,25,15}, 1.2},
    {"Skeleton",        {1,35,18,6,25,6},   1.5},
    {"Witch",           {1,15,15,20,20,30}, 1.5},
    {"Imp",             {1,15,15,15,40,15}, 1.4},
    {"Golem",           {1,20,34,34,6,6},   1.0},
    {"Murloc",          {1,20,20,20,20,20}, 0.8},
    {"Demon",           {1,25,25,20,20,10}, 0.9},
    {"Angel",           {1,15,15,20,20,30}, 0.9},
    {"Harpy",           {1,10,10,10,35,35}, 0.7},
    {"Elf",             {1,20,20,20,20,20}, 1.6},
    {"Ghost",           {1,20,20,20,20,20}, 0.5},
    {"Undead Mutant",   {1,34,34,20,6,6},   0.8},
    {"Thunder Spider",  {1,20,8,15,33,24},  1.0}
};

/*****************************************************************************/
clsMonster::clsMonster() {
    //ctor
}
/*****************************************************************************/
clsMonster::~clsMonster() {
    //dtor
}
/*****************************************************************************/
stats clsMonster::getStats() {
    /////////////////////////////////////////////////
    /// @brief Returns monster stats
    ///
    /// @return Stats of the monster
    ///
    /////////////////////////////////////////////////
    return m_stats;
}
/*****************************************************************************/
void clsMonster::makeMonster(uchar level) {
    uchar num;
    num = rand() % DEFINED_NUM_OF_MONSTERS;
    m_name = monsters[num].name;
    m_stats = monsters[num].stats;
    m_goldLean = monsters[num].goldLean;
    m_stats.level = level;

    m_inv.gold = Calculations::goldAmount(level, m_goldLean);
    if(rand() % 101 <= DEFINED_KEY_SPAWN_CHANCE) {m_inv.keys = 1;}
    else {m_inv.keys = 0;}

    if(level != 1) {doLevelUp();}
    ModMonster();
    m_health.max = Calculations::CalculateHealth(m_stats);
    m_mana.max = Calculations::CalculateMana(m_stats);
    m_health.curr = m_health.max;
    m_mana.curr = m_mana.curr;
}
/*****************************************************************************/
void clsMonster::doLevelUp() {
    char upgradeChance[5] = {0,0,0,0,0};
    int statPoints = (m_stats.level - 1) * 18;
    uchar randStat = 0;

    upgradeChance[0] = m_stats.str;
    upgradeChance[1] = m_stats.cons + upgradeChance[0];
    upgradeChance[2] = m_stats.def + upgradeChance[1];
    upgradeChance[3] = m_stats.dex + upgradeChance[2];
    upgradeChance[4] = m_stats.luk + upgradeChance[3];

    for (int i = 0; i < statPoints; i++) {
        randStat = rand() % 101;
        if (randStat < upgradeChance[0] ) {m_stats.str++;}
        else if (randStat < upgradeChance[1] ){m_stats.cons++;}
        else if (randStat < upgradeChance[2] ) {m_stats.def++;}
        else if (randStat < upgradeChance[3] ) {m_stats.dex++;}
        else {m_stats.luk++;}
    }
}
/*****************************************************************************/
void clsMonster::ModMonster() {
	//Adds a random modifier onto a monster it can boost or reduce the stats of the monster.
	//Varies a bit with a player's LUK

	uchar rand1, rand2, num;
	rand1 = rand() % 20; //0-19
	rand2 = rand() % 20; //0-19
	num = rand() % 101 + 1; //1-100

	clsPlayer player;
    stats pstats;
    pstats = player.getStats();
    /// @todo (gamerMan7799#7#) make modifiers increase based on level
    if (num < 60) {m_modifier = "";}
    else {
        if(m_stats.luk + rand1 > pstats.luk + rand2) {
        //Monster has better chance of spawning with a positive effect
            if (num < 90) { PositiveMod(); }
            else { NegativeMod(); }
        } else if (m_stats.luk + rand1 < pstats.luk + rand2) {
        //Monster has better chance of spawning with negative effects
            if(num<90) { NegativeMod(); }
            else {PositiveMod();}
        }
    }
}
/*****************************************************************************/
void clsMonster::PositiveMod() {
    uchar mod;
    m_modifier = "";
    mod = rand() % DEFINED_NUM_OF_P_MODIFIERS;
    switch(mod) {
    case pmmStrong:
        m_modifier = "Strong";
        m_stats.str +=5;
        break;
    case pmmArmoured:
        m_modifier = "Heavily-Armored";
        m_stats.cons += 5;
        m_stats.def +=5;
        m_stats.luk -=2;
        break;
    case pmmFast:
        m_modifier = "Fast";
        m_stats.dex +=5;
        break;
    case pmmLarge:
        m_modifier = "Large";
        m_stats.cons +=5;
        break;
    case pmmLucky:
        m_modifier = "Lucky";
        m_stats.luk += 5;
        break;
    case pmmMassive:
        m_modifier = "Massive";
        m_stats.cons +=5;
        m_stats.str +=5;
        m_stats.dex -=5;
        break;
    case pmmSolid:
        m_modifier = "Solid";
        m_stats.cons +=5;
        break;
    default:
        m_modifier = "";
        break;
    }
}
/*****************************************************************************/
void clsMonster::NegativeMod() {
    uchar mod;
    mod = rand() % DEFINED_NUM_OF_N_MODIFIERS;
    m_modifier = "";
    switch(mod) {
    case nmmSlow:
        m_modifier = "Slow";
        m_stats.dex -= 5;
        break;
    case nmmSmall:
        m_modifier = "Small";
        m_stats.cons -=5;
        break;
    case nmmSpineless:
        m_modifier = "Spineless";
        m_stats.str -=4;
        m_stats.cons -=4;
        m_stats.dex +=2;
        break;
    case nmmTiny:
        m_modifier = "Tiny";
        m_stats.cons -=5;
        break;
    case nmmUnlucky:
        m_modifier = "Unlucky";
        m_stats.luk -= 5;
        break;
    case nmmWeak:
        m_modifier = "Weak";
        m_stats.str -=5;
        break;
    default:
        m_modifier = "";
        break;
    }
}
/*****************************************************************************/
std::string clsMonster::getName() {
    std::string temp;
    if(m_modifier == "" ) {return m_name;}
    else {
        temp = m_modifier;
        temp += " ";
        temp += m_name;
        return temp;
    }
}
/*****************************************************************************/
