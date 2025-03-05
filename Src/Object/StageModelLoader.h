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

	//モデルの位置を設定
	void SetPosition(float _x, float _y, float _z);

	//モデルの回転を設定
	void SetRotation(float _x, float _y, float _z);

	//モデルのスケール
	void SetScale(float _x, float _y, float _z);

	//モデルを描画
	void Draw();

	//モデルを解放
	void Release();

};
