#include "stdafx.h"

class Bullet 
{
	int damage;
	Vector3 location;
	Vector3 direction;
	Real lifeTime;

	ParticleSystem* bulletEnt;
	SceneNode* bulletNode;

public:
	Bullet(SceneManager* mSceneMgr, Vector3 loc, std::string bulletName, Vector3 direction);
	void BulletMove(const Ogre::FrameEvent& fe);
};