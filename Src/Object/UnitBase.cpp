#include"../Application.h"
#include "UnitBase.h"

UnitBase::UnitBase()
{
	trans_.modelId = -1;
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.scl = { 0.0f,0.0f,0.0f };
	trans_.rot = { 0.0f,0.0f,0.0f };

	anim_ = ANIM::NONE;
	atcAnim_ = -1;
	animTotalTime_ = -1;
	stepAnim_ = -1.0f;
	speedAnim_ = 1.0f;
}

UnitBase::~UnitBase()
{
}

void UnitBase::ResetAnim(const ANIM _anim, const float _speed)
{
	
}

void UnitBase::Anim(void)
{
	// アニメーション再生
	// 経過時間の取得
	float deltaTime = 1.0f / Application::DEFAULT_FPS;
	// アニメーション時間の進行
	stepAnim_ += (speedAnim_ * deltaTime);
	if (stepAnim_ > animTotalTime_)
	{
		//アニメーション終了時処理（継承先で行動を決めておく）
		FinishAnim();
	}
	// 再生するアニメーション時間の設定
	MV1SetAttachAnimTime(trans_.modelId, atcAnim_, stepAnim_);
}

void UnitBase::FinishAnim(void)
{
	//ループ再生
	stepAnim_ = 0.0f;
}
