#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Enemy.h"
#include"Manager/ItemManager.h"
#include"Item.h"
#include"Stage.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng), stage_(_stage)
{
	//maskScreen_ = -1;

	mapFrameImg_ = -1;
	mapGroundImg_ = -1;
	mapImg_ = -1;
	mapPlayerImg_ = -1;
	mapEnemyImg_ = -1;
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//スクリーン作成
	//maskScreen_ = MakeScreen(MAP_SIZE, MAP_SIZE, TRUE);

	//マスク用としてハンドルセット
	//SetMaskScreenGraph(maskScreen_);

	//マスク画面の作成
	CreateMaskScreen();

	//画像ハンドル
	//------------------------------------

	//枠
	mapFrameImg_ = res.Load(ResourceManager::SRC::MAP_FRAME).handleId_;
	//枠内
	mapGroundImg_ = res.Load(ResourceManager::SRC::MAP_GROUND).handleId_;
	//マスク
	mapMaskImg_ = res.Load(ResourceManager::SRC::MAP_MASK).handleId_;
	//マップ
	mapImg_ = res.Load(ResourceManager::SRC::MAP_IMAGE).handleId_;
	//プレイヤー
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
	//敵
	mapEnemyImg_ = res.Load(ResourceManager::SRC::MAP_ENEMY).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//マスク用にスクリーンを変更
	//SetDrawScreen(maskScreen_);

	//マスク画像クリア
	//ClearDrawScreen();

	//枠内の描画
	DrawMask(MAP_POS_X - MAP_SIZE+5, MAP_POS_Y - MAP_SIZE+5, mapMaskImg_, DX_MASKTRANS_NONE);

	//描画先を裏画面に変更
	//SetDrawScreen(DX_SCREEN_BACK);
	
	//マスクを有効にする
	SetUseMaskScreenFlag(TRUE);

	//枠内画像
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapGroundImg_, true);

	//マップ画像
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapImg_, true);

	//プレイヤー描画
	DrawPlayer();

	//敵の描画
	DrawEnemy();

	//アイテムの描画
	DrawItem();

	//マスクを無効にする
	SetUseMaskScreenFlag(FALSE);

	//枠の描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
	//マスクスクリーンを削除
	DeleteMaskScreen();
}

const VECTOR MiniMap::GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const
{
	//相対距離
	VECTOR ret;
	//方向ベクトル
	VECTOR dir;
	//距離
	float distance;

	//方向
	dir = GetMoveVec(_startObj, _goalObj);

	//距離
	distance = CalcDistance(_startObj, _goalObj);

	//マップに合わせて縮小
	distance *= MAP_RELATIVE_EX_RATE;

	//座標計算
	ret = VScale(dir, distance);

	return ret;
}

void MiniMap::DrawPlayer(void)
{
	//プレイヤーの角度(Y軸)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//ステージからの相対座標計算
	VECTOR distance = GetDistance(player_->GetPos(), stage_->GetPos());

	//プレイヤーの描画
	DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
	for (auto& enemy : eneMng_->GetEnemys())
	{
		//敵の角度(Y軸)
		double enemyAngle = enemy.get()->GetTransform().quaRot.ToEuler().y;

		//ステージからの相対座標計算
		VECTOR distance = GetDistance(enemy.get()->GetPos(), stage_->GetPos());

		//プレイヤーの描画
		DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, enemyAngle, mapEnemyImg_, true);
	}
}

void MiniMap::DrawItem(void)
{
	//ステージからの相対座標計算
	VECTOR distance = GetDistance(itemMng_->GetItem().get()->GetPos(), stage_->GetPos());

	//プレイヤーの描画
	DrawCircle(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, 10.0 * IMAGE_EX_RATE, 0xffff00);
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
