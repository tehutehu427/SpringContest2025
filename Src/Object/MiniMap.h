#pragma once

#include<memory>
#include"../Application.h"
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;

class MiniMap
{
public:

	//ミニマップ
	static constexpr int MAP_SIZE = 100;										//ミニマップ画像の大きさ
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE;	//ミニマップのX座標
	static constexpr float MAP_POS_Y = Application::SCREEN_SIZE_Y - MAP_SIZE;	//ミニマップのY座標

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

	std::unique_ptr<Player> player_;		//プレイヤー
	std::unique_ptr<EnemyManager> eneMng_;	//敵
	std::unique_ptr<ItemManager> itemMng_;	//アイテム

	int mapFrameImg_;		//枠画像
	int mapGroundImg_;		//枠内画像
};

