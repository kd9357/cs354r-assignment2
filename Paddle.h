#include <Ogre.h>
#include "GameObject.h"


class Paddle : public GameObject
{
  protected:
     float lastTime;
  public:
    Paddle(Ogre::SceneManager* scnMgr, Simulator* sim, Ogre::Real width, Ogre::Real height, Ogre::String n);
    ~Paddle();
    void update(float elapsedTime);
};
