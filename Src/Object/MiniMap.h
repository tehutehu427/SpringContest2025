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
	static constexpr int MAP_SIZE = 130;											//ミニマップ画像の大きさ
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE + 15;	//ミニマップのX座標
	static constexpr float MAP_POS_Y = MAP_SIZE;									//ミニマップのY座標
	static constexpr double MAP_EX_RATE = 1.0;										//ミニマップ拡大率
	static constexpr double PLAYER_EX_RATE = 1.0;									//プレイヤー拡大率

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

	Player* player_;		//プレイヤー
	EnemyManager* eneMng_;	//敵
	ItemManager* itemMng_;	//アイテム

	int mapFrameImg_;		//枠画像
	int mapGroundImg_;		//枠内画像
	int mapPlayerImg_;		//プレイヤー画像

	//プレイヤー描画
	void DrawPlayer(void);

	//敵描画
	void DrawEnemy(void);

	//アイテム描画
	void DrawItem(void);

	//視野描画
	void DrawVision(void);
};

