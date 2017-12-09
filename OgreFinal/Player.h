#include "stdafx.h"

class PlayerManager {

	Entity* mPlayerEnt;
	SceneNode* mPlayerNode;

	SceneNode* mCameraNode;
	SceneNode* mPitchNode;

	Vector3 movement;
	Vector3 direction;
	Vector3 mKeyDirection;

public:
	PlayerManager(SceneManager* mSceneMgr, Camera *mCamera);
	void PlayerRotation(Camera *mCamera, const OIS::MouseEvent& me);
	void PlayerTranslation(const OIS::KeyEvent& ke);
	void ReleasedKey(const OIS::KeyEvent& ke);
	void UpdatePosition(const Ogre::FrameEvent& fe);
	void UpdateCamera();
};