#include "Paddle.h"
#include "Simulator.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr, Simulator* sim, Ogre::Real scale, Ogre::String n) 
              : GameObject(scnMgr, sim, n)
{

  // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  //   Ogre::MeshManager::getSingleton().createPlane(n, 
  //   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
  //   10, 10, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
  // Ogre::Entity* paddleEntity = scnMgr->createEntity(n);
  // paddleEntity->setMaterialName("Examples/RustySteel");
  Ogre::Entity* paddleEntity = scnMgr->createEntity("paddle","paddle.mesh");
  paddleEntity->setCastShadows(true);
  rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  //rootNode->showBoundingBox(true);
  rootNode->attachObject(paddleEntity);
  rootNode->scale(scale, scale, scale);
  rootNode->pitch(Ogre::Degree(90));
  Ogre::Vector3 v = paddleEntity->getWorldBoundingBox(true).getSize();
  shape = new btBoxShape(btVector3(v.x * 0.5, v.z * 0.5, v.y * 0.5));
}

//Specific game object update routine
void Paddle::update(float elapsedTime) {
  lastTime += elapsedTime;
  simulator->getDynamicsWorld()->contactTest(body, *callback);
  if (context->hit && (lastTime > 0.5 || (context->lastBody != context->body && lastTime > 0.1))) {
    //Handle the hit
    // std::cout << "Paddle hit" << std::endl;
    lastTime = 0.0f;
  }
  context->hit = false;
}

void Paddle::swing(void) {
  Mix_PlayChannel(-1, sounds->whoosh, 0);
  //Possibly enable hitbox
}