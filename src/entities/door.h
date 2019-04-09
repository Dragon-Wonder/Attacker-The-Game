#ifndef __DOOR__HEADER__
#define __DOOR__HEADER__
/*****************************************************************************/
#include "../global.h"
/*****************************************************************************/
class clsDoor {
  public:
    clsDoor();
    ~clsDoor();

    void activate(void);
    bool getLocked(void);
    void setLocked(bool);
    LOC getLocation(void);
    void setLocation(LOC);
  protected:

  private:
    bool m_locked;
    LOC m_location;
};
/*****************************************************************************/
/////////////////////////////////////////////////
/// @class clsDoor door.h "src/entities/door.h"
/// @brief The class to hold the stuff related to opening a locked door.
///        Currently unimplemented.
/////////////////////////////////////////////////
/*****************************************************************************/
#endif // __DOOR__HEADER__
