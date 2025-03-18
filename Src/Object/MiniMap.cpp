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

	//�g
	mapFrameImg_ = res.Load(ResourceManager::SRC::MAP_FRAME).handleId_;
	
	//�g��
	mapGroundImg_ = res.Load(ResourceManager::SRC::MAP_GROUND).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//�g���̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, 1.0, 0.0, mapGroundImg_,true);
	
	//�g�̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, 1.0, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}
