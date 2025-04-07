#include<iostream>
#include"StageModelLoader.h"

//コンストラクタ
StageModelLoader::StageModelLoader()
{
	modelHandle_ = -1;
	position_ = VGet(0, 0, 0);
	compPos_ = VGet(0, 0, 0);
	rotation_ = VGet(0, 0, 0);
	scale_ = VGet(1, 1, 1);
}

//デストラクタ
StageModelLoader::~StageModelLoader()
{
	Release();
}

//.mv1ファイルを読み込む
bool StageModelLoader::Load(const char* _filepath)
{
	modelHandle_ = MV1LoadModel(_filepath);			//モデルをロード
	if (modelHandle_ == -1) {
		std::cerr << "モデルの読み込みに失敗しました: " << _filepath << std::endl;
		return false;
	}
	return true;
}

//モデルの位置を設定
void StageModelLoader::SetPosition(float _x, float _y, float _z)
{
	position_ = VGet(_x, _y, _z);
	compPos_ = VAdd(position_, COMP_POS);
	MV1SetPosition(modelHandle_, compPos_);		//位置を適用
}

//モデルの回転を設定
void StageModelLoader::SetRotation(float _x, float _y, float _z)
{
	rotation_ = VGet(_x, _y, _z);
	MV1SetRotationXYZ(modelHandle_, rotation_);		//回転を適用
}

//モデルのスケールを設定
void StageModelLoader::SetScale(float _x, float _y, float _z)
{
	scale_ = VGet(_x, _y, _z);
	MV1SetScale(modelHandle_, scale_);		//スケールの適用
}

//モデルを描画
void StageModelLoader::Draw()
{
	if (modelHandle_ != -1)
	{
		MV1DrawModel(modelHandle_);		//モデルの描画
	}
}

//モデルを解放
void StageModelLoader::Release()
{
	if (modelHandle_ != -1)
	{
		MV1DeleteModel(modelHandle_);	//モデルの消去
		modelHandle_ = -1;
	}
}