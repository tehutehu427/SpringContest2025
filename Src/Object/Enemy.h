#pragma once
#include <DxLib.h>

#include "UnitBase.h"

class Enemy : public UnitBase
{
public:
	static constexpr float ENEMY_SIZE = 50.0f;	//敵の大きさ(半径)

	static constexpr float STAGE_SIZE = 1700.0f;	//ステージの大きさ(正方形1辺の長さ)

	static constexpr float MOVE_SPEED = 10.0f;	//移動速度

	enum class MOVEDIR
	{
		NONE,

		UP,
		LEFT,
		RIGHT,
		DOWN,

	};

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

	//座標取得
	//VECTOR GetPos(void) const;

	void SetPos(const VECTOR& pos);


private:

	//移動方向
	MOVEDIR moveDir_;


	//移動量
	float moveSpeed_;


};
