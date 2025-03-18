#pragma once

#include<memory>
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;

class MiniMap
{
public:
	//コンストラクタ
	MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng);
	//デストラクタ
	~MiniMap();
	
	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Release(void);

private:

	Player* player_;
	EnemyManager* eneMng_;
	ItemManager* itemMng_;
};

