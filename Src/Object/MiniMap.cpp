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
}

void MiniMap::Release(void)
{
}
