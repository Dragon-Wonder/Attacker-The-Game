#ifndef __HEADER__MONSTER__
#define __HEADER__MONSTER__
/*****************************************************************************/
#include "global.h"
/*****************************************************************************/
class clsMonster{
    public:
        clsMonster();
        ~clsMonster();

        stats getStats(void);

    protected:

    private:
        stats m_stats;          /**< Monster Stats */
        healthmana m_health;    /**< Monster health */
        healthmana m_mana;      /**< Monster mana */

        INV inv;                /**< Monster inventory */

};
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class Monster monster.h "src/monster.h"
/// @brief Holds all of the information related to the monsters
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __HEADER__MONSTER__
