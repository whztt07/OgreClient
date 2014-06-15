#include "StdAfx.h"
#include "CameraController.h"
#include "TerrainManager.h"
#include "GameApp.h"

CCameraController::CCameraController()
{
	m_pCamera = NULL;
	m_pBindObject = NULL;
	m_pSceneManager = NULL;

	m_vecUnitDir.x = 0.577f;
	m_vecUnitDir.y = 0.577f;
	m_vecUnitDir.z = 0.577f;
	m_fDistance = 10;

	m_bPositionUpate	= TRUE;
	m_bLocked			= FALSE;
	m_bMoveCameraFar	= FALSE;
	m_bMoveCameraNear   = FALSE;
}


CCameraController::~CCameraController(void)
{
}

BOOL CCameraController::CreateCameraControl( Ogre::SceneManager *pSceneManager )
{
	m_pSceneManager = pSceneManager;

	m_pCamera = m_pSceneManager->createCamera("PlayerCam");

	m_pCamera->setNearClipDistance(1);

	m_pCamera->setFarClipDistance(5000);

	return TRUE;
}

BOOL CCameraController::SetBindObject( CPlayerController *pBindObject )
{
	m_pBindObject = pBindObject;

	return TRUE;
}

VOID CCameraController::Rotate( float x, float y )
{
	float angle = -x * 0.01f;
	float xt = m_vecUnitDir.x * cos(angle) + m_vecUnitDir.z * sin(angle);
	float zt = m_vecUnitDir.z * cos(angle) - m_vecUnitDir.x * sin(angle);
	m_vecUnitDir.x = xt;
	m_vecUnitDir.z = zt;


	//¼ÆËãXZÐý×ªÖá
	Ogre::Vector3 axis;
	axis.x = -m_vecUnitDir.z;
	axis.z = m_vecUnitDir.x;
	axis.y = 0;
	axis.normalise();

	//ÑØÖáÐý×ª
	{
		float angle = y * 0.01f;
		float x = 
			m_vecUnitDir.x * (axis.x * axis.x * (1 - cos(angle)) + cos(angle)) + 
			m_vecUnitDir.y * (axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle)) +
			m_vecUnitDir.z * (axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle));
		float y = 
			m_vecUnitDir.x * (axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle)) + 
			m_vecUnitDir.y * (axis.y * axis.y * (1 - cos(angle)) + cos(angle)) + 
			m_vecUnitDir.z * (axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle));
		float z = 
			m_vecUnitDir.x * (axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle)) +
			m_vecUnitDir.y * (axis.y * axis.z * (1 - cos(angle)) + axis.x * sin(angle)) +
			m_vecUnitDir.z * (axis.z * axis.z * (1 - cos(angle)) + cos(angle));
		m_vecUnitDir.x = x;
		m_vecUnitDir.y = y;
		m_vecUnitDir.z = z;
	}

	m_bPositionUpate = TRUE;
	
}

BOOL CCameraController::UpdateCameraControl()
{
	if (m_bLocked)
	{
		return TRUE;
	}

	Vector3 vtNewPos = m_pBindObject->GetPosition();
	if((m_vtBindObjPos == vtNewPos)&&(!m_bPositionUpate)&&!m_bMoveCameraFar&&!m_bMoveCameraNear)
	{
		return TRUE;
	}

	if(m_bMoveCameraNear)
	{
		m_fDistance -= 0.05;
	}

	if(m_bMoveCameraFar)
	{
		m_fDistance += 0.05;
	}

	m_vtBindObjPos = vtNewPos;

	m_vecDstPos = m_vecUnitDir * m_fDistance + m_vtBindObjPos;

	

	Ogre::Vector3 RayDir = m_vecDstPos-vtNewPos;
	RayDir.normalise();

	Ogre::Ray SearchRay;
	SearchRay.setOrigin(vtNewPos);
	SearchRay.setDirection(RayDir);

	g_Debuginfo.PrintfInfo("m_vecDstPos x:%.2f-y:%.2f-z:%.2f!||", m_vecDstPos.x,m_vecDstPos.y,m_vecDstPos.z);

	
	Ogre::TerrainGroup::RayResult rayResult = CGameApp::GetGameApp()->m_World.m_pTerrainGroup->rayIntersects(SearchRay);
	if(rayResult.hit)
	{
		if((rayResult.position-vtNewPos).length()<m_fDistance)
		{
			m_vecDstPos = rayResult.position;
			m_vecDstPos .y += 1;
			g_Debuginfo.PrintfInfo("hit -- rayResult x:%.2f--y:%.2f--z:%.2f!\n", rayResult.position.x,rayResult.position.y,rayResult.position.z);
		}
		else
		{
			g_Debuginfo.PrintfInfo("hit --rayResult x:1--y:1--z:1!\n");
		}
		
	}
	else
	{
		g_Debuginfo.PrintfInfo("unhit --rayResult x:0--y:0--z:0!\n");
	}

	m_pCamera->lookAt(vtNewPos+Vector3(0,1.5,0));

	m_pCamera->setPosition(m_vecDstPos);

	m_bPositionUpate = FALSE;

	return TRUE;
}

Ogre::Camera* CCameraController::GetCameraPtr()
{
	return m_pCamera;
}

bool CCameraController::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_DOWN:
		{
			m_bMoveCameraFar = TRUE;
		}
		break;
	case OIS::KC_UP:
		{
			m_bMoveCameraNear= TRUE;
		}
		break;
	default:
		break;
	}
	return true;
}

bool CCameraController::keyReleased( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_DOWN:
		{
			m_bMoveCameraFar = FALSE;
		}
		break;
	case OIS::KC_UP:
		{
			m_bMoveCameraNear= FALSE;
		}
		break;
	default:
		break;
	}
	return true;
}

bool CCameraController::mouseMoved( const OIS::MouseEvent &arg )
{
	Ogre::Vector3 vtPlayerPos = m_pBindObject->GetPosition();
	if( arg.state.buttonDown( OIS::MB_Right ) )
	{
		Rotate(arg.state.X.rel, arg.state.Y.rel);

		Ogre::Vector3 vtCamera = m_pCamera->getPosition();

		Ogre::Vector3 vtDir = vtCamera-vtPlayerPos;

		vtDir.normalise();
		vtDir.y = 0;
		m_pBindObject->SetDirection(vtDir);
	}

	if( arg.state.buttonDown( OIS::MB_Left ) )
	{
		Rotate(arg.state.X.rel, arg.state.Y.rel);
	}
	return true;
}

bool CCameraController::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{

	return true;
}

bool CCameraController::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

Ogre::Vector3 CCameraController::GetDirection()
{
	return m_pCamera->getDirection();
}

void CCameraController::LockCamera()
{
	m_bLocked = TRUE;
}

void CCameraController::UnLockCamera()
{
	m_bLocked = FALSE;
}
