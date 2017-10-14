#include <Ogre.h>
#include "GameObject.h"
// #include <BaseApplication.h>
// #include <OgreEntity.h>
// #include <OgreSceneManager.h>

class Ball : public GameObject
{
	protected:
		Ogre::Real bRadius;
		float lastTime;
    int* score;
	public:
		Ball(Ogre::SceneManager* scnMgr, Simulator* sim, int* score, Ogre::String n);
		~Ball();
		void update(float elapsedTime);
    	void reset();
};