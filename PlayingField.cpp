#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "PlayingField.h"

PlayingField::PlayingField(Ogre::SceneManager* scnMgr, Simulator* sim) : GameObject(scnMgr, sim)
{
	// Creating reusable plane entity to create walls of the room
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("plane", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		50, 50, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	//Floor 
	Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
	planeEntity->setCastShadows(false);
	planeEntity->setMaterialName("Examples/Rockwall");

	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	rootNode->attachObject(planeEntity);

	shape = new btBoxShape(btVector3(100, 1, 100));
}
