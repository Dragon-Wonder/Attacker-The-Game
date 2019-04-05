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
    ///     \f$ 120.75 + \frac {23}{16} * C + 12.9375 * L + 0.094875 * L * C + 0.08625 * L^2 \f$
    ///
    /// L = Level
    /// C = Constitution Stat
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
  HealthTemp = 120.75;
  HealthTemp += (23.0/16.0) * modstat;
  HealthTemp += 12.9375 * level;
  HealthTemp += 0.094875 * level * modstat;
  HealthTemp += 0.08625 * pow(level,2.0);
	return floor(HealthTemp);
}
/*********************************************************************************************************/
uint Calculations::CalculateMana(stats check) {
    /////////////////////////////////////////////////
    /// @brief A simple function for calculating mana
    ///     \f$ 156.21 + 0.25625 * M + 9.58375 * L + 0.0169125 * L * M + 0.046125 * L^2 \f$
    ///
    /// L = Level
    /// M = Modifying Stat \f$ M = \frac {3*DEX + LUK}(4} \f$
    /// The reason that the modifying stat is calculated this way is because there isn't (currently) a stat
    /// that most sense to base Mana off of (such as Wisdom). I might add one later but until then this is
    /// how this will be calculated.
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

	manaTemp = 156.21;
	manaTemp += 0.25625 * modstat;
	manaTemp += 9.58375 * level;
	manaTemp += 0.0169125 * level * modstat;
	manaTemp += 0.046125 * pow(level,2);

  return floor(manaTemp);
}
/*********************************************************************************************************/
uint Calculations::goldAmount(uchar level, float GoldLean) {
  /////////////////////////////////////////////////
  /// @brief A simple function for calculating gold on monsters
  ///     \f$ G * ( 8 + 1.055^L + 1.055^{L^1.085} ) \f$
  ///
  /// L = 5*Level
  /// G = Gold lean
  /// @param level = level
  /// @param GoldLean = ratio of XP vs Gold for a monster. ranges from 0 (all XP) to 1.9 (almost all gold)
  /// @return Gold
  ///
  /////////////////////////////////////////////////
  float lvl = (float)(5.0 * level);

  float tempGold;
  tempGold = 8.0;
  tempGold += pow(1.055,lvl);
  tempGold += pow(1.055,pow(lvl,1.085));
  tempGold *= GoldLean;
  return floor(tempGold);
}
/*********************************************************************************************************/
uint Calculations::CalculateDamage(stats attacker, stats defender, uint base) {
  /////////////////////////////////////////////////
  /// @brief Returns damage done.
  ///
  /// @param attacker = stats of the attacker
  /// @param defender = stats of the defender
  /// @param base = base damage of the attack
  /// @return Damage
  ///
  /////////////////////////////////////////////////

  ///@todo (GamerMan7799#9#) vary damage with health? Less health = less damage

  float temp = 0;
  temp = 2.0 * (attacker.level / 5.0);
  temp += 2.0;
  temp *= (base / defender.def);
  temp *= attacker.str / 8.0;
  return (uint)temp;
}
/*********************************************************************************************************/
float Calculations::MobTypeMulti(uchar type) {
  /////////////////////////////////////////////////
  /// @brief Returns a multi for Gold/XP based on the type of monster
  ///         Monster Types are the following:
  ///| Type   |  Number   |  Multi  |
  ///|--------|-----------|---------|
  ///| Normal | 1         | 1       |
  ///| Elite  | 2         | 2       |
  ///| Boss   | 3         | 4       |
  ///         It uses an equation instead of a simple case return so it it can be expanded if I want to
  ///
  /// @param type = Monster type
  /// @return Multiplier for XP/Gold
  ///
  /////////////////////////////////////////////////

  float temp;
  temp = pow(type,2);
  temp += 15.0 * type;
  temp--;
  temp /= 15.0;

  return temp;
}
/*********************************************************************************************************/
uint Calculations::XPtoLevelUp(uchar level) {
  /////////////////////////////////////////////////
  /// @brief Returns amount of XP required to level up
  ///
  /// @param level = Current Level
  /// @return XP Amount
  ///
  /////////////////////////////////////////////////

  float temp;
  temp = 110.0;
  temp *= pow(1.1,level);

  return (uint)temp;
}
/*********************************************************************************************************/
uint Calculations::CalculateXP(uchar level, float goldLean) {
  /////////////////////////////////////////////////
  /// @brief Returns amount of XP for a monster
  ///
  /// @param level = Current Level
  /// @return XP Amount
  ///
  /////////////////////////////////////////////////

  float temp;
  temp = 8.0;
  temp += pow(1.055,level);
  temp += pow(1.055,pow(level,1.085));
  temp *= 3.0;
  temp *= (2.0 - goldLean);
  return (uint)temp;
}
/*********************************************************************************************************/
