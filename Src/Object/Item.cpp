#include<DxLib.h>
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Utility/AsoUtility.h"
#include "Item.h"

Item::Item(VECTOR& _pos)
{
	trans_ = Transform();
	trans_.pos = _pos;
	trans_.localPos = VAdd(trans_.pos, MODEL_POS);
	radius_ = 0.0f;
	speed_ = 0.0f;
}

void Item::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//変数の初期化
	trans_.SetModel(res.LoadModelDuplicate(
		ResourceManager::SRC::GEM));
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);
	trans_.scl = SCALE;
	radius_ = RADIUS;
	speed_ = 0.0f;

	//モデル制御
	trans_.Update();
}

void Item::Update(void)
{
	//モデル制御
	trans_.Update();
}

void Item::Draw(void)
{
#ifdef DEBUG_ITEM
	
	//デバッグ
	//DrawDebug();

#endif // DEBUG_ITEM

	//モデル描画
	MV1DrawModel(trans_.modelId);
}

void Item::DrawDebug(void)
{
	//デバッグ
	DrawSphere3D(trans_.pos, radius_, 100.0f, 0xffff00, 0xffff00, true);
	DrawFormatString(0, 16, 0xffffff, "item(%.2f,%.2f,%.2f)", trans_.pos.x, trans_.pos.y, trans_.pos.z);
}

void Item::Release(void)
{
}
