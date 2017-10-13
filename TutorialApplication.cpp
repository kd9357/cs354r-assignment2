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


// Ball* ball;
// Simulator* sim;

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
    score = 0;
    // Create your scene here :)
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox", 5000, false);

    // Lights setup
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
  
    //Physics setup
    sim = new Simulator();
    
    field = new PlayingField(mSceneMgr, sim, 100, 100, Ogre::String("field"));
    field->addToSimulator();

    // bounds = new PlayingField(mSceneMgr, sim, 10000, 10000, Ogre::String("bounds"));
    // bounds->setMaterial("Examples/BeachStones");
    // bounds->getRootNode()->setPosition(0, -10, 0);
    // bounds->addToSimulator();

    wall = new PlayingField(mSceneMgr, sim, 100, 100, Ogre::String("wall"));
    wall->getRootNode()->pitch(Ogre::Degree(90));
    wall->getRootNode()->setPosition(0, 50, -50);
    wall->addToSimulator();

    ball = new Ball(mSceneMgr, sim, score, Ogre::String("ball"));
    //ball->getRootNode()->setPosition(0, 50, 0);
    ball->addToSimulator();
    ball->reset();
    // ball->setVelocity(0, 0, 50);

    //For now, it's positioning will match that of the camera
    paddle = new Paddle(mSceneMgr, sim, 10, Ogre::String("paddle"));
    paddle->getRootNode()->setPosition(0, 25, 50);
    paddle->addToSimulator();
    paddle->updateTransform();
}
//---------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // mCamera->lookAt(Ogre::Vector3(0, 25, 0));
    mCamera->setNearClipDistance(5);
    mCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode");
    mCamNode->setPosition(Ogre::Vector3(0, 25, 150));
    mCamNode->attachObject(mCamera);
    mMove = 0.15;
    mRotate = 0.05;
}
//---------------------------------------------------------------------------
void TutorialApplication::createViewports(void)
{
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//---------------------------------------------------------------------------
//Keyboard input
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
    static bool mouseDownLastFrame = false;
    static bool mouseUpLastFrame = false;
    //Camera controls
    //For now, also move paddle
    Ogre::Vector3 dirVec = mCamera->getPosition();
    if(mKeyboard->isKeyDown(OIS::KC_R))
        ball->reset();
    if(mKeyboard->isKeyDown(OIS::KC_W))
        dirVec.y += mMove;
    if(mKeyboard->isKeyDown(OIS::KC_S))
        dirVec.y -= mMove;
    if(mKeyboard->isKeyDown(OIS::KC_A))
        dirVec.x -= mMove;
    if(mKeyboard->isKeyDown(OIS::KC_D))
        dirVec.x += mMove;
    mCamNode->translate(dirVec, Ogre::Node::TS_LOCAL);
    paddle->getRootNode()->translate(Ogre::Vector3(dirVec.x, 0, 0), Ogre::Node::TS_WORLD);
    paddle->getRootNode()->translate(Ogre::Vector3(0, 0, -dirVec.y), Ogre::Node::TS_LOCAL);
    paddle->updateTransform();
    return true;
}

//---------------------------------------------------------------------------
//Mouse movement listener (implement later)
bool TutorialApplication::mouseMoved(const OIS::MouseEvent& me) {
    //How do we translate mouse coordinates to object/world coordinates?
    // if(me.state.X.rel > 0)
    //     std::cout << "xrel positive\n";
    return true;
}

bool TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(id == OIS::MB_Left){
        paddle->getRootNode()->pitch(Ogre::Degree(-30));
        paddle->swing();
    }
    return BaseApplication::mousePressed(arg, id);
}

bool TutorialApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(id == OIS::MB_Left){
        paddle->getRootNode()->pitch(Ogre::Degree(30));
    }
    return BaseApplication::mousePressed(arg, id);
}

bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg)
{
    if(arg.key == OIS::KC_Q && !pressed){
        paddle->getRootNode()->yaw(Ogre::Degree(20), Ogre::Node::TS_WORLD);
        pressed = true;
    }
    else if(arg.key == OIS::KC_E && !pressed) {
        paddle->getRootNode()->yaw(Ogre::Degree(-20), Ogre::Node::TS_WORLD);
        pressed = true;
    }
    return BaseApplication::keyPressed(arg);
}

bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg)
{
    bool temp = pressed;
    if(arg.key == OIS::KC_Q){
        paddle->getRootNode()->yaw(Ogre::Degree(-20), Ogre::Node::TS_WORLD);
        pressed = false;
    }
    else if(arg.key == OIS::KC_E) {
        paddle->getRootNode()->yaw(Ogre::Degree(20), Ogre::Node::TS_WORLD);
        pressed = false;
    }

    return BaseApplication::keyPressed(arg);
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

    if(sim)
    {
        sim->stepSimulation(evt.timeSinceLastFrame);
    }

    if(!processUnbufferedInput(evt))
        return false;
    if(ball->getRootNode()->getPosition().y < -10)
        ball->reset();
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
