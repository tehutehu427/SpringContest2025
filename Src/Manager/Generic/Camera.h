#pragma once
#include <DxLib.h>
#include <functional>
#include <map>
#include <cmath>
#include <DirectXMath.h>
#include "../../Common/Quaternion.h"

class Transform;

class Camera
{

public:
	//カメラの描画域(Near,Far)関連の定数------------------------------------------------------
	
	static constexpr float SPEED = 10.0f;			//カメラスピード：NEAR

	
	static constexpr float CAMERA_NEAR = 40.0f;		//カメラクリップ：NEAR

	
	static constexpr float CAMERA_FAR = 15000.0f;	//カメラクリップ：NEAR

	//カメラ座標関連の定数---------------------------------------------------------------------
	
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };					//カメラの初期座標

	static constexpr VECTOR RELATIVE_C2T_POS = { 0.0f, -400.0f, 500.0f };					//カメラ位置から注視点までの相対座標
	
	static constexpr VECTOR RELATIVE_C2T_POS_FOLLOW_PERSPECTIVE = { 0.0f, 0.0f, 200.0f };	//カメラ位置から注視点までの相対座標(追従対象視点)
	
	static constexpr VECTOR RELATIVE_F2C_POS_FOLLOW = { 0.0f, 500.0f, -500.0f };	//追従対象からカメラ位置までの相対座標(完全追従)

	//static constexpr VECTOR RELATIVE_F2C_POS_SPRING = { 0.0f, 40.0f, 150.0f };	//追従対象からカメラ位置までの相対座標(ばね付き)
	
	//カメラ移動関連の定数---------------------------------------------------------------------
	
	static constexpr float MAX_MOVE_SPEED = 5.0f;	//移動速度の最大値

	static constexpr float MOVE_ACC = 0.5f;			//加速

	static constexpr float MOVE_DEC = 0.2f;			//減速

	//カメラ揺らし関連の定数--------------------------------------------------------------------

	static constexpr float TIME_SHAKE = 0.5f;		//時間

	static constexpr float WIDTH_SHAKE = 5.0f;		//幅

	static constexpr float SPEED_SHAKE = 40.0f;		//スピード

	//カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT,		//定点カメラ
		FREE,				//フリーモード
		FOLLOW,				//追従モード
		FOLLOW_SPRING,		//ばね付き追従モード
		FOLLOW_PERSPECTIVE,	//追従対象視点モード
		SHAKE				//カメラ揺らし
	};

	//コンストラクタ
	Camera(void);

	//デストラクタ
	~Camera(void);

	//初期化処理
	void Init(void);

	//更新処理
	void Update(void);

	//カメラの描画モード関連
	void SetBeforeDraw(void);

	// 描画処理
	void Draw(void);

	//解放処理
	void Release(void);

	//座標取得
	VECTOR GetPos(void) const;

	//カメラモードの変更
	void ChangeMode(MODE mode);

	//追従対象の設定
	const void SetFollow(const Transform* follow);

	void SetPos(const VECTOR& pos,const VECTOR& target);

private:

	//追従対象
	const Transform* followTransform_;

	//カメラモード
	MODE mode_;			
	MODE currentMode_;	//Shakeモードに遷移する際に現在のモード保存するための変数

	//カメラの描画モード
	std::map<MODE, std::function<void(void)>> setBeforeDrawMode_;

	//カメラの位置
	VECTOR pos_;

	//カメラの注視点
	VECTOR targetPos_;

	//カメラの上方向
	VECTOR cameraUp_;

	//カメラの回転
	Quaternion rot_;

	//カメラの速度(移動量)
	VECTOR velocity_;

	//移動量
	float moveSpeed_;

	//向き
	VECTOR moveDir_;

	//画面揺らし用
	float stepShake_;

	VECTOR defaultPos_;

	VECTOR shakeDir_;

	//ライト
	int spotLight_;

	//カメラを初期位置に戻す
	void SetDefault(void);

	//ライト設定
	void SetLighting(void);

	//カメラの描画モード関連------------------
	void SetBeforeDrawFixedPoint(void);			//定点カメラ
	void SetBeforeDrawFree(void);				//フリーカメラ
	void SetBeforeDrawFollow(void);				//追従カメラ
	void SetBeforeDrawFollowSpring(void);		//ばね追従カメラ
	void SetBeforeDrawFollowPerspective(void);	//追従対象視点カメラ
	void SetBeforeDrawShake(void);				//カメラシェイク
	//----------------------------------------

	//カメラシェイク
	void Shake(void);

	//カメラシェイクさせるための準備
	void SetShake(float intensity, float duration);

	//移動操作
	void ProcessMove(void);

	//移動
	void Move(void);

	//加速
	void Accele(float speed);

	//減速（スピードを減少させる）
	void Decelerate(float speed);

};

