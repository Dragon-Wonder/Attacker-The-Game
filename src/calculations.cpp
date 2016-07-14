/*********************************************************************************************************/
#include "calculations.h"
/*********************************************************************************************************/
#include <math.h>
#include <cstdlib>
/*********************************************************************************************************/
bool Calculations::DodgeCheck(stats check) {
	//The way I worked out this dodge calc is that if the Dex and Luk both equal 150 (which isn't possible under the current levelling up system),
	//then they have a 25% chance to dodge. I also wanted Dex to factor into 75% of the chance and Luk only 25%
	//Can return true, that they dodged or false that they did not.
    float douDodgeChance = ((check.dex/2)+(check.luk/6)/4);
	if(rand() % 101 <= douDodgeChance) {return true;}
	else {return false;}
}
/*********************************************************************************************************/
float Calculations::ElementMulti(uchar AttackingElement, uchar DefendingElement) {
	/*The further away two elements are the more damage that they do to each other.
	  For example a fire attack on an ice monster will be 125% damage, while a fire
	  attack on fire monster will only do 75% damage. 2 spaces away will do normal damage
	  And none elements or physical do normal damage as well.*/

	/*
				Light
		Energy			Wind
	Fire					Ice
		Earth			Water
				Darkness
	*/
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
	//A simple function for calculating health.
	//In its own function so future changes will be changed everywhere.
	float HealthTemp = 0;
	HealthTemp = (0.9722 * pow(check.level, 2) )+( 0.4167 * check.level) + 48.611;
	HealthTemp += 23.979*exp(0.01414 * check.cons);
	return floor(HealthTemp);
}
/*********************************************************************************************************/
