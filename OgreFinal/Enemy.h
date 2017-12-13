#pragma once
#include "stdafx.h"

#define ENEMY_ANIM_COUNT 1

class Enemy 
{
	enum AnimID 
	{
		ANIM_WALK,
		ANIM_IDLE
	};

	AnimationState* mAnimationState;

	Entity* mEnemyEnt;
	SceneNode* mEnemyNode;

	Vector3 initPos;
	Vector3 position;
	Vector3 movement;
	Vector3 direction;

public:
	Enemy(SceneManager* mSceneMgr, Vector3 loc, String EnemyName);
	void AnimationSetup();
	void EnemyTranslation(const FrameEvent& fe);
	void GoingBack();
	Vector3 getPos();
};