/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
#include <iostream>
#include "TutorialApplication.h"
#include "Ball.h"
#include "Simulator.h"
#include "GameObject.h"

Ball* ball;
Simulator* sim;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox", 5000, false);

    Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setDiffuseColour(1.0, 1.0, 1.0);
    pointLight->setSpecularColour(1.0, 1.0, 1.0);
    pointLight->setPosition(0, 200, 0);

    Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDirection(-1, -1, -1);
    spotLight->setPosition(50, 50, 50);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
  
    // Creating reusable plane entity to create walls of the room
    // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    // Ogre::MeshManager::getSingleton().createPlane("plane", 
    //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
    //     50, 50, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    // Ogre::Entity* planeEntity = mSceneMgr->createEntity("plane");
    // planeEntity->setCastShadows(false);
    // planeEntity->setMaterialName("Examples/Rockwall");
    // Ogre::SceneNode* floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    // floorNode->attachObject(planeEntity);

    sim = new Simulator();
    PlayingField* field = new PlayingField(mSceneMgr, sim);
    ball = new Ball(mSceneMgr, sim);
    field->addChild(ball->getNode());
    // std::cout << "before simulator" << std::endl;
    // field->addToSimulator();
    // ball->addToSimulator();
    // std::cout << "after simulator" << std::endl;

    std::cout << "end of createScene" << std::endl;
}
//---------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0, 25, 80));
    mCamera->lookAt(Ogre::Vector3(0, 25, 0));
    mCamera->setNearClipDistance(5);
}
//---------------------------------------------------------------------------
void TutorialApplication::createViewports(void)
{
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//---------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
	   return false;
    if(mShutDown)
	   return false;

    mKeyboard->capture();
    mMouse->capture();

    std::cout << "before step sim" << std::endl;
    /*
    if(sim)
    {
        std::cout << "sim not null" << std::endl;
        sim->stepSimulation(evt.timeSinceLastFrame);
        std::deque<GameObject*> objs = sim->getGameObjects();
        for (GameObject* obj : objs){
            if(obj == NULL)
                std::cout << "obj is null" << std::endl;
            btTransform trans;
            btRigidBody* body = obj->getBody();
            body->getMotionState()->getWorldTransform(trans);
            //btQuaternion orientation = trans.getRotation();
            Ogre::SceneNode* sceneNode = obj->getRootNode();
            sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
            sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
        }
    }*/
    std::cout << "after step sim" << std::endl;

    return true;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
