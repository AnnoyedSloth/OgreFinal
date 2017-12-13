#pragma once
#include"stdafx.h"
#include"Enemy.h"

Wolf::Wolf(SceneManager* mSceneMgr, Vector3 loc, String wolfName) 
{

	mWolfEnt = mSceneMgr->createEntity(wolfName, "Wolf.mesh");
	mWolfEnt->setCastShadows(true);


	mWolfNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * 300);
	mWolfNode->setScale(30, 30, 30);
	mWolfNode->showBoundingBox(true);
	AxisAlignedBox box = mWolfEnt->getBoundingBox();
	mWolfNode->setPosition(loc.x, -box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 32, loc.z);
	mWolfNode->pitch(Degree(-90));
	mWolfNode->attachObject(mWolfEnt);

	//AnimationSetup();
}

void Wolf::AnimationSetup() {

	//SkeletonPtr skel = SkeletonManager::getSingleton().load("Wolf.skeleton",		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME).staticCast<Skeleton>();

	String animNames[] = {"wolf_run_cycle"};

	if (animNames[0] == mAnims[0]->getAnimationName()) {
		mAnims[0]->setWeight(0);
	}

	//for (int i = 0; i < WOLF_ANIM_COUNT; i++)
	//{
	//	mAnims[i] = mWolfEnt->getAnimationState(animNames[i]);
	//	mAnims[i]->setLoop(true);
	//}
	mAnims[ANIM_RUN]->setLoop(true);
	mAnims[ANIM_RUN]->setEnabled(true);

}

void Wolf::WolfTranslation(const FrameEvent& fe) {

	mAnims[ANIM_RUN]->addTime(fe.timeSinceLastFrame);
}