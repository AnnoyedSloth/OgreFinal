#include "stdafx.h"
#include "Main.h"


#pragma region Setup
ProjectFarm::ProjectFarm()
	: mRoot(0), mShutdown(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	mWindow(0), mSceneMgr(0), mCamera(0), mInputMgr(0), mMouse(0), mKeyboard(0)
{

}

ProjectFarm::~ProjectFarm()
{

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}

void ProjectFarm::go()
{
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;


	//if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	//return false;

	mRoot->startRendering();

	destroyScene();

}

bool ProjectFarm::setup()
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	if (!configure())
		return false;

	chooseSceneManager();
	createCamera();
	createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(10);

	createResourceListener();
	loadResources();

	createScene();
	createFrameListener();

	return true;
}

bool ProjectFarm::configure()
{
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}

	mWindow = mRoot->initialise(true, "ProjectFarm");

	return true;
}

void ProjectFarm::createCamera()
{
	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setNearClipDistance(5);
}

void ProjectFarm::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

#pragma endregion

//조작 구현
bool ProjectFarm::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		mShutdown = true;
	}

	if (mShutdown)
	{
		return false;
	}

	if (mWindow->isClosed()) return false;
	//
	//mPlayerNode->translate(playerDirection *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	mKeyboard->capture();
	mMouse->capture();

	mPlayer->UpdatePosition(fe);

	//playerptr->MovePlayer(fe);

	//mCameraNode->translate(playerptr->getPosition() *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	//mPlayerAnimationState->addTime(fe.timeSinceLastFrame);

	return true;
}

bool ProjectFarm::mouseMoved(const OIS::MouseEvent& me)
{
	//mCamera->yaw(Degree(-0.05f * me.state.X.rel));
	mPlayer->PlayerRotation(mCamera, me);
	return true;
}
bool ProjectFarm::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}
bool ProjectFarm::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}

bool ProjectFarm::keyPressed(const OIS::KeyEvent& ke)
{
	mPlayer->PlayerTranslation(ke);
	return true;
}
bool ProjectFarm::keyReleased(const OIS::KeyEvent& ke)
{
	mPlayer->ReleasedKey(ke);
	return true;
}


void ProjectFarm::chooseSceneManager()
{
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}


//Create Overall Scene
void ProjectFarm::createScene()
{
	mSceneSetter = new SceneSetter();
	mSceneSetter->GroundSetting(mSceneMgr);
	mSceneSetter->ObjectSetting(mSceneMgr);
	mSceneSetter->LightSetting(mSceneMgr);
	mSceneSetter->ParticleSetting(mSceneMgr);

	mPlayer = new PlayerManager(mSceneMgr, mCamera);

}

#pragma region Irrelevant

void ProjectFarm::destroyScene()
{
}

void ProjectFarm::createFrameListener()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(
		mInputMgr->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(
		mInputMgr->createInputObject(OIS::OISMouse, true));

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);

	windowResized(mWindow);

	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	Ogre::LogManager::getSingletonPtr()->logMessage("Finished");
}

void ProjectFarm::setupResources()
{
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}

void ProjectFarm::createResourceListener()
{
}

void ProjectFarm::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void ProjectFarm::windowResized(Ogre::RenderWindow* rw)
{
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void ProjectFarm::windowClosed(Ogre::RenderWindow* rw)
{
	if (rw == mWindow)
	{
		if (mInputMgr)
		{
			mInputMgr->destroyInputObject(mMouse);
			mInputMgr->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputMgr);
			mInputMgr = 0;
		}
	}
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		ProjectFarm app;

		try
		{
			app.go();
		}
		catch (Ogre::Exception& e)
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			/*
			MessageBox(
			NULL,
			e.getFullDescription().c_str(),
			"An exception has occured!",
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
			*/
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}
#ifdef __cplusplus
}
#endif

#pragma endregion
