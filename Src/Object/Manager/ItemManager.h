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

	static constexpr VECTOR SPAWN_POS_1 = { -700.0f,50.0f,670.0f };
	static constexpr VECTOR SPAWN_POS_2 = { 0.0f,50.0f,670.0f };
	static constexpr VECTOR SPAWN_POS_3 = { 700.0f,50.0f,670.0f };
	static constexpr VECTOR SPAWN_POS_4 = { -700.0f,50.0f,0.0f };
	static constexpr VECTOR SPAWN_POS_5 = { 700.0f,50.0f,0.0f };
	static constexpr VECTOR SPAWN_POS_6 = {	-700.0f,50.0f,-700.0f };
	static constexpr VECTOR SPAWN_POS_7 = { 0.0f,50.0f,-700.0f };
	static constexpr VECTOR SPAWN_POS_8 = { 700.0f,50.0f,-700.0f };

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

	//アイテムの生成
	void CreateItem(void);

private:
	//***********************************************
	//メンバ変数
	//***********************************************

	//アイテム
	std::shared_ptr<Item> item_;

	//出現位置
	std::vector<VECTOR> spawnPos_;

	//出現番号
	int spawnNum_;

	float cnt_;

	//***********************************************
	//メンバ関数
	//***********************************************

	//アイテムの一定間隔での消去(デバッグ)
	void DebugCountDelete(void);
};

