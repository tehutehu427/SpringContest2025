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
	//変数の初期化
	trans_ = Transform();
	//trans_.modelId = 
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);

	//モデル制御
	trans_.Update();
}

void Stage::Update(void)
{
	//モデル制御
	trans_.Update();
}

void Stage::Draw(void)
{
	//モデル描画
	MV1DrawModel(trans_.modelId);
}

void Stage::Release(void)
{
}
