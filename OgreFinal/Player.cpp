#pragma once
#include"stdafx.h"
#include"Player.h"

PlayerManager::PlayerManager(SceneManager* mSceneMgr, Camera *mCamera) {
	mPlayerEnt = mSceneMgr->createEntity("PlayerBody", "Sinbad.mesh");
	mPlayerEnt->setCastShadows(true);

	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * 300);
	mPlayerNode->setScale(10, 10, 10);
	mPlayerNode->showBoundingBox(true);
	AxisAlignedBox box = mPlayerEnt->getBoundingBox();
	mPlayerNode->setPosition(0, -box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 32, 0);
	mPlayerNode->attachObject(mPlayerEnt);

	mCameraNode = mPlayerNode->createChildSceneNode();
	//mCameraNode->attachObject(mPlayerNode);
	mCameraNode->setPosition(0, 5, -20);
	mCameraNode->yaw(Degree(180));
	mCameraNode->lookAt(mPlayerNode->getPosition(), Node::TS_WORLD);
	mPitchNode = mCameraNode->createChildSceneNode();
	mPitchNode->attachObject(mCamera);

	mKeyDirection = Vector3(0, 0, 0);
	direction = Vector3::ZERO;
}

void PlayerManager::PlayerRotation(Camera *mCamera, const OIS::MouseEvent& me) {
	//mCameraNode->yaw(Degree(-0.05f * me.state.X.rel), Node::TS_WORLD);
	mPlayerNode->yaw(Degree(-0.05f * me.state.X.rel), Node::TS_WORLD);
	mCamera->pitch(Degree(0.005f * me.state.Y.rel));
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
	}
}

void PlayerManager::UpdateCamera() {
	//mPitchNode->setPosition(mPlayerNode->getPosition() + Vector3::UNIT_Y * 2);
}