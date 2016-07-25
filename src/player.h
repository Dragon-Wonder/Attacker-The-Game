#ifndef __HEADER__PLAYER__
#define __HEADER__PLAYER__
/*****************************************************************************/
#include "global.h"
/*****************************************************************************/
class clsPlayer {
    public:
        clsPlayer();
        ~clsPlayer();

        void setLocation(LOC);
        LOC getLocation(void);

        void doHeal(void);
        void showStatus(void);
        void initialize(void);
        stats getStats(void);
        void setStats(stats);
        healthmana getHealth(void);
        healthmana getMana(void);

        void setHealth(healthmana);
        void setMana(healthmana);

        void doLevelup(void);

    protected:

    private:
        static LOC m_loc;           /**< Location of the player */

        static stats m_stats;       /**< Player's stats */
        static healthmana m_health; /**< Player's health */
        static healthmana m_mana;   /**< Player's mana */

        static INV m_inv;           /**< Player's inventory */
};
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class Player player.h "src/player.h"
/// @brief Holds all of the information related to the monsters
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __HEADER__PLAYER__
