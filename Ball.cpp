#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Simulator* sim) : GameObject(scnMgr, sim)
{
	Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh");
	ball->setMaterialName("Examples/SphereMappedRustySteel");
	ball->setCastShadows(true);
	//rootNode = scnMgr->createSceneNode();
	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	rootNode->attachObject(ball);
	rootNode->scale(0.1f, 0.1f, 0.1f);
	bRadius = 10.0f;

	shape = new btSphereShape(bRadius);
	mass = 10;
}