#pragma once
#include"stdafx.h"
#include"Scene.h"

SceneSetter::SceneSetter() {
}

void SceneSetter::Setter(SceneManager *mSceneMgr)
{

}

void SceneSetter::GroundSetting(SceneManager *mSceneMgr)
{
	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 10000, false);

	Plane plane(Vector3::UNIT_Y, -10);
	MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 5000, 5000, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
	Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/GrassFloor");
}
void SceneSetter::ObjectSetting(SceneManager *mSceneMgr)
{
	Entity* fence1 = mSceneMgr->createEntity("fence1", "WoodPallet.mesh");
	fence1->setMaterialName("WoodPallet");
	SceneNode* fence1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence1");
	fence1Node->showBoundingBox(true);
	AxisAlignedBox fence1Box = fence1->getBoundingBox();
	fence1Node->scale(10.0f, 60.0f, 200.0f);
	fence1Node->setPosition(300, -fence1Box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 30, -1500);
	fence1Node->roll(Degree(90));
	fence1Node->attachObject(fence1);

	Entity* fence2 = mSceneMgr->createEntity("fence2", "WoodPallet.mesh");
	fence2->setMaterialName("WoodPallet");
	SceneNode* fence2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence2");
	fence2Node->showBoundingBox(true);
	AxisAlignedBox fence2Box = fence2->getBoundingBox();
	fence2Node->scale(10.0f, 60.0f, 200.0f);
	fence2Node->setPosition(-300, -fence2Box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 30, -1500);
	fence2Node->roll(Degree(-90));
	fence2Node->attachObject(fence2);

	Ogre::Entity* tudorEntity = mSceneMgr->createEntity("tudorhouse.mesh");
	Ogre::SceneNode* tudorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("tudorNode");
	tudorNode->setPosition(0, 530, -2000);
	tudorNode->attachObject(tudorEntity);
}

void SceneSetter::LightSetting(SceneManager *mSceneMgr)
{
	Ogre::Light* light = mSceneMgr->createLight("DirectLight");
	Ogre::SceneNode* node = mSceneMgr->createSceneNode("DirectNode");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, -1));
	light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	node->setPosition(1000, 1000, -1500);
	node->attachObject(light);

	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void SceneSetter::ParticleSetting(SceneManager *mSceneMgr) {
	ParticleSystem* rainParticle = mSceneMgr->createParticleSystem("Rain", "Examples/Rain");
	SceneNode* rainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RainParticle");
	rainNode->setPosition(0, 1000, 0);
	rainNode->attachObject(rainParticle);
}