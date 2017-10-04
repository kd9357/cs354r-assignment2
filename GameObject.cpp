#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "GameObject.h"
#include "Simulator.h"

GameObject::GameObject(Ogre::SceneManager* scnMgr, Simulator* sim)
{
	scnMgr = scnMgr;
	simulator = sim;
	rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	shape = NULL;
	mass = 0.0f;
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
	simulator->addObject(this);
}