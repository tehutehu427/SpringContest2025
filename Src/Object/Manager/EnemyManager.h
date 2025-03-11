#pragma once

class Enemy;

class EnemyManager
{
public:

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
private:
	//敵クラスのインスタンス
	Enemy* enemy_;
};

