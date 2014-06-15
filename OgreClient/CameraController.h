#pragma once
#include "Ogre.h"
#include "OIS/OIS.h"
#include "PlayerController.h"
class CCameraController
{
public:
	CCameraController();
	virtual ~CCameraController(void);
public:

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);	
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	BOOL CreateCameraControl( Ogre::SceneManager *pSceneManager );

	BOOL UpdateCameraControl();

	Ogre::Camera* GetCameraPtr();


	BOOL SetBindObject(CPlayerController *pBindObject);

	VOID Rotate(float x, float y);

	Vector3 GetDirection();

	void LockCamera();
	void UnLockCamera();

public:
	BOOL	m_bPositionUpate;
	BOOL	m_bLocked;
	Vector3 m_vtBindObjPos;
	BOOL    m_bMoveCameraFar;
	BOOL    m_bMoveCameraNear;

protected:
	CPlayerController	*m_pBindObject;
	Ogre::SceneManager	*m_pSceneManager;
	Ogre::Camera		*m_pCamera;
	Ogre::Vector3		m_vecUnitDir;
	Ogre::Vector3		m_vecDstPos;
	float				m_fDistance;
};

