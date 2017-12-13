#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#define NUM_ANIMS 13
#define ANIM_FADE_SPEED 7.5f

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

	bool mFadingIn[NUM_ANIMS];
	bool mFadingOut[NUM_ANIMS];

	std::list<Bullet*> myBullet;

	std::stringstream bulletsName;

	Entity* mPlayerEnt;
	SceneNode* mPlayerNode;

	Real score;
	Real bulletCount;

	bool _mIsColliside;

	SceneNode* mCameraNode;
	SceneNode* mPitchNode;

	Vector3 movement;
	Vector3 direction;
	Vector3 mKeyDirection;

	AxisAlignedBoxSceneQuery *AABBQuery;
	SceneQueryResult result;

public:
	PlayerManager(SceneManager* mSceneMgr, Camera *mCamera);
	void AnimationSetup();
	void PlayerRotation(Camera *mCamera, const OIS::MouseEvent& me);
	void PlayerTranslation(const OIS::KeyEvent& ke);
	void ReleasedKey(const OIS::KeyEvent& ke);
	void UpdatePosition(const Ogre::FrameEvent& fe);
	void AttackAnimation(const Ogre::FrameEvent& fe);
	void fadeAnimations(Real deltaTime);
	void BulletShooting(SceneManager* mSceneMgr);
	void BulletMove(const Ogre::FrameEvent& fe, SceneManager* mSceneMgr);
	void checkcollision(SceneManager* mSceneMgr, std::vector<Enemy*> enemys);
	void UIUpdate(Real *pScore, Real *pBulletNum);
	Real getScore();
	Real getBulletNum();
};