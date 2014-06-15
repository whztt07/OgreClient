/*!
	@file
	@author		Albert Semenov
	@date		08/2008
*/

#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

#include <Ogre.h>
#include <MyGUI.h>

#include "MyGUI_LastHeader.h"

namespace MyGUI
{
	class OgrePlatform;
}


class CMyGuiManager
{
public:
	CMyGuiManager();
	virtual ~CMyGuiManager();

	bool CreateUISystem(Ogre::SceneManager* pSceneMgr, Ogre::RenderWindow* pRenderWin, Ogre::Camera* pCamera);
	void DestroyUISystem();

	void setWindowCaption(const std::wstring& _text);
	void createDefaultScene();
	void makeScreenShot();

	const std::string& getRootMedia();
	void setResourceFilename(const std::string& _flename);
	void addResourceLocation(const std::string& _name, bool _recursive = false);

/*internal:*/
	Ogre::SceneManager* getSceneManager();
	Ogre::Camera* getCamera();


	virtual void setupResources();

	virtual void injectMouseMove(int _absx, int _absy, int _absz);
	virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id);
	virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);
	virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
	virtual void injectKeyRelease(MyGUI::KeyCode _key);

private:
	void createGui();
	void destroyGui();

	virtual void windowResized(Ogre::RenderWindow* _rw);
	virtual void windowClosed(Ogre::RenderWindow* _rw);

	void addResourceLocation(const std::string& _name, const std::string& _group, const std::string& _type, bool _recursive);

private:
	MyGUI::Gui* mGUI;
	MyGUI::OgrePlatform* mPlatform;
	Ogre::Root* mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mWindow;

	Ogre::String mResourcePath;
	std::string mPluginCfgName;
	std::string mResourceXMLName;
	std::string mResourceFileName;
	std::string mRootMedia;

	Ogre::SceneNode* mNode;
};

#endif // __BASE_MANAGER_H__
