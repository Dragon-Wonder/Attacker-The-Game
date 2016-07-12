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

        void doLevelup(void);

    protected:

    private:
        static LOC m_loc;

        static stats m_stats;
        static healthmana m_health;
        static healthmana m_mana;

        static INV m_inv;
};
/*****************************************************************************/
#endif // __HEADER__PLAYER__
