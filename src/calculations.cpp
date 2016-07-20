/*********************************************************************************************************/
#include "calculations.h"
/*********************************************************************************************************/
#include <math.h>
#include <cstdlib>
/*********************************************************************************************************/
/////////////////////////////////////////////////
/// @file calculations.cpp
/// @brief  This file holds the many formulas used for different aspects of the game.
/////////////////////////////////////////////////
/*****************************************************************************/
bool Calculations::DodgeCheck(stats check) {
    /////////////////////////////////////////////////
    /// @brief Function checks if an attack was dodged. The way this was worked
    ///        out is that if Dex and Luk both equal 150 (which shouldn't be possible
    ///        with the current system), but then they have a 25% chance to dodge.
    ///        I also wanted Dex to factor 75% into the chance while LUK is only
    ///        25%.
    ///
    /// @param check = stcStats of monster/player to be checked.
    /// @return True/False of if dodge occurred.
    ///
    /////////////////////////////////////////////////
    float douDodgeChance = ((check.dex/2)+(check.luk/6)/4);
	if(rand() % 101 <= douDodgeChance) {return true;}
	else {return false;}
}
/*********************************************************************************************************/
float Calculations::ElementMulti(uchar AttackingElement, uchar DefendingElement) {
    /////////////////////////////////////////////////
    /// @brief The further away two elements are the more damage that they do to each other.
	///        For example a fire attack on an ice monster will be 125% damage, while a fire
	///        attack on fire monster will only do 75% damage. 2 spaces away will do normal damage
	///        And none elements or physical do normal damage as well.
	///	    			Light
	/// 	    Energy			Wind
	///     Fire					Ice
	///     	Earth			Water
	///     			Darkness
    ///
    /// @param AttackingElement = Element of the Attack
    /// @param DefendingElement = Element of the Defender
    /// @return Multiplier of the Attack Damage, ranges from 0.75 to 1.25
    ///
    /////////////////////////////////////////////////
	if (AttackingElement == elementNone || DefendingElement == elementNone) {return 1.0;}
	if (AttackingElement == elementPhysical || DefendingElement == elementPhysical) {return 1.0;}
	switch (abs(AttackingElement - DefendingElement)) {
		case 0 :
			return 0.75;
		case 1 :
			return 0.875;
		case 2 :
			return 1;
		case 3 :
			return 1.125;
		case 4 :
			return 1.25;
		default :
			return 1;
	};
	return 1;
}
/*********************************************************************************************************/
uint Calculations::CalculateHealth(stats check) {
    /////////////////////////////////////////////////
    /// @brief A simple function for calculating health
    ///
    /// @param check = stats of Monster/Player to be calculated
    /// @return Health
    ///
    /////////////////////////////////////////////////
	float HealthTemp = 0;
	float level;
	float modstat;
	level = (float)check.level;
	modstat = (float)check.cons;

	HealthTemp = 5.25 + 0.5625 * level + 0.00375 * pow(level,2);
	HealthTemp += (1+0.066*level) * (modstat/16.0);
	HealthTemp *= 23.0;
	return floor(HealthTemp);
}
/*********************************************************************************************************/
uint Calculations::CalculateMana(stats check) {
    /////////////////////////////////////////////////
    /// @brief A simple function for calculating mana
    ///
    /// @param check = stats of Monster/Player to be calculated
    /// @return Mana
    ///
    /////////////////////////////////////////////////
 	float manaTemp = 0;
	float level;
	float modstat;
	level = (float)check.level;
	modstat = (3.0*(float)check.dex+(float)check.luk)/4.0;

	manaTemp = 32.0;
	manaTemp += 6.1+2.3375*level+0.01125*pow(level,2);
	manaTemp += (1+0.066*level) * (modstat/16.0);
	manaTemp *= 4.1;

    return floor(manaTemp);
}
/*********************************************************************************************************/
uint Calculations::goldAmount(uchar level, float GoldLean) {
    /////////////////////////////////////////////////
    /// @brief A simple function for calculating gold on monsters
    ///
    /// @param level = level
    /// @param GoldLean = ratio of XP vs Gold for a monster. ranges from 0 (all XP) to 1.9 (almost all gold)
    /// @return Gold
    ///
    /////////////////////////////////////////////////

    float tempGold;
    tempGold = pow(1.055,level) + 8.0 + pow(1.055,pow(level,1.085));
    tempGold *= GoldLean;
    return floor(tempGold);
}
/*********************************************************************************************************/
