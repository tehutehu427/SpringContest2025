#pragma once

#include"UnitBase.h"

class Item : public UnitBase
{
#define DEBUG_ITEM

public:
	//***********************************************
	//定数
	//***********************************************

	//半径
	static constexpr float RADIUS = 80.0f;

	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.05f,0.05f,0.05f };

	//モデルのモデル座標用
	static constexpr VECTOR MODEL_POS = { 0.0f,50.0f,0.0f };

	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	Item(VECTOR& _pos);
	//デストラクタ
	~Item() = default;

	//初期化
	void Init(void);
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//デバッグ描画
	void DrawDebug(void);
	//解放
	void Release(void)override;

private:

};

