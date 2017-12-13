#pragma once
#include "stdafx.h"
#include "Main.h"


#pragma region Setup
ProjectFarm::ProjectFarm()
	: mRoot(0), mShutdown(0), isStarted(false),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	mWindow(0), mSceneMgr(0), mFirstScene(0), mLastScene(0), mCamera(0), mInputMgr(0), mMouse(0), mKeyboard(0),
	timer(30), mTimerInfo(0), mScoreInfo(0), mBulletInfo(0), mOverlaySystem(0), isMainScene(0)
{

}

ProjectFarm::~ProjectFarm()
{

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}

static void sceneSwap(SceneManager *&before, SceneManager *&after) {
	SceneManager *tmp = before;
	before = after;
	after = tmp;
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
	mFirstScene->createCamera("MainCam");
	mLastScene->createCamera("LastCam");
}

void ProjectFarm::createViewports()
{
	setupViewport(mFirstScene); // 타이틀 화면 먼저 세팅

	mSceneMgr->setAmbientLight(ColourValue(0.2f, 0.2f, 0.2f));
}

void ProjectFarm::chooseSceneManager()
{
	mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "Main");
	mFirstScene = mRoot->createSceneManager(ST_GENERIC, "First");
	mLastScene = mRoot->createSceneManager(ST_GENERIC, "Last");
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
}

void ProjectFarm::setupViewport(Ogre::SceneManager *curr)
{
	mWindow->removeAllViewports();
	Ogre::Camera *cam = curr->getCamera("MainCam");
	Ogre::Viewport* vp = mWindow->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	isMainScene = true;
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

	mKeyboard->capture();
	mMouse->capture();

	if (isStarted) {
		mPlayer->UpdatePosition(fe);

		mPlayer->BulletMove(fe, mSceneMgr);

		for (int a = 0; a < myEnemy.size(); a++) {
			myEnemy[a]->EnemyTranslation(fe);
		}

		if (isStarted) time = clock();

		timer = 65 - time / CLOCKS_PER_SEC;
		if (timer < 0)
			setupViewport(mLastScene);
		
		String sTimer = "Time : " + std::to_string((int)timer);
		mPlayer->checkcollision(mSceneMgr, myEnemy);
		UIUpdate();
		mTimerInfo->setCaption(sTimer);
	}

	return true;
}


void ProjectFarm::UIUpdate() {
	String sScore = "Score : " + std::to_string((int)mPlayer->getScore());
	String sBulletNum = std::to_string((int)mPlayer->getBulletNum()) + " / 30";
	mScoreInfo->setCaption(sScore);
	mBulletInfo->setCaption(sBulletNum);
}

bool ProjectFarm::mouseMoved(const OIS::MouseEvent& me)
{
	//mCamera->yaw(Degree(-0.05f * me.state.X.rel));
	mPlayer->PlayerRotation(mCamera, me);
	return true;
}
bool ProjectFarm::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	if (id == OIS::MB_Left) {
		mPlayer->BulletShooting(mSceneMgr);
	}

	return true;
}
bool ProjectFarm::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}

bool ProjectFarm::keyPressed(const OIS::KeyEvent& ke)
{
	if (ke.key == OIS::KC_SPACE) {
		
		//if(!isMainScene)sceneSwap(mFirstScene, mSceneMgr);
		setupViewport(mSceneMgr);
		//mEndGame->hide();
		isStarted = true;		
	}
	mPlayer->PlayerTranslation(ke);
	return true;
}
bool ProjectFarm::keyReleased(const OIS::KeyEvent& ke)
{
	mPlayer->ReleasedKey(ke);
	return true;
}

//Create Overall Scene
void ProjectFarm::createScene()
{
	mFirstScene->setSkyDome(true, "Examples/CloudySky", 5, 8);
	//mLastScene->setSkyBox(true, "EveningSkyBox");

	mSceneSetter = new SceneSetter();
	mSceneSetter->GroundSetting(mSceneMgr);
	mSceneSetter->ObjectSetting(mSceneMgr);
	mSceneSetter->LightSetting(mSceneMgr);
	mSceneSetter->ParticleSetting(mSceneMgr);

	mPlayer = new PlayerManager(mSceneMgr, mCamera);
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(-100, -15, 800), "Ninja"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(100,  -15, 600), "Ninja1"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(-250, -15, 1000), "Ninja2"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(250,  -15, 700), "Ninja3"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(-150, -15, 800), "Ninja4"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(150,  -15, 600), "Ninja5"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(50,   -15, 0), "Ninja6"));
	myEnemy.push_back(new Enemy(mSceneMgr, Vector3(-50,  -15, 700), "Ninja7"));
}

#pragma region Irrelevant

void ProjectFarm::destroyScene()
{
}

void ProjectFarm::createFrameListener()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	UIMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
	mTimerInfo = UIMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 100);
	mScoreInfo = UIMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "TInfo1", "", 200);
	mBulletInfo = UIMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "TInfo2", "", 100);
	//mEndGame = UIMgr->createLabel(OgreBites::TL_CENTER, "End", "", 400);
	//mEndGame->hide();
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
	
	mInputContext.mKeyboard = mKeyboard;
	mInputContext.mMouse = mMouse;
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
			
			//MessageBox(
			//NULL,
			//e.getFullDescription().c_str(),
			//"An exception has occured!",
			//MB_OK | MB_ICONERROR | MB_TASKMODAL);
			
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
