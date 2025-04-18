#pragma once
#include <DxLib.h>

#include "UnitBase.h"

class Enemy : public UnitBase
{
public:
	static constexpr float ENEMY_SIZE = 120.0f;		//敵の大きさ(半径)

	static constexpr float STAGE_SIZE = 1700.0f;	//ステージの大きさ(正方形1辺の長さ)

	static constexpr float ANIM_SPEED = 60.0f;		//アニメーション速度

	static constexpr float ATK_CNT = 2.0f;			//再攻撃時間

	static constexpr int MOVE_POINT = 4;		//敵の移動ポイント

	enum class MOVEDIR
	{
		NONE,

		UP,
		LEFT,
		RIGHT,
		DOWN,

	};
	enum class MOVECLOCKDIR 
	{
		NONE,

		CLOCKWISE,
		COUNTERCLOCKWISE,
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
	
	void SetMovePoint(const float& squarSize);
	void SetMoveSpeed(const float& moveSpeed);
	MOVECLOCKDIR SetMoveClockDir(const MOVECLOCKDIR& moveClockDir);
	MOVEDIR SetMoveDir(const MOVEDIR& moveDir);

	void SetDebugDrawPos(const int& pos);

	//攻撃済みか
	const bool IsAtk(void)const { return atkCnt_ < ATK_CNT; }

	//攻撃した
	void Hit(void) { atkCnt_ = 0.0f; }

private:

	void EnemyMove(void);
	void Clockwise(void);
	void CounterClockwise(void);

	/// <summary>
	/// とある点からとある点までの移動ベクトルを返す
	/// </summary>
	/// <param name="_start">狙う側</param>
	/// <param name="_goal">向かう先</param>
	/// <param name="_speed">設定速度(未設定だと、方向ベクトルのみを返す)</param>
	/// <returns>向かう先までの移動ベクトル</returns>
	const VECTOR GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed = 1.0f)const;

	/// <summary>
	/// とある点からとある点までの距離を返す
	/// </summary>
	/// <param name="_start">開始地点</param>
	/// <param name="_goal">終了地点</param>
	/// <returns>距離</returns>
	const float CalcDistance(const VECTOR _start, const VECTOR _goal)const;

	//アニメーション
	void InitAnimation(void)override;

	//移動方向
	MOVEDIR moveDir_;

	//移動方向(右、左回り)
	MOVECLOCKDIR moveClockDir_;

	//移動ポイント
	VECTOR movePointPos_[MOVE_POINT];

	//現在位置
	VECTOR nowPos_;

	//移動位置
	VECTOR goalPos_;

	int DebugDrawPos;

	//再攻撃時間
	float atkCnt_;

};
