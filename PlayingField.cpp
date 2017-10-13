// #include <OgreEntity.h>
// #include <OgreSceneManager.h>
#include "PlayingField.h"

PlayingField::PlayingField(Ogre::SceneManager* scnMgr, Simulator* sim, 
													 Ogre::Real width, Ogre::Real height, Ogre::String n) 
												 	: GameObject(scnMgr, sim, n)
{
	// Creating reusable plane entity to create walls of the room
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(n, 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		width, height, 200, 200, true, 1, 50, 50, Ogre::Vector3::UNIT_Z);

	//Floor 
	Ogre::Entity* planeEntity = scnMgr->createEntity(n);
	planeEntity->setCastShadows(false);
	planeEntity->setMaterialName("Examples/Green");

	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	rootNode->attachObject(planeEntity);

	shape = new btBoxShape(btVector3(width / 2.0, 1, height / 2.0));
}

void PlayingField::setMaterial(Ogre::String material)
{
	Ogre::Entity* planeEntity = static_cast<Ogre::Entity*>(rootNode->getAttachedObject(0));
	planeEntity->setMaterialName(material);
}
