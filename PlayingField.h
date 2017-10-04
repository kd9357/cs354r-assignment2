#include <Ogre.h>
#include <BaseApplication.h>
#include "GameObject.h"

class PlayingField : public GameObject
{
	protected:
		Ogre::SceneNode* rootNode;
		float height;
		float length;
		float width;
	public:
		PlayingField(Ogre::SceneManager* scnMgr, Simulator* sim);
		~PlayingField();
		void addChild(Ogre::SceneNode* node) { rootNode->addChild(node);
node->setPosition(Ogre::Vector3(0, 20, 0)); }
		float getHeight(void) { return height; }
		float getLength(void) { return length; }
		float getWidth(void) { return width; }
};
