#include "stdafx.h"
#include "OgreNode.h"


class SceneSetter {
public:
	SceneSetter();
	void Setter(SceneManager *mSceneMgr);
	void GroundSetting(SceneManager *mSceneMgr);
	void ObjectSetting(SceneManager *mSceneMgr);
	void LightSetting(SceneManager *mSceneMgr);
	void ParticleSetting(SceneManager *mSceneMgr);
};