#pragma once

#include <OIS.h>
#include "MyGui.h"
#include "MyGuiManager.h"
#include "GroupSettingUI.h"

class CPlayerController;
class CCameraController;
class CInputSystem;


using namespace Ogre;
class CGameApp
{
protected:
	CGameApp(void);
	virtual ~CGameApp(void);

public:
	static CGameApp* GetGameApp()
	{
		static CGameApp gameApp;

		return &gameApp;
	}

public:
	BOOL InitGame();

	BOOL RunGame();
	
	BOOL UninitGame();

protected:
	BOOL CreateInputSystem();

	BOOL CreateUISystem();

public:
	BOOL CreatePlayer();

public:
	CCameraController *m_pCameraControl;
	CPlayerController *m_pMainPlayer;
	CInputSystem	  *m_pInputSystem;
	CMyGuiManager	  *m_pMyGuiManager;
	BaseUI::CGroupSettingUI   m_GroupSettingUI;
};

