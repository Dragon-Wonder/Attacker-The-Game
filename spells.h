#ifndef _SPELLS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SPELLS_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold functions related to spells and magic, a possible future addition.
Current Revision: 1.0.2
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date		Revision	Changed By		Changes
------  	---------   ------------	---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVED FROM BETA TO GAMMA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================		
2015/03/16	1.0			Patrick Rye		-Move from beta revisions to gamma revisions.
										-Added more stuff to spells.
										-Changed some int to smaller variables because they don't need to be that big.	
=============================================================================================================================================================
2015/03/16	1.0.1		Patrick Rye		-Added more spells.
=============================================================================================================================================================
2015/03/17	1.0.2		Patrick Rye 	-More damage for elements that are farther apart.
=============================================================================================================================================================
*/
/*********************************************************************************************************/
bool blSpellsDebugMode = false;
/*********************************************************************************************************/
void SetSpellDebugMode(bool bldebugmode) {blSpellsDebugMode = bldebugmode;}
/*********************************************************************************************************/
struct spell {
	string name; //Name of spell
	unsigned char damage; //Base damage / heal.
	unsigned char cost; //Base cost.
	unsigned char type; //Type, damage, healing or effect
	unsigned char element; //Element of spell, currently does nothing.
	unsigned char effect; //Effect that can be caused by spell
};
/*********************************************************************************************************/
const spell basespells[8] = {{"spell fail",0,0,100,elementNone,effectNone},
							{"fireball",15,5,typeDamage,elementFire,effectBurned},
							{"heal",50,20,typeHeal,elementNone,effectNone},
							{"blind",0,5,typeEffect,elementNone,effectBlinded},
							{"shock",25,0,typeDamage,elementEnergy,effectNone},
							{"blizzard",22,0,typeDamage,elementIce,effectFrozen},
							{"water",10,10,typeEffect,elementWater,effectWet},
							{"confusion",0,10,typeEffect,elementLight,effectConfused}};
/*********************************************************************************************************/

void init_spell(string SpellCast)
{
	unsigned char n;
	for (unsigned char i = 0; i < 8; i++) {if (SpellCast == basespells[i].name) {n = i;}}
	if (n < 0 || n > 6) {n = 0;}
	unsigned char playerLuk = getbattlevalue(statLuk);
	unsigned char monsterdef = getmonstervalue(statDef);
	unsigned char playerStr = getbattlevalue(statStr);
	int CurrPHealth = getbattlevalue(statCurrHealth);
	int MaxPHealth = getbattlevalue(statMaxHealth);
	unsigned char PStatus = getbattlevalue(statStatus);
	unsigned char MStatus = getmonstervalue(statStatus);
	int MHealth = getmonstervalue(statCurrHealth);
	unsigned char MElement = getmonstervalue(statElement);
	unsigned int SpellDamage;
	float ElementalMulti = ElementMulti(basespells[n].element,MElement);
	unsigned char SpellStrength;
	
	if(blSpellsDebugMode) {cout<<"You cast "<<basespells[n].name;}
	
	switch (basespells[n].type)
	{
		case typeHeal :
			if (PStatus != effectNone) //If player has an effect chance to remove it.
			{
				if (rand() % 101 <= playerLuk) 
				{
					setbattlevalue(statStatus,effectNone);
					cout<<endl<<EndOfEffectString("player",PStatus)<<endl;
				} 
			}
			if (CurrPHealth + basespells[n].damage >= MaxPHealth) {setbattlevalue(statCurrHealth,MaxPHealth);}
			else {setbattlevalue(statCurrHealth,CurrPHealth + basespells[n].damage);}
			cout<<endl<<"You heal yourself for "<<(int)basespells[n].damage<<". ";
			break;
		case typeEffect :
			if (MStatus != effectNone) {cout<<endl<<"Spell fails. "; break;}
			setmonstervalue(statStatus,basespells[n].effect);
			cout<<endl<<StartOfEffectString("monster",basespells[n].effect)<<endl;
			break;
		case typeDamage :
			SpellStrength = floor(basespells[n].damage + playerStr/2);
			if (basespells[n].effect != effectNone && MStatus == effectNone && rand() % 101 <= playerLuk) 
			{
				setmonstervalue(statStatus,basespells[n].effect); 
				setmonstervalue(statStatusCounter,0);
				cout<<endl<<StartOfEffectString("monster",basespells[n].effect);
			}
			SpellDamage = CalculateDamage(6,SpellStrength,monsterdef);
			SpellDamage = floor(SpellDamage * ElementalMulti);
			if (MStatus == effectWet && basespells[n].element == elementEnergy) {SpellDamage = floor(SpellDamage * 1.5);}
			cout<<endl<<"You cast "<<basespells[n].name<<" and hit the monster for "<<SpellDamage<<".";
			MHealth -= SpellDamage;
			setmonstervalue(statCurrHealth,MHealth);
			break;
		default : 
			cout<<endl<<"Spell failed to cast.";
			break;
	}
}


#endif
