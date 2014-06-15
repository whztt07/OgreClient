#pragma once
#include "Ogre.h"
#include "OIS/OIS.h"
#include "PlayerController.h"
#include "CameraController.h"
#include "MyGuiManager.h"
using namespace Ogre;
class CInputSystem : public OIS::KeyListener,
	public OIS::MouseListener
{
public:
	CInputSystem(void);
	virtual ~CInputSystem(void);

public:
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);	
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

public:
	BOOL CreateInputSystem(Ogre::RenderWindow *pRenderWindow);

	BOOL Capture();

	BOOL SetCameraAndPlayer(CCameraController *pCameraController, CPlayerController *pPlayerController);

public:
	OIS::InputManager *m_pInputManager;
	OIS::Keyboard     *m_pKeyboard;
	OIS::Mouse		  *m_pMouse;
	CCameraController *m_pCameraController;
	CPlayerController *m_pPlayerController;
	CMyGuiManager	  *m_pGuiSystem;
};


