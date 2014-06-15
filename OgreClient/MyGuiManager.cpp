/*!
	@file
	@author		Albert Semenov
	@date		08/2008
*/

#include "stdafx.h"
#include "MyGuiManager.h"
#include <MyGUI_OgrePlatform.h>

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#	include <windows.h>
#endif

	CMyGuiManager::CMyGuiManager() :
		mGUI(nullptr),
		mPlatform(nullptr),
		mRoot(nullptr),
		mCamera(nullptr),
		mSceneManager(nullptr),
		mWindow(nullptr),
		mPluginCfgName("plugins.cfg"),
		mResourceXMLName("ClientUI_res.xml"),
		mResourceFileName("MyGUI_Core.xml"),
		mNode(nullptr)
	{
		mResourcePath = "";
	}

	CMyGuiManager::~CMyGuiManager()
	{
	}

	bool CMyGuiManager::CreateUISystem(Ogre::SceneManager* pSceneMgr, Ogre::RenderWindow* pRenderWin, Ogre::Camera* pCamera)
	{
		mSceneManager = pSceneMgr;

		mCamera = pCamera;
		
		mWindow = pRenderWin;

		setupResources();

		createGui();

		windowResized(mWindow);

		return true;
	}


	void CMyGuiManager::DestroyUISystem()
	{

		destroyGui();

		// очищаем сцену
		if (mSceneManager)
		{
			mSceneManager->clearScene();
			mSceneManager->destroyAllCameras();
			mSceneManager = nullptr;
			mCamera = nullptr;
		}

		if (mWindow)
		{
			mWindow->destroy();
			mWindow = nullptr;
		}

		if (mRoot)
		{
			Ogre::RenderWindow* window = mRoot->getAutoCreatedWindow();
			if (window)
				window->removeAllViewports();
			delete mRoot;
			mRoot = nullptr;
		}

	}

	void CMyGuiManager::createGui()
	{
		mPlatform = new MyGUI::OgrePlatform();

		mPlatform->initialise(mWindow, mSceneManager);

		mGUI = new MyGUI::Gui();

		mGUI->initialise(mResourceFileName);
	}

	void CMyGuiManager::destroyGui()
	{
		if (mGUI)
		{
			mGUI->shutdown();
			delete mGUI;
			mGUI = nullptr;
		}

		if (mPlatform)
		{
			mPlatform->shutdown();
			delete mPlatform;
			mPlatform = nullptr;
		}
	}

	void CMyGuiManager::setupResources()
	{
		MyGUI::xml::Document doc;

		if (!doc.open(mResourceXMLName))
			doc.getLastError();

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				bool rootAttr = false;
				if (node->findAttribute("root") != "")
				{
					rootAttr = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (rootAttr) mRootMedia = node->getContent();
				}
				addResourceLocation(node->getContent());
			}
		}

		addResourceLocation(getRootMedia() + "/Common/Base");
	}


	void CMyGuiManager::windowResized(Ogre::RenderWindow* _rw)
	{
		int width = (int)_rw->getWidth();
		int height = (int)_rw->getHeight();

		if (mCamera)
		{
			mCamera->setAspectRatio((float)width / (float)height);
		}
	}

	void CMyGuiManager::windowClosed(Ogre::RenderWindow* _rw)
	{

	}

	void CMyGuiManager::setWindowCaption(const std::wstring& _text)
	{
	#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		size_t handle = 0;
		mWindow->getCustomAttribute("WINDOW", &handle);
		::SetWindowTextW((HWND)handle, _text.c_str());
	#endif
	}

	void CMyGuiManager::addResourceLocation(const std::string& _name, const std::string& _group, const std::string& _type, bool _recursive)
	{
		#if MYGUI_PLATFORM == MYGUI_PLATFORM_APPLE
			// OS X does not set the working directory relative to the app, In order to make things portable on OS X we need to provide the loading with it's own bundle path location
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Ogre::String(macBundlePath() + "/" + _name), _type, _group, _recursive);
		#else
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(_name, _type, _group, _recursive);
		#endif
	}

	void CMyGuiManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		addResourceLocation(_name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "FileSystem", false);
	}

	void CMyGuiManager::createDefaultScene()
	{
		try
		{
			Ogre::Entity* entity = mSceneManager->createEntity("Mikki.mesh", "Mikki.mesh");
			mNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
			mNode->attachObject(entity);
		}
		catch (Ogre::FileNotFoundException&)
		{
			return;
		}

		try
		{
			Ogre::MeshManager::getSingleton().createPlane(
				"FloorPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000, 1000, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

			Ogre::Entity* entity = getSceneManager()->createEntity("FloorPlane", "FloorPlane");
			entity->setMaterialName("Ground");
			mNode->attachObject(entity);
		}
		catch (Ogre::FileNotFoundException&)
		{
			return;
		}
	}

	void CMyGuiManager::injectMouseMove(int _absx, int _absy, int _absz)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
	}

	void CMyGuiManager::injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
	}

	void CMyGuiManager::injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
	}

	void CMyGuiManager::injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text)
	{
		if (!mGUI)
			return;

		if (_key == MyGUI::KeyCode::Escape)
		{
			return;
		}
		else if (_key == MyGUI::KeyCode::SysRq)
		{
			makeScreenShot();
			return;
		}

		// change polygon mode
		// TODO: polygon mode require changes in platform
		else if (_key == MyGUI::KeyCode::F5)
		{
			getCamera()->setPolygonMode(Ogre::PM_SOLID);
		}
		else if (_key == MyGUI::KeyCode::F6)
		{
			getCamera()->setPolygonMode(Ogre::PM_WIREFRAME);
		}
		else if (_key == MyGUI::KeyCode::F7)
		{
			getCamera()->setPolygonMode(Ogre::PM_POINTS);
		}
#if OGRE_VERSION >= MYGUI_DEFINE_VERSION(1, 7, 0) && OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0
		else if (_key == MyGUI::KeyCode::F1)
		{
			mWindow->getViewport(0)->setOrientationMode(Ogre::OR_DEGREE_0, false);
			mPlatform->getRenderManagerPtr()->setRenderWindow(mWindow);
		}
		else if (_key == MyGUI::KeyCode::F2)
		{
			mWindow->getViewport(0)->setOrientationMode(Ogre::OR_DEGREE_90, false);
			mPlatform->getRenderManagerPtr()->setRenderWindow(mWindow);
		}
		else if (_key == MyGUI::KeyCode::F3)
		{
			mWindow->getViewport(0)->setOrientationMode(Ogre::OR_DEGREE_180, false);
			mPlatform->getRenderManagerPtr()->setRenderWindow(mWindow);
		}
		else if (_key == MyGUI::KeyCode::F4)
		{
			mWindow->getViewport(0)->setOrientationMode(Ogre::OR_DEGREE_270, false);
			mPlatform->getRenderManagerPtr()->setRenderWindow(mWindow);
		}
#endif
		MyGUI::InputManager::getInstance().injectKeyPress(_key, _text);
	}

	void CMyGuiManager::injectKeyRelease(MyGUI::KeyCode _key)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectKeyRelease(_key);
	}

	const std::string& CMyGuiManager::getRootMedia()
	{
		return mRootMedia;
	}

	void CMyGuiManager::setResourceFilename(const std::string& _flename)
	{
		mResourceFileName = _flename;
	}

	Ogre::SceneManager* CMyGuiManager::getSceneManager()
	{
		return mSceneManager;
	}

	Ogre::Camera* CMyGuiManager::getCamera()
	{
		return mCamera;
	}

	void CMyGuiManager::makeScreenShot()
	{
		std::ifstream stream;
		std::string file;
		do
		{
			stream.close();
			static size_t num = 0;
			const size_t max_shot = 100;
			if (num == max_shot)
			{
				MYGUI_LOG(Info, "The limit of screenshots is exceeded : " << max_shot);
				return;
			}
			file = MyGUI::utility::toString("screenshot_", ++num, ".png");
			stream.open(file.c_str());
		}
		while (stream.is_open());
		mWindow->writeContentsToFile(file);
	}

