#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "GameObject.h"
#include "Simulator.h"
#include <iostream>

GameObject::GameObject(Ogre::SceneManager* scnMgr, Simulator* sim)
{
	scnMgr = scnMgr;
	simulator = sim;
	//shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	shape = NULL;
	motionState = NULL;
	mass = 0.0f;
	restitution = 1.0;
	friction = 0;
	inertia.setZero();
	tr.setIdentity();
}

void GameObject::updateTransform(){
	Ogre::Vector3 pos = rootNode ->getPosition();
	tr.setOrigin(btVector3(pos.x, pos.y, pos.z));
	Ogre::Quaternion qt = rootNode ->getOrientation();
	tr.setRotation(btQuaternion(qt.x, qt.y, qt.z, qt.w));

	if (motionState) motionState -> updateTransform(tr);
}

void GameObject::addToSimulator(){
	updateTransform();
	motionState = new OgreMotionState(tr, rootNode);
	if(mass != 0.0f) shape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
	body = new btRigidBody(rbInfo);
	body->setRestitution(restitution);
	body->setFriction(friction);
	simulator->addObject(this);
}