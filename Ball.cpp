#include "Ball.h"
#include "Simulator.h"
#include <iostream>

Ball::Ball(Ogre::SceneManager* scnMgr, Simulator* sim, int& s, Ogre::String n) 
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
	score = s;
}

//Specific game object update routine
void Ball::update(float elapsedTime) {
	lastTime += elapsedTime;
	simulator->getDynamicsWorld()->contactTest(body, *callback);
	if (context->hit && (context->velNorm > 1.0 || context->velNorm < -1.0) 
		&& (lastTime > 0.1 || (context->lastBody != context->body && lastTime > 0.05))) {
		//Handle the hit
		Ogre::String objName = callback->ctxt.theObject->getName();
		if(objName =="wall")
		{
			++score;
			std::cout << "score: " << score <<"\n";
			Mix_PlayChannel(-1, sounds->score, 0);
		}
		else if(objName == "bounds")
		{
			//lose sound
			reset();
		}
		else 
			Mix_PlayChannel(-1, sounds->bounce, 0);
		lastTime = 0.0f;
	}
	context->hit = false;
}

void Ball::reset()
{
	//Update score
	score = 0;
	rootNode->setPosition(0, 50, 0);
	Ogre::Real x = Ogre::Math::RangeRandom(-50, 50);
	Ogre::Real y = Ogre::Math::RangeRandom(-10, 10);
	setVelocity(x, y, 50);
	updateTransform();
}