#pragma once
#include<vector>
#include <iostream>
#include <memory>

class Enemy;

class EnemyManager
{
public:
	static constexpr int ENEMY_NUM =2;

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
	//敵クラスのインスタンス
	//Enemy* enemy_[ENEMY_NUM];
	std::vector<Enemy*>enemys_;


	void CreateEnemy(void);
	void EraseEnemy(void);
};

