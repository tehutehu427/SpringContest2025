#pragma once
#include "UnitBase.h"
class Enemy : public UnitBase
{
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy()override;

	//初期化
	void Init(void)override;
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Release(void)override;
};

