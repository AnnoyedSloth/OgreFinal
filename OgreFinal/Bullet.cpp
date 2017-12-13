#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(SceneManager* mSceneMgr, Vector3 loc, std::string bulletName, Vector3 dir) {

	bulletEnt = mSceneMgr->createParticleSystem(bulletName, "Examples/GreenyNimbus");
	bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(bulletName + "p");
	bulletNode->attachObject(bulletEnt);
	bulletNode->setPosition(loc);
	direction = dir;
}

void Bullet::BulletMove(const Ogre::FrameEvent& fe) {
	bulletNode->translate(-direction.x * fe.timeSinceLastFrame, 0, direction.z * fe.timeSinceLastFrame * 1000, Node::TS_LOCAL);
}