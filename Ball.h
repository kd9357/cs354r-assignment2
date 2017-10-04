#include <Ogre.h>
#include "PlayingField.h"

class Ball : public GameObject
{
	protected:
		Ogre::SceneNode* rootNode;
		Ogre::Real bRadius;
		Ogre::Vector3 bDirection;
		Ogre::Real bSpeed;
		PlayingField* grounds;
	public:
		Ball(Ogre::SceneManager* scnMgr, Simulator* sim);
		~Ball();
		void move(const Ogre::FrameEvent& evt);
		Ogre::SceneNode* getNode() { return rootNode; }
		void setPlayingField(PlayingField* pf) { grounds = pf; }
};