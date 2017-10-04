#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "PlayingField.h"

PlayingField::PlayingField(Ogre::SceneManager* scnMgr, Simulator* sim) : GameObject(scnMgr, sim)
{
	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// Creating reusable plane entity to create walls of the room
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("plane", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		50, 50, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* planeEntity = scnMgr->createEntity("plane");
	planeEntity->setCastShadows(false);
	planeEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* floorNode = rootNode->createChildSceneNode();
	floorNode->attachObject(planeEntity);

	// Left Wall
	Ogre::Entity* leftEntity = scnMgr->createEntity("plane");
	leftEntity->setCastShadows(false);
	leftEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* leftNode = rootNode->createChildSceneNode(Ogre::Vector3(-25, 25, 0));
	leftNode->attachObject(leftEntity);
	leftNode->roll(Ogre::Degree(-90));

	// Right Wall
	Ogre::Entity* rightEntity = scnMgr->createEntity("plane");
	rightEntity->setCastShadows(false);
	rightEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* rightNode = rootNode->createChildSceneNode(Ogre::Vector3(25, 25, 0));
	rightNode->attachObject(rightEntity);
	rightNode->roll(Ogre::Degree(90));

	// Front Wall
	Ogre::Entity* frontEntity = scnMgr->createEntity("plane");
	rightEntity->setCastShadows(false);
	frontEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* frontNode = rootNode->createChildSceneNode(Ogre::Vector3(0, 25, 25));
	frontNode->attachObject(frontEntity);
	frontNode->pitch(Ogre::Degree(-90));

	// Back Wall
	Ogre::Entity* backEntity = scnMgr->createEntity("plane");
	backEntity->setCastShadows(false);
	backEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* backNode = rootNode->createChildSceneNode(Ogre::Vector3(0, 25, -25));
	backNode->attachObject(backEntity);
	backNode->pitch(Ogre::Degree(90));

	// Cieling
	Ogre::Entity* cielEntity = scnMgr->createEntity("plane");
	cielEntity->setCastShadows(false);
	cielEntity->setMaterialName("Examples/Rockwall");
	Ogre::SceneNode* cielNode = rootNode->createChildSceneNode(Ogre::Vector3(0, 50, 0));
	cielNode->attachObject(cielEntity);
	cielNode->pitch(Ogre::Degree(180));

	height = 50.0f;
	length = 50.0f;
	width = 50.0f;
}
