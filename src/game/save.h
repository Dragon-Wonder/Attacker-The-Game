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
/////////////////////////////////////////////////
/// @class clsSave save.h "src/game/save.h"
/// @brief The class to hold the stuff related to saving.
///        Currently unimplemented
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __SAVE__HEADER__
