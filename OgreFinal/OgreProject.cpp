#include "stdafx.h"
#include "OgreProject.h"
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreColourValue.h>
#include <OgreResourceGroupManager.h>
#include <OgreVector3.h>
#include <OgreMeshManager.h>

TutorialApplication::TutorialApplication(void) :
	mRoot(0),
	mCamera(0),
	mSceneMgr(0),
	mWindow(0),
	mMouse(0),
	mKeyboard(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK)
{
	mKeyDirection = Vector3(0, 0, 0);
	isFPSMode = false;
}

TutorialApplication::~TutorialApplication(void)
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

bool TutorialApplication::configure(void)
{
	if (mRoot->showConfigDialog())
	{
		mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
		return true;
	}

	else
	{
		return false;
	}
}

void TutorialApplication::chooseSceneManager(void)
{
	// Get the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

}

void TutorialApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("MainCam");

	//mCamera->setPosition(0, 0, 80);
	//mCamera->lookAt(0, 0, -300);
	//mCamera->setNearClipDistance(5);

}

void TutorialApplication::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, true));


	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	// Set initial mouse clipping size 
	windowResized(mWindow);

	// Register as a Window listener 
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	// Register as a Frame listener 
	mRoot->addFrameListener(this);
}

void TutorialApplication::createViewports(void)
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void TutorialApplication::setupResources(void)
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

void TutorialApplication::createResourceListener(void)
{

}

void TutorialApplication::loadResources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


void TutorialApplication::go()
{
#ifdef _DEBUG 
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else 
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
	// The first parameter determines whether or not Ogre will create a RenderWindow for us. 

	if (!setup())
		return;

	mRoot->startRendering();

	destroyScene();
}

bool TutorialApplication::setup()
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	bool carryOn = configure();
	if (!carryOn) return false;

	chooseSceneManager();
	createCamera();
	createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	loadResources();

	createScene();

	createFrameListener();

	return true;
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if (mWindow->isClosed())
		return false;

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	mKeyboard->capture();
	mMouse->capture();

	update(fe);
//	if (isFPSMode) mCamera->translate(10*fe.timeSinceLastFrame * );

	return true;
}

void TutorialApplication::update(const FrameEvent& fe) {
	player->TranslatePosition(fe, mKeyDirection);
	if (!isFPSMode) {
		mCamera->setPosition(player->GetPosition().x, player->GetPosition().y + 100, player->GetPosition().z - 150);
		mFreeCameraLoc = Vector3(player->GetPosition().x, player->GetPosition().y + 50, player->GetPosition().z - 50);
	}
	else if(isFPSMode) {
		mCamera->setPosition(mFreeCameraLoc);
	}
}

void TutorialApplication::cameraRotate(Real deltaX, Real deltaY, Real deltaZ) {
	/*mCamera->yaw(Degree(deltaX));
	mCamera->pitch(Degree(deltaY));	*/
	player->TranslateRotation()
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke)
{
	if (ke.key == OIS::KC_F && isFPSMode == false) isFPSMode = true;
	else if(ke.key == OIS::KC_F && isFPSMode == true) isFPSMode = false;

	if (!isFPSMode) {
		if (ke.key == OIS::KC_W) {
			mKeyDirection.z = 1;
		}
		if (ke.key == OIS::KC_S) {
			mKeyDirection.z = -1;
		}
		if (ke.key == OIS::KC_A) {
			mKeyDirection.x = 1;
		}
		if (ke.key == OIS::KC_D) {
			mKeyDirection.x = -1;
		}
	}
	else {
		mFreeCameraLoc = Vector3(-3000, 1000, -3000);
		mCamera->lookAt(0, 0, 0);
	}
	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &ke)
{
	if (!isFPSMode) {
		if (ke.key == OIS::KC_W && mKeyDirection.z == 1.0f) {
			mKeyDirection.z = 0;
		}
		else if (ke.key == OIS::KC_S && mKeyDirection.z == -1.0f) {
			mKeyDirection.z = 0;
		}
		if (ke.key == OIS::KC_A && mKeyDirection.x == 1.0f) {
			mKeyDirection.x = 0;
		}
		else if (ke.key == OIS::KC_D  && mKeyDirection.x == -1.0f) {
			mKeyDirection.x = 0;
		}
	}
	return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent& me)
{
	cameraRotate(-0.05f * me.state.X.rel, -0.05f * me.state.Y.rel, -0.0005f * me.state.Z.rel);

	player->TranslateRotation(me);
	//if (!isFPSMode) player->TranslateRotation(-0.05f * me.state.X.rel);
	return true;
}

bool TutorialApplication::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}

bool TutorialApplication::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	return true;
}

void TutorialApplication::createScene(void)
{
	player = new CharacterController(mSceneMgr, mCamera);
	//player->Init(mSceneMgr, Vector3(0, 45, -1300));

	//Setup Skybox
	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 10000, false);

	//Setup camera & viewport
	//mCamera->setPosition(Ogre::Vector3(player->GetPosition().x, player->GetPosition().y + 50, player->GetPosition().z - 50));
	//mCamera->lookAt(Ogre::Vector3(player->GetPosition().x, player->GetPosition().y + 20, player->GetPosition().z + 50));
	//mCamera->setNearClipDistance(5);
	//mCamera->getParentNode(player->TranslatePosition);

	//Create a spot light
	Ogre::Light* light = mSceneMgr->createLight("DirectLight");
	Ogre::SceneNode* node = mSceneMgr->createSceneNode("DirectNode");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, -1));
	light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	node->setPosition(1000, 1000, -1500);
	node->attachObject(light);

	//Create a particle
	ParticleSystem* rainParticle = mSceneMgr->createParticleSystem("Rain", "Examples/Rain");
	SceneNode* rainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RainParticle");
	rainNode->setPosition(0, 1000, 0);
	rainNode->attachObject(rainParticle);

	//Create plane
	Ogre::Plane plane(Vector3::UNIT_Y, -10);
	Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 5000, 5000, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/GrassFloor");

	Entity* fence1 = mSceneMgr->createEntity("fence1", "WoodPallet.mesh");
	fence1->setMaterialName("WoodPallet");
	SceneNode* fence1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence1");
	fence1Node->scale(10.0f, 60.0f, 200.0f);
	fence1Node->setPosition(300, 30, -1500);
	fence1Node->roll(Degree(90));
	fence1Node->attachObject(fence1);

	Entity* fence2 = mSceneMgr->createEntity("fence2", "WoodPallet.mesh");
	fence2->setMaterialName("WoodPallet");
	SceneNode* fence2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence2");
	fence2Node->scale(10.0f, 60.0f, 200.0f);
	fence2Node->setPosition(-300, 30, -1500);
	fence2Node->roll(Degree(-90));
	fence2Node->attachObject(fence2);

	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	//Create Environmental Objects
	Ogre::Entity* tudorEntity = mSceneMgr->createEntity("tudorhouse.mesh");
	Ogre::SceneNode* tudorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("tudorNode");
	tudorNode->setPosition(0, 530, -2000);
	tudorNode->attachObject(tudorEntity);
}

void TutorialApplication::destroyScene(void)
{

}

void TutorialApplication::windowResized(Ogre::RenderWindow* rw)
{
	int left, top;
	unsigned int width, height, depth;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void TutorialApplication::windowClosed(Ogre::RenderWindow* rw)
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
		TutorialApplication app;

		try
		{
			app.go();
		}

		catch (Ogre::Exception& e)
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
			MessageBox(
				NULL,
				e.getFullDescription().c_str(),
				"An exception has occured!",
				MB_OK | MB_ICONERROR | MB_TASKMODAL);
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