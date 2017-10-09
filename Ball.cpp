#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Simulator* sim) : GameObject(scnMgr, sim)
{
	Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh");
	ball->setMaterialName("Examples/SphereMappedRustySteel");
	ball->setCastShadows(true);
	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	rootNode->attachObject(ball);
	rootNode->scale(0.05f, 0.05f, 0.05f);
	bRadius = 5.0f;
	shape = new btSphereShape(bRadius);
	mass = 10;
}

void Ball::reset()
{
	rootNode->setPosition(0, 50, 0);
	setVelocity(0, 0, 50);
	updateTransform();
}