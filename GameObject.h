#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include "OgreMotionState.h"


class Simulator;

class GameObject
{
	protected:
		Ogre::String name;
		Ogre::SceneManager* sceneMgr;
		Simulator* simulator;
		Ogre::SceneNode* rootNode;
		Ogre::Entity* geom;
		btCollisionShape* shape;
		btScalar mass;
		btRigidBody* body;
		btTransform tr;
		btVector3 inertia;
		OgreMotionState* motionState;

	public:
		GameObject(Ogre::SceneManager* scnMgr, Simulator* sim);
		btRigidBody* getBody(){return body;}
		Ogre::SceneNode* getRootNode(){return rootNode;}
		void updateTransform();
		void addToSimulator();
};

#endif