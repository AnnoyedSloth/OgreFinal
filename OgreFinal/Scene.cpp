#pragma once
#include"stdafx.h"
#include"Scene.h"
#include"Enemy.h"

SceneSetter::SceneSetter() {
}

void SceneSetter::Setter(SceneManager *mSceneMgr)
{

}

void SceneSetter::GroundSetting(SceneManager *mSceneMgr)
{
	mSceneMgr->setSkyBox(true, "Examples/StormySkyBox", 10000, false);

	Plane plane(Vector3::UNIT_Y, -10);
	MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 3000, 3000, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
	Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	ent->setCastShadows(false);
	ent->getCastShadows();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/GrassFloor");
}
void SceneSetter::ObjectSetting(SceneManager *mSceneMgr)
{
	//Entity* fence1 = mSceneMgr->createEntity("fence1", "WoodPallet.mesh");
	//fence1->setMaterialName("WoodPallet");
	////fence1->getBoundingRadius();
	//fence1->getWorldBoundingBox();
	//SceneNode* fence1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence1");
	//fence1Node->showBoundingBox(true);
	//AxisAlignedBox fence1Box = fence1->getBoundingBox();
	//fence1Node->scale(10.0f, 60.0f, 200.0f);
	//fence1Node->setPosition(300, -fence1Box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 30, -1500);
	//fence1Node->roll(Degree(90));
	//fence1Node->attachObject(fence1);

	//Entity* fence2 = mSceneMgr->createEntity("fence2", "WoodPallet.mesh");
	//fence2->setMaterialName("WoodPallet");
	//fence2->getBoundingRadius();
	//SceneNode* fence2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("fence2");
	//fence2Node->showBoundingBox(true);
	//AxisAlignedBox fence2Box = fence2->getBoundingBox();
	//fence2Node->scale(10.0f, 60.0f, 200.0f);
	//fence2Node->setPosition(-300, -fence2Box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y + 30, -1500);
	//fence2Node->roll(Degree(-90));
	//fence2Node->attachObject(fence2);

	std::stringstream FenceNodeName;
	AxisAlignedBox fenceBox[12];

	for (int a = 0; a < 6; a++) {
		FenceNodeName.str(std::string());
		FenceNodeName << "FenceNode" << a;
		fenceEnt.push_back(mSceneMgr->createEntity("fence.mesh"));
		fenceNode.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode(FenceNodeName.str()));
		fenceEnt[a]->setMaterialName("fence");
		fenceEnt[a]->setCastShadows(true);
		fenceEnt[a]->getBoundingBox();
		fenceBox[a] = fenceEnt[a]->getBoundingBox();
		fenceNode[a]->showBoundingBox(true);
		fenceNode[a]->setScale(30, 30, 30);
		fenceNode[a]->setPosition(300, -fenceBox[a].getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y - 30, -1200 + a*150);
		fenceNode[a]->pitch(Degree(-90));
		fenceNode[a]->attachObject(fenceEnt[a]);
	}

	for (int a = 6; a < 12; a++) {
		FenceNodeName.str(std::string());
		FenceNodeName << "FenceNode" << a;
		fenceEnt.push_back(mSceneMgr->createEntity("fence.mesh"));
		fenceNode.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode(FenceNodeName.str()));
		fenceEnt[a]->setMaterialName("fence");
		fenceEnt[a]->setCastShadows(true);
		fenceNode[a]->setScale(30, 30, 30);
		fenceNode[a]->setPosition(-300, -30, -2100 + a * 150);
		fenceNode[a]->pitch(Degree(-90));
		fenceNode[a]->attachObject(fenceEnt[a]);
	}

	Ogre::Entity* tudorEntity = mSceneMgr->createEntity("tudorhouse.mesh");
	Ogre::SceneNode* tudorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("tudorNode");
	tudorNode->setPosition(600, 530, -1000);
	tudorNode->attachObject(tudorEntity);

	std::vector<Entity*> treeEnt;
	std::vector<Entity*> treeLeaf;
	std::vector<SceneNode*> treeNode;
	std::vector<SceneNode*> leafNode;
	std::vector<Vector3> location;

	location.push_back(Vector3(-800, -10, -1000));
	location.push_back(Vector3(-900, -10, -800));
	location.push_back(Vector3(-700, -10, -900));
	location.push_back(Vector3(-800, -10, -800));
	location.push_back(Vector3(-900, -10, -700));
	location.push_back(Vector3(-650, -10, -500));
	location.push_back(Vector3(-1000, -10, -700));
	location.push_back(Vector3(-1100, -10, -600));
	location.push_back(Vector3(-1100, -10, -700));
	location.push_back(Vector3(-100, -10, 1000));
	location.push_back(Vector3(-200, -10, 1100));
	location.push_back(Vector3(-300, -10, 900));
	location.push_back(Vector3(-400, -10, 800));
	location.push_back(Vector3(-150, -10, 1200));
	location.push_back(Vector3(-250, -10, 900));
	location.push_back(Vector3(-350, -10, 800));
	location.push_back(Vector3(-450, -10, 1200));
	location.push_back(Vector3(-00, -10, -1200));
	location.push_back(Vector3(-50, -10, -1200));
	location.push_back(Vector3(100, -10, -1200));
	location.push_back(Vector3(150, -10, -1200));
	location.push_back(Vector3(250, -10, -1200));
	location.push_back(Vector3(300, -10, -1200));
	location.push_back(Vector3(350, -10, -1200));
	location.push_back(Vector3(270, -10, -1200));
	location.push_back(Vector3(180, -10, -1200));
	location.push_back(Vector3(00, -10, -1200));

	std::stringstream TreeNodeName;
	std::stringstream LeafNodeName;

	for (int a = 0; a < location.size(); a++) {
		TreeNodeName.str(std::string());
		LeafNodeName.str(std::string());
		TreeNodeName << "TreeNode" << a;
		LeafNodeName << "LeafNode" << a;
		treeEnt.push_back(mSceneMgr->createEntity("Tree.mesh"));
		treeLeaf.push_back(mSceneMgr->createEntity("LowPolyTree.mesh"));

		treeNode.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode(TreeNodeName.str()));
		leafNode.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode(LeafNodeName.str()));

		treeEnt[a]->setMaterialName("Tree_Bark");
		treeEnt[a]->setCastShadows(true);
		treeLeaf[a]->setMaterialName("Tree_Leaf");
		treeLeaf[a]->setCastShadows(true);
		treeNode[a]->setScale(50, 30, 50);
		treeNode[a]->setPosition(location[a]);
		treeNode[a]->pitch(Degree(-90));
		treeNode[a]->attachObject(treeEnt[a]);
		//treeNode[a]->attachObject(treeLeaf[a]);
		leafNode[a]->pitch(Degree(-90));
		leafNode[a]->setScale(100, 70, 100);
		leafNode[a]->setPosition(Vector3(location[a].x, location[a].y + 100, location[a].z));
		leafNode[a]->attachObject(treeLeaf[a]);
		//treeNode[a]->attachObject(treeLeaf[a]);
	}
}

void SceneSetter::LightSetting(SceneManager *mSceneMgr)
{
	//Ogre::Light* light = mSceneMgr->createLight("DirectLight");
	//Ogre::SceneNode* node = mSceneMgr->createSceneNode("DirectNode");
	//light->setType(Ogre::Light::LT_DIRECTIONAL);
	//light->setDirection(Ogre::Vector3(1, -1, 1));
	//light->setDiffuseColour(Ogre::ColourValue(.1f, .1f, .1f));
	//node->setPosition(1000, 1000, -1500);
	//node->attachObject(light);

	//Ogre::Light* point1 = mSceneMgr->createLight("PointLight1");
	////Ogre::SceneNode* point1Node = mSceneMgr->createSceneNode("PointNode1");
	//point1->setType(Ogre::Light::LT_SPOTLIGHT);
	////point1->setDirection(Ogre::Vector3(0, -1, 1));
	//point1->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
	//point1->setPosition(600, 500, -800);
	////point1Node->setPosition(1200, 20, -1200);
	////point1Node->attachObject(point1);

	Ogre::SceneNode* mainNode = mSceneMgr->createSceneNode("Node1");
	mSceneMgr->getRootSceneNode()->addChild(mainNode);


	// //Create the first point light
	//Light* light1 = mSceneMgr->createLight("Light1");
	//light1->setType(Ogre::Light::LT_SPOTLIGHT);
	//light1->setPosition(600, 20, -300);
	//light1->setDiffuseColour(0.255, 0.253, 0.210);
	//light1->setDirection(0, -1, 0);

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	light->setDirection(Ogre::Vector3(0, -1, 0));
	light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	Ogre::SceneNode* node2 = mainNode->createChildSceneNode("node2");
	node2->setPosition(0, 800, 0); node2->attachObject(light);
	//Ogre::Entity* lightEnt = mSceneMgr->createEntity("MyEntity", "sphere.mesh");
	//Ogre::SceneNode* node3 = node2->createChildSceneNode("node3");
	//node3->setScale(0.1f, 0.1f, 0.1f); node3->attachObject(lightEnt);



	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	mSceneMgr->setShadowColour(ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
}

void SceneSetter::ParticleSetting(SceneManager *mSceneMgr) {
	ParticleSystem* rainParticle = mSceneMgr->createParticleSystem("Rain", "Examples/Rain");
	SceneNode* rainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RainParticle");
	rainNode->setPosition(0, 1000, 0);
	rainNode->attachObject(rainParticle);
}