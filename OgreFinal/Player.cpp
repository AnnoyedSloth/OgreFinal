#pragma once
#include"stdafx.h"
#include"Player.h"

PlayerManager::PlayerManager(SceneManager* mSceneMgr, Camera *mCamera) {
	//Player setup
	mPlayerEnt = mSceneMgr->createEntity("PlayerBody", "Sinbad.mesh");
	mPlayerEnt->setCastShadows(true);
	//mPlayerEnt->getBoundingRadius();
	mPlayerEnt->getWorldBoundingBox();
	
	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * 300);
	mPlayerNode->setScale(10, 10, 10);
	mPlayerNode->showBoundingBox(true);
	AxisAlignedBox box = mPlayerEnt->getBoundingBox();
	mPlayerNode->setPosition(0, -box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 32, -1000);
	mPlayerNode->attachObject(mPlayerEnt);

	//Camera setup
	mCameraNode = mPlayerNode->createChildSceneNode();
	//mCameraNode->attachObject(mPlayerNode);
	mCameraNode->setPosition(0, 5, -20);
	mCameraNode->yaw(Degree(180));
	mCameraNode->lookAt(mPlayerNode->getPosition(), Node::TS_WORLD);
	mPitchNode = mCameraNode->createChildSceneNode();
	mPitchNode->attachObject(mCamera);

	mKeyDirection = Vector3(0, 0, 0);
	direction = Vector3::ZERO;
	bulletCount = 30;


	AnimationSetup();
}

void PlayerManager::AnimationSetup() {
	mPlayerEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	String animNames[] =
	{ "IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
		"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd" };

	for (int i = 0; i < NUM_ANIMS; i++)
	{
		mAnims[i] = mPlayerEnt->getAnimationState(animNames[i]);
		mAnims[i]->setLoop(true);
	}

	// start off in the idle state (top and bottom together)
	mAnims[ANIM_IDLE_BASE]->setLoop(true);
	mAnims[ANIM_IDLE_BASE]->setEnabled(true);

	mAnims[ANIM_IDLE_TOP]->setLoop(true);
	mAnims[ANIM_IDLE_TOP]->setEnabled(true);

	// relax the hands since we're not holding anything
	mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);
}

void PlayerManager::PlayerRotation(Camera *mCamera, const OIS::MouseEvent& me) {
	//mCameraNode->yaw(Degree(-0.05f * me.state.X.rel), Node::TS_WORLD);
	mPlayerNode->yaw(Degree(-0.05f * me.state.X.rel), Node::TS_WORLD);
	mCamera->pitch(Degree(-0.05f * me.state.Y.rel));
}

void PlayerManager::PlayerTranslation(const OIS::KeyEvent& ke) {
	if (ke.key == OIS::KC_W) {
		mKeyDirection.z = 1;
	}
	if (ke.key == OIS::KC_S) {
		mKeyDirection.z = -1;
	}
	if (ke.key == OIS::KC_A) {
		mKeyDirection.x = 1;
	}
	if (ke.key == OIS::KC_D) {
		mKeyDirection.x = -1;
	}
}

void PlayerManager::ReleasedKey(const OIS::KeyEvent& ke) {
	if (ke.key == OIS::KC_W && mKeyDirection.z == 1.0f) {
		mKeyDirection.z = 0;
	}
	else if (ke.key == OIS::KC_S && mKeyDirection.z == -1.0f) {
		mKeyDirection.z = 0;
	}
	if (ke.key == OIS::KC_A && mKeyDirection.x == 1.0f) {
		mKeyDirection.x = 0;
	}
	else if (ke.key == OIS::KC_D  && mKeyDirection.x == -1.0f) {
		mKeyDirection.x = 0;
	}
}

void PlayerManager::UpdatePosition(const Ogre::FrameEvent& fe) {
	direction = Vector3::ZERO;
	if (mKeyDirection != Vector3::ZERO) {
		direction += mKeyDirection.z * mCameraNode->getOrientation().z;
		direction += mKeyDirection.x * mCameraNode->getOrientation().x;
		direction.y = 0;
		direction.normalise();
		mPlayerNode->translate(mKeyDirection.x * fe.timeSinceLastFrame * 100, 0, mKeyDirection.z * fe.timeSinceLastFrame * 100, Node::TS_LOCAL);

		mAnims[ANIM_RUN_BASE]->setLoop(true);
		mAnims[ANIM_RUN_BASE]->setEnabled(true);
		mAnims[ANIM_RUN_BASE]->addTime(fe.timeSinceLastFrame);

		//mAnims[ANIM_RUN_TOP]->setLoop(true);
		//mAnims[ANIM_RUN_TOP]->setEnabled(true);	
		//mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
		//mAnims[ANIM_RUN_TOP]->addTime(fe.timeSinceLastFrame);
	}
	else {
		mAnims[ANIM_RUN_BASE]->setEnabled(false);
		mAnims[ANIM_RUN_TOP]->setEnabled(false);

		mAnims[ANIM_IDLE_BASE]->setLoop(true);
		mAnims[ANIM_IDLE_BASE]->setEnabled(true);
		mAnims[ANIM_IDLE_TOP]->setLoop(true);
		mAnims[ANIM_IDLE_TOP]->setEnabled(true);
		mAnims[ANIM_IDLE_BASE]->addTime(fe.timeSinceLastFrame);
		mAnims[ANIM_IDLE_TOP]->addTime(fe.timeSinceLastFrame);
	}		   
}

void PlayerManager::UpdateCamera() {
	//mPitchNode->setPosition(mPlayerNode->getPosition() + Vector3::UNIT_Y * 2);
}

void PlayerManager::BulletShooting(SceneManager* mSceneMgr) {
	if (bulletCount > 0) {
		Vector3 bulletDirection = Vector3::ZERO;
		bulletDirection += mCameraNode->getOrientation().x;
		bulletDirection += mCameraNode->getOrientation().y;
		bulletDirection += mCameraNode->getOrientation().z;
		bulletDirection.normalise();
		bulletsName.str(std::string());
		bulletsName << "bulletName" << bulletCount;
		myBullet.push_back(new Bullet(mSceneMgr, mPlayerNode->getPosition(), bulletsName.str(), bulletDirection));
		bulletCount--;
	}
}

void PlayerManager::BulletMove(const Ogre::FrameEvent& fe) {
	if (myBullet.empty() == false) {
		for (auto it = myBullet.begin(); it != myBullet.end(); it++) {
			(*it)->BulletMove(fe);
		}
	}
}