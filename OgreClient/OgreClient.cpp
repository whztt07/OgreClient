// GameOne.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "OgreClient.h"
#include "GameApp.h"
#include "SampleApp.h"



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//CGameApp *pGameApp = CGameApp::GetGameApp();

	//if(pGameApp->InitGame())
	//{
	//	pGameApp->RunGame();
	//}

	//pGameApp->UninitGame();

	SampleApp app;

	try {
		app.go();
	} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

