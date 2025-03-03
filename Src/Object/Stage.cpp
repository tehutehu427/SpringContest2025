#include<DxLib.h>
#include"../Utility/AsoUtility.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
	//•Ï”‚Ì‰Šú‰»
	trans_ = Transform();
	//trans_.modelId = 
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);

	//ƒ‚ƒfƒ‹§Œä
	trans_.Update();
}

void Stage::Update(void)
{
	//ƒ‚ƒfƒ‹§Œä
	trans_.Update();
}

void Stage::Draw(void)
{
	//ƒ‚ƒfƒ‹•`‰æ
	MV1DrawModel(trans_.modelId);
}

void Stage::Release(void)
{
}
