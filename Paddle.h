#include <Ogre.h>
#include "GameObject.h"


class Paddle : public GameObject
{
  protected:
     float lastTime;
  public:
    Paddle(Ogre::SceneManager* scnMgr, Simulator* sim, Ogre::Real scale, Ogre::String n);
    ~Paddle();
    void update(float elapsedTime);
    void swing(void);
};
