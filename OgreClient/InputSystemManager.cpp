#include "StdAfx.h"
#include "InputSystemManager.h"


CInputSystem::CInputSystem(void)
{
	m_pInputManager = NULL;
	m_pKeyboard 	= NULL;
	m_pMouse		= NULL;
	m_pCameraController = NULL;
	m_pPlayerController = NULL;
	m_pGuiSystem    = NULL;

}


CInputSystem::~CInputSystem(void)
{
	
}


BOOL CInputSystem::CreateInputSystem(Ogre::RenderWindow *pRenderWindow)
{
	OIS::ParamList tParamList;
	size_t hWindow = 0;

	pRenderWindow->getCustomAttribute("WINDOW", &hWindow);
	std::ostringstream windowHndStr;
	windowHndStr << hWindow;

	tParamList.insert(std::make_pair("WINDOW", windowHndStr.str()));
	tParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	tParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	m_pInputManager = OIS::InputManager::createInputSystem(tParamList);
	if (m_pInputManager == NULL)
	{
		return FALSE;
	}

	m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject(OIS::OISKeyboard, true));
	if (m_pKeyboard == NULL)
	{
		return FALSE;
	}

	m_pMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject(OIS::OISMouse, true));
	if (m_pMouse == NULL)
	{
		return FALSE;
	}

	m_pKeyboard->setEventCallback(this);

	m_pMouse->setEventCallback(this);

	const OIS::MouseState &th_mstate = m_pMouse->getMouseState();
	th_mstate.width  = pRenderWindow->getWidth();
	th_mstate.height = pRenderWindow->getHeight();

	return TRUE;
}

BOOL CInputSystem::Capture()
{
	if(m_pKeyboard != NULL)
	{
		m_pKeyboard->capture();
	}

	if(m_pMouse != NULL)
	{
		m_pMouse->capture();
	}

	/*for (int i = 0; i < 256; i++)
	{
	if (m_pKeyboard->isKeyDown(OIS::KeyCode(i)))
	keyPressed(OIS::KeyEvent(m_pKeyboard, OIS::KeyCode(i), 0));
	}
	*/

	return TRUE;
}

bool CInputSystem::keyPressed( const OIS::KeyEvent &arg )
{
	m_pCameraController->keyPressed(arg);
	m_pPlayerController->keyPressed(arg);
	

	MyGUI::Char text ='/';
	MyGUI::KeyCode key = MyGUI::KeyCode::Enum(arg.key);
	int scan_code = key.toValue();

	if (scan_code > 70 && scan_code < 84)
	{
		static MyGUI::Char nums[13] = { 55, 56, 57, 45, 52, 53, 54, 43, 49, 50, 51, 48, 46 };
		text = nums[scan_code-71];
	}
	else if (key == MyGUI::KeyCode::Divide)
	{
		text = '/';
	}


	m_pGuiSystem->injectKeyPress(key, text);		
	
	return true;
}

bool CInputSystem::keyReleased( const OIS::KeyEvent &arg )
{
	m_pCameraController->keyReleased(arg);
	m_pPlayerController->keyReleased(arg);

	m_pGuiSystem->injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));

	return true;
}

bool CInputSystem::mouseMoved( const OIS::MouseEvent &arg )
{
	m_pCameraController->mouseMoved(arg);
	m_pPlayerController->mouseMoved(arg);
	m_pGuiSystem->injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);


	return true;
}

bool CInputSystem::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	m_pCameraController->mousePressed(arg,id);
	m_pPlayerController->mousePressed(arg,id);
	m_pGuiSystem->injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton((MyGUI::MouseButton::Enum)id));
	return true;
}

bool CInputSystem::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	m_pCameraController->mouseReleased(arg,id);
	m_pPlayerController->mouseReleased(arg,id);
	m_pGuiSystem->injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton((MyGUI::MouseButton::Enum)id));
	return true;
}

BOOL CInputSystem::SetCameraAndPlayer( CCameraController *pCameraController, CPlayerController *pPlayerController )
{
	m_pCameraController = pCameraController;
	m_pPlayerController = pPlayerController;

	return TRUE;
}
