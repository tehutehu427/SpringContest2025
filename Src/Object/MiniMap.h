#pragma once

#include<memory>
#include"../Application.h"
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;
class Stage;

class MiniMap
{
public:

	//ミニマップ
	static constexpr int MAP_SIZE = 130;											//ミニマップ画像の大きさ
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE + 15;	//ミニマップのX座標
	static constexpr float MAP_POS_Y = MAP_SIZE;									//ミニマップのY座標
	static constexpr double IMAGE_EX_RATE = 1.0;									//ミニマップ拡大率
	static constexpr double MAP_EX_RATE = 0.075;									//ミニマップ拡大率

	//コンストラクタ
	MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage);
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
	Stage* stage_;			//ステージ

	int mapFrameImg_;		//枠画像
	int mapGroundImg_;		//枠内画像
	int mapImg_;			//マップ画像
	int mapPlayerImg_;		//プレイヤー画像
	int mapEnemyImg_;		//敵画像

	/// <summary>
	/// とある位置からとある位置までの相対距離
	/// </summary>
	/// <param name="_startObj">開始オブジェクト位置</param>
	/// <param name="_goalObj">終了オブジェクト位置</param>
	/// <returns>相対距離</returns>
	const VECTOR GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const;

	//プレイヤー描画
	void DrawPlayer(void);

	//敵描画
	void DrawEnemy(void);

	//アイテム描画
	void DrawItem(void);

	//視野描画
	void DrawVision(void);

	/// <summary>
	/// とある点からとある点までの移動ベクトルを返す
	/// </summary>
	/// <param name="_start">狙う側</param>
	/// <param name="_goal">向かう先</param>
	/// <param name="_speed">設定速度(未設定だと、方向ベクトルのみを返す)</param>
	/// <returns>向かう先までの移動ベクトル</returns>
	const VECTOR GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed = 1.0f)const;

	/// <summary>
	/// とある点からとある点までの距離を返す
	/// </summary>
	/// <param name="_start">開始地点</param>
	/// <param name="_goal">終了地点</param>
	/// <returns>距離</returns>
	const float CalcDistance(const VECTOR _start, const VECTOR _goal)const;

};

