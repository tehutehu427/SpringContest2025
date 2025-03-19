#pragma once
#include<DxLib.h>

//モデルを管理するクラス
class StageModelLoader {
private:
	int modelHandle_;			//モデルのハンド
	VECTOR position_;			//モデルの位置
	VECTOR rotation_;			//モデルの回転角
	VECTOR scale_;				//モデルのスケール

public:
	//コンストラクタ
	StageModelLoader();
	
	//デストラクタ
	~StageModelLoader();

	//.xファイルを読み込む
	bool Load(const char* _filepath);

	//モデルハンドルを返す
	const int GetModelId(void) { return modelHandle_; }

	//モデルの位置を返す
	const VECTOR& GetPos(void) { return position_; }

	//モデルの位置を設定
	void SetPosition(float _x, float _y, float _z);

	//モデルの回転を返す
	const VECTOR& GetRot(void) { return rotation_; }

	//モデルの回転を設定
	void SetRotation(float _x, float _y, float _z);

	//モデルの位置を返す
	const VECTOR& GetScl(void) { return scale_; }

	//モデルのスケール
	void SetScale(float _x, float _y, float _z);

	//モデルを描画
	void Draw();

	//モデルを解放
	void Release();

};
