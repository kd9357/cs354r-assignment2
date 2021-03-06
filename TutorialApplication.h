/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "Simulator.h"
#include "PlayingField.h"
#include "Ball.h"
#include "Paddle.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <SDL.h>
#include <SDL_mixer.h>


//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
    // OIS::MouseListener
    virtual bool mouseMoved(const OIS::MouseEvent& me);
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    // Ogre::KeyListener
    virtual bool processUnbufferedInput(const Ogre::FrameEvent& fe);
    virtual bool keyPressed( const OIS::KeyEvent &arg);
    virtual bool keyReleased( const OIS::KeyEvent &arg);
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    CEGUI::OgreRenderer* mRenderer;
    CEGUI::Window *scoreLabel = NULL;

    //Simulator and Game objects
    Simulator * sim;
    PlayingField * field;
    PlayingField * bounds;
    PlayingField * wall;
    Ball * ball;
    Paddle * paddle;
    //Camera Parameters
    Ogre::SceneNode * mCamNode;
    Ogre::Vector3 mDirection;
    Ogre::Real mMove;
    Ogre::Real mRotate;

    bool pressed;
    int score;

    // Music
    Mix_Music* bgMusic;
    int volume;
    int musVol;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
