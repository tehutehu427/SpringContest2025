#pragma once

#include<unordered_map>
#include"Common/Transform.h"

class UnitBase
{
public:

	//***********************************************
	//列挙型
	//***********************************************

	//アニメーション
	enum class ANIM
	{
		NONE,	
		IDLE,	//待機
		WALK,	//歩き
	};

	//***********************************************
	//メンバ関数
	//***********************************************

	//コンストラクタ
	UnitBase();
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

	//位置
	const VECTOR GetPos(void)const { return trans_.pos; };
	//角度
	const VECTOR GetRot(void)const { return trans_.rot; };
	//大きさ
	const VECTOR GetScl(void)const { return trans_.scl; };

	//半径
	const float GetRadius(void)const { return radius_; }

	//アニメーションリセット
	void ResetAnim(const ANIM _anim, const float _speed);

protected:

	//***********************************************
	//メンバ変数
	//***********************************************

	//モデルの情報
	Transform trans_;

	//半径
	float radius_;

	//アニメーション
	ANIM anim_;								//アニメステート
	std::unordered_map<ANIM, int> animNum_;	//アニメーションナンバー格納配列。
	int atcAnim_;							//アタッチするアニメを格納
	int animTotalTime_;						//アニメーションの総再生時間
	float stepAnim_;						//アニメーションの再生時間
	float speedAnim_;						//アニメーション速度


	//***********************************************
	//メンバ関数
	//***********************************************

	//アニメーション関数
	void Anim(void);
	//アニメーション終了時の動き
	virtual void FinishAnim(void);
};

