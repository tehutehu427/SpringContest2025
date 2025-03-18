#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{
public:
	//コンストラクタ
	Player() = default;
	//デストラクタ
	~Player()override;

	//初期化
	void Init(void)override;
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Release(void)override;
};

