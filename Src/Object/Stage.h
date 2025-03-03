#pragma once

#include"Common/Transform.h"

class Stage
{
public:
	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Release(void);

private:
	//***********************************************
	//メンバ変数
	//***********************************************

	//モデルの情報
	Transform trans_;
};