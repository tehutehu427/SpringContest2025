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

}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//˜g“à‚Ì•`‰æ
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, 1.0, 0.0, mapGroundImg_,true);
	
	//˜g‚Ì•`‰æ
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, 1.0, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}
