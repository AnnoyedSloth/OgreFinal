#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "SdkTrays.h"

class ProjectFarm : public WindowEventListener, public FrameListener, public OgreBites::SdkTrayListener, public OIS::KeyListener, public OIS::MouseListener {

private:
	bool mShutdown;
	Root* mRoot;
	String mResourcesCfg;
	String mPluginsCfg;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
	SceneManager* mFirstScene;
	Camera* mCamera;

	SceneSetter* mSceneSetter;
	PlayerManager* mPlayer;
	Wolf* myWolf;

	//CharacterController* player;
	SdkTrayListener* mTrayMgr;

	Vector3 mKeyDirection;
	Vector3 direction;

	OIS::InputManager* mInputMgr;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

protected:
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
	virtual void createViewports(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool setup();
	virtual void setupViewport(SceneManager *curr);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual void createScene(void);
	virtual void destroyScene(void);
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
public:
	ProjectFarm();
	virtual ~ProjectFarm();

	void go();
};