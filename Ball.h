#include <Ogre.h>
#include "PlayingField.h"

class Ball : public GameObject
{
	protected:
		Ogre::Real bRadius;
		PlayingField* grounds;
	public:
		Ball(Ogre::SceneManager* scnMgr, Simulator* sim);
		~Ball();
		Ogre::SceneNode* getNode() { return rootNode; }
		// void setPlayingField(PlayingField* pf) { grounds = pf; }
};