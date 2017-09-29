#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr)
{
	Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh");
	ball->setMaterialName("Examples/SphereMappedRustySteel");
	ball->setCastShadows(true);
	rootNode = scnMgr->createSceneNode("Ball");
	rootNode->attachObject(ball);
	rootNode->scale(0.1f, 0.1f, 0.1f);
	bRadius = 10.0f;
	bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f);
	bDirection.normalise();
	bSpeed = 10.0f;
}

void Ball::move(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 bPosition = rootNode->getPosition();
	if(bPosition.y < 0.0f + bRadius && bDirection.y < 0.0f)
		bDirection.y = -bDirection.y;
	if(bPosition.y > grounds->getHeight() - bRadius && bDirection.y > 0.0f)
		bDirection.y = -bDirection.y;
	if(bPosition.z < -grounds->getLength() / 2.0f + bRadius && bDirection.z < 0.0f)
		bDirection.z = -bDirection.z;
	if(bPosition.z > grounds->getLength() / 2.0f - bRadius && bDirection.z > 0.0f)
		bDirection.z = -bDirection.z;
	if(bPosition.x < -grounds->getWidth() / 2.0f + bRadius && bDirection.x < 0.0f)
		bDirection.x = -bDirection.x;
	if(bPosition.x > grounds->getLength() / 2.0f - bRadius && bDirection.x > 0.0f)
		bDirection.x = -bDirection.x;
	rootNode->translate(bSpeed * evt.timeSinceLastFrame * bDirection);
}
