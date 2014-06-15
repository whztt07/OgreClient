#pragma once
#include "Ogre.h"
#include "OIS/OIS.h"

using namespace Ogre;
class CCameraController;
class CPlayerController
{
public:
	CPlayerController(void);
	virtual ~CPlayerController(void);

public:
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);	
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

public:
	BOOL CreatePlayer(Ogre::SceneManager *pSceneManager);

	BOOL CreateSinBa(Ogre::SceneManager *pSceneManager);

	Ogre::Vector3 GetPosition();

	void SetPosition(Vector3 &vtNewPos);

	void SetDirection(Vector3 &vtDir);

	BOOL PlayerAnimation(UINT32 dwIndex);

	BOOL UpdateAnimation();

	BOOL SetCameraControl(CCameraController *pCameraControl);

	BOOL UpdatePlayerControl();

public:
	UINT32  m_dwAnimateIndex;
	BOOL	m_bUp;
	BOOL	m_bDown;
	BOOL    m_bRight;
	BOOL    m_bLeft;
	BOOL    m_bChangePos;

public:
	CCameraController *m_pCameraController;
	Ogre::Entity *m_pEntity;
	Ogre::SceneNode *m_pSceneNode;
	Ogre::SceneManager *m_pSceneManager;
	Entity* mSword1;
	Entity* mSword2;
	AnimationState* mAnims[13];
};


