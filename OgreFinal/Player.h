#include "stdafx.h"
#include "Bullet.h"

#define NUM_ANIMS 13

class PlayerManager {

	enum AnimID
	{
		ANIM_IDLE_BASE,
		ANIM_IDLE_TOP,
		ANIM_RUN_BASE,
		ANIM_RUN_TOP,
		ANIM_HANDS_CLOSED,
		ANIM_HANDS_RELAXED,
		ANIM_DRAW_SWORDS,
		ANIM_SLICE_VERTICAL,
		ANIM_SLICE_HORIZONTAL,
		ANIM_DANCE,
		ANIM_JUMP_START,
		ANIM_JUMP_LOOP,
		ANIM_JUMP_END,
		ANIM_NONE
	};

	AnimationState* mAnims[NUM_ANIMS];

	std::list<Bullet*> myBullet;

	int bulletCount;
	std::stringstream bulletsName;

	Entity* mPlayerEnt;
	SceneNode* mPlayerNode;

	SceneNode* mCameraNode;
	SceneNode* mPitchNode;

	Vector3 movement;
	Vector3 direction;
	Vector3 mKeyDirection;

public:
	PlayerManager(SceneManager* mSceneMgr, Camera *mCamera);
	void AnimationSetup();
	void PlayerRotation(Camera *mCamera, const OIS::MouseEvent& me);
	void PlayerTranslation(const OIS::KeyEvent& ke);
	void ReleasedKey(const OIS::KeyEvent& ke);
	void UpdatePosition(const Ogre::FrameEvent& fe);
	void UpdateCamera();

	void BulletShooting(SceneManager* mSceneMgr);
	void BulletMove(const Ogre::FrameEvent& fe);
};