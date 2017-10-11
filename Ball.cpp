#include "Ball.h"
#include "Simulator.h"

Ball::Ball(Ogre::SceneManager* scnMgr, Simulator* sim, Ogre::String n) 
	: GameObject(scnMgr, sim, n)
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

//Specific game object update routine
void Ball::update(float elapsedTime) {
	lastTime += elapsedTime;
	simulator->getDynamicsWorld()->contactTest(body, *callback);
	if (context->hit && (context->velNorm > 1.0 || context->velNorm < -1.0) 
		&& (lastTime > 0.5 || (context->lastBody != context->body && lastTime > 0.1))) {
		//Handle the hit
		std::cout << "ball hit" << std::endl;
		lastTime = 0.0f;
	}
	context->hit = false;
}

void Ball::reset()
{
	rootNode->setPosition(0, 50, 0);
	setVelocity(0, 0, 50);
	updateTransform();
}