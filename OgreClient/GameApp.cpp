#include "StdAfx.h"
#include "GameApp.h"
#include "CameraController.h"
#include "PlayerController.h"
#include "InputSystemManager.h"

CGameApp::CGameApp(void)
{
	m_pCameraControl= NULL;
	m_pMainPlayer	= NULL;
	m_pInputSystem  = NULL;
}


CGameApp::~CGameApp(void)
{
}

BOOL CGameApp::InitGame()
{
	g_Debuginfo.PrintfInfo("---Start InitGame!\n");

	if(!CreatePlayer())
	{
		return FALSE;
	}
	
	if(!CreateInputSystem())
	{
		return FALSE;
	}

	if(!CreateUISystem())
	{
		return FALSE;
	}

	g_Debuginfo.PrintfInfo("---End InitGame!\n");

	return TRUE;
}

BOOL CGameApp::RunGame()
{
	DWORD dwTick = GetTickCount();
	DWORD dwTick2 = 0;
	int nTimes = 0;

	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);

	//SetCursor(hCursor);

	//ShowCursor(TRUE);
	
	while(TRUE)
	{
		WindowEventUtilities::messagePump();

		m_pInputSystem->Capture();

		m_pMainPlayer->UpdatePlayerControl();
		
		m_pMainPlayer->UpdateAnimation();
		
		m_pCameraControl->UpdateCameraControl();
		

		//***************************************************************
		nTimes++;

		dwTick2 = GetTickCount();
		if((dwTick2-dwTick)>1000)
		{
			dwTick = dwTick2;

			g_Debuginfo.PrintfInfo("%d\n",nTimes);

			nTimes = 0;
		}
		//***************************************************************
	}

	return TRUE;
}





BOOL CGameApp::CreatePlayer()
{
	m_pMainPlayer = new CPlayerController;

	m_pMainPlayer->CreatePlayer(m_World.m_pSceneManager);

	m_pCameraControl->SetBindObject(m_pMainPlayer);

	m_pMainPlayer->SetCameraControl(m_pCameraControl);

	return TRUE;
}

BOOL CGameApp::UninitGame()
{
	if(m_pMainPlayer != NULL)
	{
		delete m_pMainPlayer;
		m_pMainPlayer = NULL;
	}

	if(m_pCameraControl != NULL)
	{
		delete m_pCameraControl;
		m_pCameraControl = NULL;
	}

	if(m_pInputSystem != NULL)
	{
		delete m_pInputSystem;
		m_pInputSystem = NULL;
	}
	
	return TRUE;
}

BOOL CGameApp::CreateInputSystem()
{
	m_pInputSystem = new CInputSystem;

	m_pInputSystem->SetCameraAndPlayer(m_pCameraControl, m_pMainPlayer);

	return m_pInputSystem->CreateInputSystem(m_World.m_pRenderWindow);
}

BOOL CGameApp::CreateUISystem()
{
	m_pMyGuiManager = new CMyGuiManager;

	m_pMyGuiManager->CreateUISystem(m_World.m_pSceneManager, m_World.m_pRenderWindow, m_World.m_pActiveCamera);

	m_GroupSettingUI.LoadUI();

	m_GroupSettingUI.Show(true);

	m_pInputSystem->m_pGuiSystem = m_pMyGuiManager;

	return TRUE;
}
