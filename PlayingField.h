#include <Ogre.h>
#include <BaseApplication.h>
#include "GameObject.h"

class PlayingField : public GameObject
{
	protected:
		// float height;
		// float length;
		// float width;
	public:
		PlayingField(Ogre::SceneManager* scnMgr, Simulator* sim);
		~PlayingField();
};
