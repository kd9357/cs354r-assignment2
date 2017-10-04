#include <iostream>
#include "Simulator.h"

Simulator::Simulator()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
												overlappingPairCache,
												solver,
												collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0, -0.098, 0.0));
}

void Simulator::addObject(GameObject* o)
{
	objList.push_back(o);
	dynamicsWorld->addRigidBody(o->getBody());
}

btAlignedObjectArray<btCollisionShape*> Simulator::getCollisionShapes()
{
	return this->collisionShapes;
}

btDiscreteDynamicsWorld* Simulator::getDynamicsWorld()
{
	return this->dynamicsWorld;
}

void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep)
{
	getDynamicsWorld()->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
	//int count = objList.size();
	// for(int i = 0; i < count; ++i)
	// {
	// 	btCollisionObject* obj = getDynamicsWorld()->getCollisionObjectArray()[i];
	// 	btRigidBody* body = btRigidBody::upcast(obj);

	// 	if(body && body->getMotionState())
	// 	{
	// 		btTransform trans;
	// 		body->getMotionState()->getWorldTransform(trans);

	// 		void* userPointer = body->getUserPointer();
	// 		if(userPointer)
	// 		{
	// 			btQuaternion orientation = trans.getRotation();
	// 			Ogre::SceneNode* sceneNode = static_cast<Ogre::SceneNode*>(userPointer);
	// 			sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
	// 			sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
	// 		}
	// 	}
	// }
}