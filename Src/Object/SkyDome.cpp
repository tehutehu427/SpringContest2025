#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "Common/Transform.h"
#include "SkyDome.h"

SkyDome::SkyDome(const Transform& syncTransform) : syncTransform_(syncTransform)
{

	state_ = STATE::NONE;
	
	// 状態管理
	stateChanges_.emplace(STATE::NONE, std::bind(&SkyDome::ChangeStateNone, this));
	stateChanges_.emplace(STATE::STAY, std::bind(&SkyDome::ChangeStateStay, this));
	stateChanges_.emplace(STATE::FOLLOW, std::bind(&SkyDome::ChangeStateFollow, this));

}

SkyDome::~SkyDome(void)
{
}

void SkyDome::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	auto& scn = SceneManager::GetInstance();

	// モデル制御の基本情報
	trans_.SetModel(
		res.LoadModelDuplicate(
			ResourceManager::SRC::SKY_DOME));
	trans_.scl = SCALES;
	trans_.pos = AsoUtility::VECTOR_ZERO;
	trans_.quaRot = Quaternion::Euler(
		0.0f, 
		AsoUtility::Deg2RadF(180.0f),
		0.0f
	);
	trans_.quaRotLocal = Quaternion();
	trans_.Update();

	// Zバッファ無効(突き抜け対策)
	MV1SetUseZBuffer(trans_.modelId, false);
	MV1SetWriteZBuffer(trans_.modelId, false);

	// 状態遷移
	auto sceneId = scn.GetSceneID();
	if(sceneId == SceneManager::SCENE_ID::TITLE)
	{
		ChangeState(STATE::STAY);
	}
	else
	{
		ChangeState(STATE::FOLLOW);
	}

}

void SkyDome::Update(void)
{

	// 更新ステップ
	stateUpdate_();

}

void SkyDome::Draw(void)
{
	MV1DrawModel(trans_.modelId);
}

void SkyDome::Release(void)
{
}

void SkyDome::ChangeState(STATE state)
{

	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();

}

void SkyDome::ChangeStateNone(void)
{
	stateUpdate_ = std::bind(&SkyDome::UpdateNone, this);
}

void SkyDome::ChangeStateStay(void)
{
	stateUpdate_ = std::bind(&SkyDome::UpdateStay, this);
}

void SkyDome::ChangeStateFollow(void)
{
	stateUpdate_ = std::bind(&SkyDome::UpdateFollow, this);
	trans_.pos = syncTransform_.pos;
	trans_.Update();
}

void SkyDome::UpdateNone(void)
{
}

void SkyDome::UpdateStay(void)
{
}

void SkyDome::UpdateFollow(void)
{
	trans_.pos = syncTransform_.pos;
	trans_.Update();
}
