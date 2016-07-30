#ifndef __HEADER__CALCULATIONS__ //Guard the header so if it was already called once it isn't called again.
#define __HEADER__CALCULATIONS__
/*********************************************************************************************************/
#include "global.h"
/*********************************************************************************************************/
/** This namespace is used to hold the different calculations of the program. */
namespace Calculations {
	uint CalculateHealth(stats);
	bool DodgeCheck(stats);
	float ElementMulti(uchar, uchar);
	uint CalculateMana(stats);
	uint goldAmount(uchar,float);
	uint CalculateDamage(stats,stats,uint);
	float MobTypeMulti(uchar);
	uint XPtoLevelUp(uchar);
	uint CalculateXP(uchar, float);
};
/*********************************************************************************************************/
#endif
