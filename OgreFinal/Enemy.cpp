#pragma once
#include"stdafx.h"
#include"Enemy.h"

Enemy::Enemy(SceneManager* mSceneMgr, Vector3 pos, String EnemyName) 
{

	mEnemyEnt = mSceneMgr->createEntity(EnemyName, "Ninja.mesh");
	mEnemyEnt->setCastShadows(true);

	initPos = pos;

	mEnemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * 300);
	mEnemyNode->setScale(.5, .5, .5);
	mEnemyNode->showBoundingBox(false);
	AxisAlignedBox box = mEnemyEnt->getBoundingBox();
	mEnemyNode->setPosition(pos.x, -box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y-15, pos.z);
	//mEnemyNode->pitch(Degree(-90));
	//mEnemyNode->roll(Degree(180));
	mEnemyNode->attachObject(mEnemyEnt);

	AnimationSetup();
}

void Enemy::AnimationSetup() {
	
	mAnimationState = mEnemyEnt->getAnimationState("Stealth"); mAnimationState->setLoop(true); mAnimationState->setEnabled(true);

}

void Enemy::EnemyTranslation(const FrameEvent& fe) {
	if (mEnemyNode->getPosition().z < -1500) GoingBack();
	mEnemyNode->translate(Vector3(0, 0, -1) * fe.timeSinceLastFrame * 100);
	position = mEnemyNode->getPosition();
	mAnimationState->addTime(fe.timeSinceLastFrame);
}

void Enemy::GoingBack() {
	mEnemyNode->setPosition(initPos);
}

Vector3 Enemy::getPos() {
	return position;
}