#pragma once

class Enemy;

class EnemyManager
{
public:

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static EnemyManager& GetInstance(void);


	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Release(void);
private:
	//静的インスタンス
	static EnemyManager* instance_;

	//敵クラスのインスタンス
	Enemy* enemy_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	EnemyManager(void);

	// デストラクタも同様
	~EnemyManager(void) = default;


};

