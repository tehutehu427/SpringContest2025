#pragma once

#include"Common/Transform.h"

class UnitBase
{
public:

	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	UnitBase() = default;
	//デストラクタ
	virtual ~UnitBase() = 0;

	//初期化
	virtual void Init(void) = 0;
	//更新
	virtual void Update(void) = 0;
	//描画
	virtual void Draw(void) = 0;
	//解放
	virtual void Release(void) = 0;

protected:

	//***********************************************
	//メンバ変数
	//***********************************************

	//モデルの情報
	Transform trans_;

	//
};

