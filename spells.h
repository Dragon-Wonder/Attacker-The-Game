#ifndef _SPELLS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SPELLS_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold functions related to spells and magic, a possible future addition.
Current Revision: 1.0
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
2015/03/09	1.0			Patrick Rye		-Original
=============================================================================================================================================================
*/
/*********************************************************************************************************/
bool blSpellsDebugMode = false;
/*********************************************************************************************************/
void SetSpellDebugMode(bool bldebugmode) {blSpellsDebugMode = bldebugmode;}
/*********************************************************************************************************/
struct spell {
	string name; //Name of spell
	int damage; //Base damage / heal.
	int cost; //Base cost.
	int type; //Type, damage, healing or effect
	int element; //Element of spell, currently does nothing.
	int effect; //Effect that can be caused by spell
};
/*********************************************************************************************************/
const spell basespells[7] = {{"Spell Fail",0,0,typeHeal,elementNone,effectNone},
							{"Fireball",15,5,typeDamage,elementFire,effectBurned},
							{"Heal",50,20,typeHeal,elementNone,effectNone},
							{"Blind",0,5,typeEffect,elementNone,effectBlinded},
							{"Shock",50,0,typeDamage,elementEnergy,effectNone},
							{"Blizzard",50,0,typeDamage,elementIce,effectFrozen},
							{"Water spout",10,10,typeDamage,elementWater,effectWet}};
/*********************************************************************************************************/

void init_spell(string SpellCast)
{
	int n;
	for (int i = 0; i < 7; i++)
	{
		if (SpellCast == basespells[i].name) {n = i;}
		else {n = 0;} //A catch if it cannot find spell name, then sets it to 0, which is fail spell. 
	}
	
	int playerLuk = getbattlevalue(statLuk);
	int CurrPHealth = getbattlevalue(statCurrHealth);
	int MaxPHealth = getbattlevalue(statMaxHealth);
	int PStatus = getbattlevalue(statStatus);
	int MStatus = getmonstervalue(statStatus);
	
	
	
	switch (basespells[n].type)
	{
		case typeHeal :
			if (PStatus != effectNone){ //If player has an effect chance to remove it.
				if (rand() % 101 <= playerLuk) {setbattlevalue(statStatus,effectNone);} }
			
			if (CurrPHealth + basespells[n].damage >= MaxPHealth) {setbattlevalue(statMaxHealth,MaxPHealth);}
			else {setbattlevalue(statCurrHealth,CurrPHealth + basespells[n].damage);}
			cout<<endl<<"You heal yourself for "<<basespells[n].damage<<". ";
			break;
		case typeEffect :
			if (MStatus != effectNone) {cout<<"Spell fails. "; break;}
			setmonstervalue(statStatus,basespells[n].effect);
			break;
		case typeDamage :
			if (basespells[n].effect != effectNone) {if (rand() % 101 <= playerLuk) {setmonstervalue(statStatus,basespells[n].effect);}}
			
			break;
		default : 
			cout<<endl<<"Spell failed to cast.";
			break;
	}
	
	
	
	
}


#endif
