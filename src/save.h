#ifndef __SAVE__HEADER__
#define __SAVE__HEADER__
/*****************************************************************************/
#include "global.h"
/*****************************************************************************/
#define DEFINED_SAVE_FILE_NAME "save.bif"
/*****************************************************************************/
class clsSave {
    public:
        clsSave();
        ~clsSave();

        void doSave(void);
        void doLoad(void);

    protected:

    private:
        bool exists(void);
};
/*****************************************************************************/
#endif // __SAVE__HEADER__
