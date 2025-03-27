#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Manager/ItemManager.h"
#include"Stage.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng), stage_(_stage)
{

}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//枠
	mapFrameImg_ = res.Load(ResourceManager::SRC::MAP_FRAME).handleId_;
	//枠内
	mapGroundImg_ = res.Load(ResourceManager::SRC::MAP_GROUND).handleId_;
	//マップ
	mapImg_ = res.Load(ResourceManager::SRC::MAP_IMAGE).handleId_;
	//プレイヤー
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//枠内の描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapGroundImg_,true);

	//マップ画像
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapImg_,true);

	//プレイヤー描画
	DrawPlayer();
	
	//枠の描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}

const VECTOR MiniMap::GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const
{
	//相対距離
	VECTOR ret;
	//方向ベクトル
	VECTOR dir;
	//距離
	float distance;
	//マップ半径
	float radius = MAP_SIZE / 2;

	//方向
	dir = GetMoveVec(_startObj, _goalObj);

	//距離
	distance = CalcDistance(_startObj, _goalObj);

	//マップに合わせて縮小
	distance *= MAP_EX_RATE;

	//座標計算
	ret = VScale(dir, distance);

	return ret;
}

void MiniMap::DrawPlayer(void)
{
	//プレイヤーの角度(Y軸)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//プレイヤーからの相対座標計算
	VECTOR distance = GetDistance(player_->GetPos(), stage_->GetPos());

	//プレイヤーの描画
	DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
	for (auto& enemy : eneMng_)
	{

	}
}

void MiniMap::DrawItem(void)
{
}

void MiniMap::DrawVision(void)
{
}

const VECTOR MiniMap::GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed)const
{
	//標的への方向ベクトルを取得
	VECTOR targetVec = VSub(_goal, _start);

	//正規化
	targetVec = VNorm(targetVec);

	//Y座標は必要ないので要素を消す
	targetVec = { targetVec.x,0.0f,targetVec.z };

	//移動量を求める
	VECTOR ret = VScale(targetVec, _speed);

	return ret;
}

const float MiniMap::CalcDistance(const VECTOR _start, const VECTOR _goal)const
{
	VECTOR ret;

	ret.x = powf(_goal.x - _start.x, 2);
	ret.y = powf(_goal.y - _start.y, 2);
	ret.z = powf(_goal.z - _start.z, 2);

	return sqrtf(ret.x + ret.y + ret.z);
}
