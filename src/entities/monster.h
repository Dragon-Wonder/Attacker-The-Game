#ifndef __HEADER__MONSTER__
#define __HEADER__MONSTER__
/*****************************************************************************/
#include "../global.h"
#include <string>
/*****************************************************************************/
#define DEFINED_NUM_OF_MONSTERS 13
#define DEFINED_NUM_OF_P_MODIFIERS 7
#define DEFINED_NUM_OF_N_MODIFIERS 6
/*****************************************************************************/
enum PosMonsterMods {
  pmmStrong = 0,
  pmmLarge,
  pmmMassive,
  pmmFast,
  pmmLucky,
  pmmSolid,
  pmmArmoured
};

enum NegMonsterMods {
  nmmWeak = 0,
  nmmSmall,
  nmmTiny,
  nmmSlow,
  nmmUnlucky,
  nmmSpineless
};
/*****************************************************************************/
struct stcMonster {
  std::string name;
  stats stats;
  float goldLean;
  uchar element;
};

typedef struct stcMonster Mons;
/*****************************************************************************/
class clsMonster{
  public:
    clsMonster();
    ~clsMonster();

    stats getStats(void);

    void makeMonster(uchar);
    std::string getName();
    void setHealth(healthmana);
    healthmana getHealth(void);
    uchar getElement(void);

  protected:

  private:
    static std::string m_name;      /**< Name of the monster */
    static std::string m_modifier;
    static stats       m_stats;     /**< Monster Stats */
    static healthmana  m_health;    /**< Monster health */
    static healthmana  m_mana;      /**< Monster mana */
    static float       m_goldLean;  /**< Lean of gold vs xp. ranges from 0 to 1.9 */
    static INV         m_inv;       /**< Monster inventory */
    static uchar       m_element;   /**< Monster element type */
    static const Mons monsters[DEFINED_NUM_OF_MONSTERS]; 

    void doLevelUp();
    void ModMonster();
    void PositiveMod();
    void NegativeMod();
};
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class clsMonster monster.h "src/entities/monster.h"
/// @brief Holds all of the information related to the monsters
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __HEADER__MONSTER__
