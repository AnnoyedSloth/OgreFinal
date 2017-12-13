#include "stdafx.h"

#define WOLF_ANIM_COUNT 1

class Wolf 
{
	enum AnimID 
	{
		ANIM_RUN
	};

	AnimationState* mAnims[WOLF_ANIM_COUNT];

	Entity* mWolfEnt;
	SceneNode* mWolfNode;

	Vector3 movement;
	Vector3 direction;

public:
	Wolf(SceneManager* mSceneMgr, Vector3 loc, String wolfName);
	void AnimationSetup();
	void WolfTranslation(const FrameEvent& fe);
};