#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "Stage.h"

//コンストラクト
Stage::Stage()
{

}

//デストラクタ
Stage::~Stage()
{

}

//初期化処理
bool Stage::Init()
{
	//モデルの読み込み
	if (!model_.Load("Data/Model/Stage.mv1"))
	{
		MessageBox(NULL, "モデルの読み込み失敗しました", "エラー", MB_OK);
		return false;
	}

	// モデルの位置・スケールを設定
	model_.SetPosition(0.0f, 0.0f, 0.0f);
	model_.SetScale(0.3f, 0.3f, 0.3f);

	return true;
}

// 更新処理
void Stage::Update() 
{

}

// 描画処理
void Stage::Draw() 
{
	// モデルを描画
	model_.Draw();
}