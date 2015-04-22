#ifndef _SPELLS_H_INCLUDED__ //Guard the header so if it was already called once it isn't called again.
#define _SPELLS_H_INCLUDED__
/*
Made By: Patrick J. Rye
Purpose: A header to hold functions related to spells and magic, a possible future addition.
Current Revision: 1.1.1
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
2015/03/17	1.0.3		Patrick Rye		-Added more spells.
=============================================================================================================================================================
2015/03/18	1.1			Patrick Rye		-Implemented mana system.
=============================================================================================================================================================
2015/04/17	1.1.1		Patrick Rye		-Now gets monster name for status effect outputs.
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
const spell basespells[11] = {{"spell fail",0,0,100,elementNone,effectNone},
							{"fireball",15,15,typeDamage,elementFire,effectBurned},
							{"heal",25,30,typeHeal,elementNone,effectNone},
							{"blind",0,20,typeEffect,elementNone,effectBlinded},
							{"shock",25,20,typeDamage,elementEnergy,effectNone},
							{"blizzard",22,20,typeDamage,elementIce,effectFrozen},
							{"water",10,15,typeEffect,elementWater,effectWet},
							{"confusion",0,15,typeEffect,elementWind,effectConfused},
							{"burn",0,15,typeEffect,elementFire,effectBurned},
							{"freeze",0,15,typeEffect,elementIce,effectFrozen},
							{"poison",0,15,typeEffect,elementDarkness,effectPoison}};
/*********************************************************************************************************/

void init_spell(string SpellCast)
{
	unsigned char n;
	for (unsigned char i = 0; i < 11; i++) {if (SpellCast == basespells[i].name) {n = i;}}
	if (n < 0 || n >= 11) {n = 0;}
	unsigned char playerLuk = getbattlevalue(statLuk);
	unsigned char monsterdef = getmonstervalue(statDef);
	unsigned char playerStr = getbattlevalue(statStr);
	int CurrMana = getbattlevalue(statCurrMana);
	int CurrPHealth = getbattlevalue(statCurrHealth);
	int MaxPHealth = getbattlevalue(statMaxHealth);
	unsigned char PStatus = getbattlevalue(statStatus);
	unsigned char MStatus = getmonstervalue(statStatus);
	int MHealth = getmonstervalue(statCurrHealth);
	unsigned char MElement = getmonstervalue(statElement);
	string strMonsterName = getMonsterName();
	unsigned int SpellDamage;
	float ElementalMulti = ElementMulti(basespells[n].element,MElement);
	unsigned char SpellStrength;
	if(blSpellsDebugMode) {cout<<"You cast "<<basespells[n].name;}
	CurrMana -= basespells[n].cost;
	if (CurrMana < 0) {cout<<endl<<"Spell fails to cast, you do not have enough mana."<<endl;}
	else
	{
		setbattlevalue(statCurrMana,CurrMana);
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
				cout<<endl<<StartOfEffectString(strMonsterName,basespells[n].effect)<<endl;
				break;
			case typeDamage :
				SpellStrength = floor(basespells[n].damage + playerStr/2);
				if (basespells[n].effect != effectNone && MStatus == effectNone && rand() % 101 <= playerLuk) 
				{
					setmonstervalue(statStatus,basespells[n].effect); 
					setmonstervalue(statStatusCounter,0);
					cout<<endl<<StartOfEffectString(strMonsterName,basespells[n].effect);
				}
				SpellDamage = CalculateDamage(6,SpellStrength,monsterdef);
				SpellDamage = floor(SpellDamage * ElementalMulti);
				if (MStatus == effectWet && basespells[n].element == elementEnergy) {SpellDamage = floor(SpellDamage * 1.5);}
				cout<<endl<<"You cast "<<basespells[n].name<<" and hit the " <<strMonsterName<< " for "<<SpellDamage<<".";
				MHealth -= SpellDamage;
				setmonstervalue(statCurrHealth,MHealth);
				break;
			default : 
				cout<<endl<<"Spell failed to cast.";
				break;
		//End of switch
		}
	//End of else
	}
//End of init_spell.
}


#endif
