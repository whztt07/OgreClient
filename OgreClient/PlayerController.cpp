#include "StdAfx.h"
#include "PlayerController.h"
#include "CameraController.h"
#include "GameApp.h"

CPlayerController::CPlayerController(void)
{
	m_pSceneManager = NULL;
	m_pEntity = NULL;
	m_pSceneNode = NULL;
	m_dwAnimateIndex = 0;
	m_pCameraController = NULL;
	m_bUp		= FALSE;
	m_bDown		= FALSE;
	m_bRight	= FALSE;
	m_bLeft		= FALSE;
	m_bChangePos= FALSE;
}


CPlayerController::~CPlayerController(void)
{
	
}

BOOL CPlayerController::CreatePlayer( Ogre::SceneManager *pSceneManager )
{
	m_pSceneNode = pSceneManager->getRootSceneNode()->createChildSceneNode( "RobotNode");

	Entity *face = pSceneManager->createEntity( "face", "p_m_face_02_face.mesh");
	face->setMaterialName("p_m_face_01");
	m_pSceneNode->attachObject(face);

	Entity *hair = pSceneManager->createEntity( "hair", "p_m_hair_02_t.mesh");
	hair->setMaterialName("p_m_hair_02_t");
	m_pSceneNode->attachObject( hair );
	hair->shareSkeletonInstanceWith(face);

	Entity *neiyi = pSceneManager->createEntity( "neiyi", "p_m_neiyi1_f.mesh");
	neiyi->setMaterialName("p_m_luomo1_x");
	m_pSceneNode->attachObject( neiyi );
	neiyi->shareSkeletonInstanceWith(face);

	Entity *pijia = pSceneManager->createEntity( "pijia", "p_m_neiyi1_k.mesh");
	pijia->getSubEntity(0)->setMaterialName("p_m_luomo1_x");
	pijia->getSubEntity(1)->setMaterialName("p_m_neiyi1_k");
	m_pSceneNode->attachObject( pijia );
	pijia->shareSkeletonInstanceWith(face);

	Entity *banjia = pSceneManager->createEntity( "banjia", "p_m_neiyi1_x.mesh");
	banjia->setMaterialName("p_m_luomo1_x");
	m_pSceneNode->attachObject( banjia );
	banjia->shareSkeletonInstanceWith(face);

	Entity *shou = pSceneManager->createEntity( "shou", "p_m_neiyi1_w.mesh");
	shou->setMaterialName("p_m_luomo1_x");
	m_pSceneNode->attachObject( shou );
	shou->shareSkeletonInstanceWith(face);

	Entity *wuqi = pSceneManager->createEntity( "wuqi", "w_s_dawuqi_01.mesh");
	shou->setMaterialName("w_s_dawuqi_01");

	shou->attachObjectToBone("Bip01 R Hand", wuqi);

	face->getSkeleton()->addLinkedSkeletonAnimationSource("p_m_idle.skeleton");
	face->getSkeleton()->addLinkedSkeletonAnimationSource("p_m_run.skeleton");
	face->getSkeleton()->addLinkedSkeletonAnimationSource("p_m_sit_down.skeleton");
	face->getSkeleton()->addLinkedSkeletonAnimationSource("p_m_jump_star.skeleton");

	face->refreshAvailableAnimationState();

	ParticleSystem* ps = pSceneManager->createParticleSystem("Aureola", "Examples/Aureola");
	m_pSceneNode->attachObject(ps);

	/*Ogre::AnimationStateSet *pSet = face->getAllAnimationStates();
	Ogre::ConstEnabledAnimationStateIterator itor = pSet->getEnabledAnimationStateIterator();*/

	mAnims[0] = face->getAnimationState("idle");
	mAnims[1] = face->getAnimationState("run");
	mAnims[2] = face->getAnimationState("jump_star");

	return TRUE;
}

Ogre::Vector3 CPlayerController::GetPosition()
{
	return m_pSceneNode->getPosition();
}

void CPlayerController::SetPosition( Vector3 &vtNewPos )
{
	m_pSceneNode->setPosition(vtNewPos);
}

void CPlayerController::SetDirection( Vector3 &vtDir )
{
	m_pSceneNode->setDirection(vtDir,Ogre::Node::TS_WORLD);
}

bool CPlayerController::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_W:
		{
			PlayerAnimation(1);
			m_bUp = TRUE;
		}
		break;
	case OIS::KC_A:
		{
			PlayerAnimation(1);
			m_bLeft = TRUE;
		}
		break;
	case OIS::KC_S:
		{
			PlayerAnimation(1);
			m_bDown = TRUE;
		}
		break;
	case OIS::KC_D:
		{
			PlayerAnimation(2);
			m_bRight = TRUE;
		}
		break;
	default:
		break;
	}

	return true;
}

bool CPlayerController::keyReleased( const OIS::KeyEvent &arg )
{
	
	switch (arg.key)
	{
	case OIS::KC_W:
		{
			m_bUp = FALSE;
		}
		break;
	case OIS::KC_A:
		{
			m_bLeft = FALSE;
		}
		break;
	case OIS::KC_S:
		{
			m_bDown = FALSE;
		}
		break;
	case OIS::KC_D:
		{
			m_bRight = FALSE;
		}
		break;
	case OIS::KC_1:
		{
			PlayerAnimation(1);
		}
		break;
	case OIS::KC_2:
		{
			PlayerAnimation(2);
		}
		break;

	case OIS::KC_3:
		{
			PlayerAnimation(3);
		}
		break;
	case OIS::KC_4:
		{
			PlayerAnimation(4);
		}
		break;
	case OIS::KC_5:
		{
			PlayerAnimation(5);
		}
		break;
	case OIS::KC_6:
		{
			PlayerAnimation(6);
		}
		break;
	case OIS::KC_7:
		{
			PlayerAnimation(7);
		}
		break;
	case OIS::KC_8:
		{
			PlayerAnimation(8);
		}
		break;
	case OIS::KC_9:
		{
			PlayerAnimation(9);
		}
		break;
	default:
		{
			PlayerAnimation(1);
		}
		break;
	}

	if((!m_bDown)&&(!m_bUp)&&(!m_bRight)&&(!m_bLeft))
	{
		PlayerAnimation(1);
	}
	
	return true;
}

bool CPlayerController::mouseMoved( const OIS::MouseEvent &arg )
{
	return true;
}

bool CPlayerController::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

bool CPlayerController::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

BOOL CPlayerController::CreateSinBa( Ogre::SceneManager *pSceneManager )
{
	m_pEntity = pSceneManager->createEntity( "SinbadBody1", "Sinbad.mesh");
	m_pEntity->setCastShadows(true);
	m_pSceneNode = pSceneManager->getRootSceneNode()->createChildSceneNode( "RobotNode1",Vector3::UNIT_Y * 5 );
	m_pSceneNode->attachObject( m_pEntity );
	m_pSceneNode->translate(Vector3(1963, 65, 1660));

	mSword1 = pSceneManager->createEntity("SinbadSword1", "Sword.mesh");
	mSword2 = pSceneManager->createEntity("SinbadSword2", "Sword.mesh");
	m_pEntity->attachObjectToBone("Sheath.L", mSword1);
	m_pEntity->attachObjectToBone("Sheath.R", mSword2);

	String animNames[] =
	{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
	"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

	// populate our animation list
	for (int i = 0; i < 13; i++)
	{
		mAnims[i] = m_pEntity->getAnimationState(animNames[i]);
	}

	return TRUE;
}

BOOL CPlayerController::PlayerAnimation( UINT32 dwIndex )
{
	//return TRUE;
	if(dwIndex == m_dwAnimateIndex)
	{
		return TRUE;
	}

	mAnims[m_dwAnimateIndex]->setEnabled(false);
	m_dwAnimateIndex = dwIndex;
	mAnims[m_dwAnimateIndex]->setEnabled(true);
	mAnims[m_dwAnimateIndex]->setTimePosition(0);

	return TRUE;
}

BOOL CPlayerController::UpdateAnimation()
{
	//return TRUE;
	static DWORD dwTick1 = 0;
	static DWORD dwTick2 = 0;
	dwTick2 = GetTickCount();
	float time = dwTick2;
	time -= dwTick1;
	time = time / 1000;
	mAnims[m_dwAnimateIndex]->addTime(time);
	dwTick1 = dwTick2;

	return TRUE;
}

BOOL CPlayerController::SetCameraControl( CCameraController *pCameraControl )
{
	m_pCameraController = pCameraControl;

	return TRUE;
}

BOOL CPlayerController::UpdatePlayerControl()
{
	m_bChangePos = TRUE;
	float fAngle = 0;
	if (m_bUp)
	{
		if(m_bLeft)
		{
			fAngle = 45;
		}
		else if(m_bRight)
		{
			fAngle = 315;
		}
		else
		{
			fAngle = 0;
		}
	}
	else if (m_bDown)
	{
		if(m_bLeft)
		{
			fAngle = 135;
		}
		else if(m_bRight)
		{
			fAngle = 2225;
		}
		else
		{
			fAngle = 180;
		}
	}
	else if(m_bLeft)
	{
		fAngle = 90;
	}
	else if(m_bRight)
	{
		fAngle = 270;
	}
	else
	{
		m_bChangePos = FALSE;
	}

	if(m_bChangePos)
	{
		Vector3 vtDir = m_pCameraController->GetDirection();
		vtDir.y = 0;
		vtDir.x *= -1;
		vtDir.z *= -1;
		m_pSceneNode->setDirection(vtDir,Ogre::Node::TS_WORLD);
		m_pSceneNode->yaw(Ogre::Degree(fAngle));
		
		
		m_pSceneNode->translate(0,0,0.5,Ogre::Node::TS_LOCAL);

		Vector3 vtPos = m_pSceneNode->getPosition();

		//float fhight = CGameApp::GetGameApp()->m_World.GetPositionHeight(vtPos);

		//vtPos.y = fhight+5;

		m_pSceneNode->setPosition(vtPos);
	}

	return TRUE;
}
