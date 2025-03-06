#pragma once

#include <vector>
#include <iostream>
#include <memory>

class Item;

class ItemManager
{
public:
	//***********************************************
	//定数
	//***********************************************

	static constexpr VECTOR SPAWN_POS_1 = { -600.0f,100.0f,1500.0f };
	static constexpr VECTOR SPAWN_POS_2 = { 110.0f,100.0f,1500.0f };
	static constexpr VECTOR SPAWN_POS_3 = { 800.0f,100.0f,1500.0f };
	static constexpr VECTOR SPAWN_POS_4 = { -600.0f,100.0f,800.0f };
	static constexpr VECTOR SPAWN_POS_5 = { 800.0f,100.0f,800.0f };
	static constexpr VECTOR SPAWN_POS_6 = {	-600.0f,100.0f,200.0f };
	static constexpr VECTOR SPAWN_POS_7 = { 110.0f,100.0f,200.0f };
	static constexpr VECTOR SPAWN_POS_8 = { 800.0f,100.0f,200.0f };

	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	ItemManager();
	//デストラクタ
	~ItemManager() = default;

	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//デバッグ描画
	void DrawDebug(void);
	//解放
	void Release(void);

	//アイテム取得
	const std::shared_ptr<Item> GetItem(void);

private:
	//***********************************************
	//メンバ変数
	//***********************************************

	//アイテム
	std::shared_ptr<Item> item_;

	//出現位置
	std::vector<VECTOR> spawnPos_;

	float cnt_;

	//***********************************************
	//メンバ関数
	//***********************************************

	//アイテムの生成
	void CreateItem(void);

	//アイテムの一定間隔での消去(デバッグ)
	void DebugCountDelete(void);
};

