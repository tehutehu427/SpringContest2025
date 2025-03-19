#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Manager/ItemManager.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng)
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
	//プレイヤー
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//枠内の描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapGroundImg_,true);

	//プレイヤー描画
	DrawPlayer();
	
	//枠の描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}

void MiniMap::DrawPlayer(void)
{
	//プレイヤーの角度(Y軸)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//プレイヤーの描画
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, PLAYER_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
}

void MiniMap::DrawItem(void)
{
}

void MiniMap::DrawVision(void)
{
}
