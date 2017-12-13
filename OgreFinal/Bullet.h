#pragma once
#include "stdafx.h"

class Bullet 
{
	int damage;
	Vector3 direction;
	Vector3 position;
	Real lifeTime;
	bool isGoing;

	ParticleSystem* bulletEnt;
	SceneNode* bulletNode;

	RaySceneQuery *mRaySceneQuery;
	AxisAlignedBoxSceneQuery *AABBQuery;

public:
	Bullet(SceneManager* mSceneMgr, Vector3 loc, std::string bulletName);
	void BulletMove(const Ogre::FrameEvent& fe, SceneManager* mSceneMgr);
	Vector3 getPos();
	void Destroy(SceneManager* mSceneMgr);
	bool getIsGoing();
	void DirectionToBottom();
};