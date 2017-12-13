#pragma once
#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(SceneManager* mSceneMgr, Vector3 loc, std::string bulletName) {
	bulletEnt = mSceneMgr->createParticleSystem(bulletName, "Examples/GreenyNimbus");
	bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(bulletName + "p");
	bulletNode->attachObject(bulletEnt);
	bulletNode->setPosition(loc);
	direction = Vector3(0,0,1);
	isGoing = true;

	//AABBQuery = mSceneMgr->createAABBQuery(r);
}

void Bullet::BulletMove(const Ogre::FrameEvent& fe, SceneManager* mSceneMgr) {
	bulletNode->translate(direction * fe.timeSinceLastFrame * 1000);
	position = bulletNode->getPosition();
	if (bulletNode->getPosition().z > 1500) {
	//	direction = Vector3(0, -1, 0);
	//	isGoing = false;
	//	bulletNode->detachObject(bulletEnt);
	//	mSceneMgr->destroySceneNode(bulletNode);
	//	mSceneMgr->destroyParticleSystem(bulletEnt);
	}
}

bool Bullet::getIsGoing() {
	return isGoing;
}

Vector3 Bullet::getPos() {
	return position;
}

void Bullet::DirectionToBottom() {
	direction = Vector3(0, -1, 0);
}

//void Bullet::Destroy(SceneManager* mSceneMgr) {
//	bulletNode->detachObject(bulletEnt);
//	mSceneMgr->destroySceneNode(bulletNode);
//	mSceneMgr->destroyParticleSystem(bulletEnt);
//}