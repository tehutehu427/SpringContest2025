#pragma once
#include<vector>
#include <iostream>
#include <memory>

class Enemy;

class EnemyManager
{
public:
	//***********************************************
	//定数
	//***********************************************
	////内側
	//static constexpr VECTOR MOVE_POS_1 = { -600.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_2 = { 110.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_3 = { 800.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_4 = { -600.0f,100.0f,800.0f };
	////外側
	//static constexpr VECTOR MOVE_POS_5 = { 800.0f,100.0f,800.0f };
	//static constexpr VECTOR MOVE_POS_6 = { -600.0f,100.0f,200.0f };
	//static constexpr VECTOR MOVE_POS_7 = { 110.0f,100.0f,200.0f };
	//static constexpr VECTOR MOVE_POS_8 = { 800.0f,100.0f,200.0f };

	static constexpr int ENEMY_NUM =2;

	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	EnemyManager(void);

	// デストラクタ
	~EnemyManager(void) = default;

	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Release(void);
	
	//敵の取得
	Enemy* EnemyClass(void);

private:
	//***********************************************
	//メンバ変数
	//***********************************************

	//敵クラスのインスタンス
	//Enemy* enemy_[ENEMY_NUM];
	std::vector<Enemy*>enemys_;

	//移動位置
	std::vector<VECTOR>movePos_;

	//***********************************************
	//メンバ関数
	//***********************************************

	//敵の生成
	void CreateEnemy(void);

	//敵の消去
	void EraseEnemy(void);
};

