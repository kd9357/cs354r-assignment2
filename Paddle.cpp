#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr, Simulator* sim, 
               Ogre::Real width, Ogre::Real height) 
              : GameObject(scnMgr, sim)
{
   // Creating an upright plane for our paddle
  // Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
  // Ogre::MeshManager::getSingleton().createPlane("paddle", 
  //   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
  //   width, height, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  // Ogre::Entity* paddleEntity = scnMgr->createEntity("paddle");
  Ogre::Entity* paddleEntity = scnMgr->createEntity("paddle","paddle.mesh");
  paddleEntity->setCastShadows(true);
  //paddleEntity->setMaterialName("Examples/RustySteel");

  rootNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  //rootNode->showBoundingBox(true);
  rootNode->attachObject(paddleEntity);
  rootNode->scale(15,15,15);
  rootNode->pitch(Ogre::Degree(90));
  Ogre::Vector3 v = paddleEntity->getWorldBoundingBox(true).getSize();
  shape = new btBoxShape(btVector3(v.x * 0.8, v.z * 0.8, v.y * 0.8));
}