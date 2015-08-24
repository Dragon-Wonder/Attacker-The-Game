#include "spells.h"
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
void init_spell(string SpellCast) {
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
	if(Global::blnDebugMode) {cout<<"You cast "<<basespells[n].name;}
	CurrMana -= basespells[n].cost;
	if (CurrMana < 0) {cout<<endl<<"Spell fails to cast, you do not have enough mana."<<endl;}
	else {
		setbattlevalue(statCurrMana,CurrMana);
		switch (basespells[n].type) {
			case typeHeal :
				if (PStatus != effectNone) /*If player has an effect chance to remove it.*/  {
					if (rand() % 101 <= playerLuk) {
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
				if (basespells[n].effect != effectNone && MStatus == effectNone && rand() % 101 <= playerLuk) {
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


