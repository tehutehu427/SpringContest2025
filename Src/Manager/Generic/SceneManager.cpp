#include <chrono>
#include <DxLib.h>
#include<EffekseerForDXLib.h>
#include<cassert>

#include "../../Scene/SceneTitle.h"
#include "../../Scene/SceneGame.h"
#include "../../Scene/SceneGameOver.h"
#include "../../Scene/SceneGameClear.h"
#include "ResourceManager.h"
#include"../System/Collision.h"
#include"../Decoration/SoundManager.h"
#include"Camera.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr){
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{
	//各マネージャの生成
	//判定の生成
	Collision::CreateInstance();
	SoundManager::CreateInstance();

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// カメラ
	camera_ = std::make_shared<Camera>();
	camera_->Init();

	scene_ = new SceneTitle();
	scene_->Init();

	isSceneChanging_ = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	//3D用の初期化
	Init3D();

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);
}

void SceneManager::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(0, 0, 0);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// ライトの設定
	SetLightEnable(true);

	// 正面から斜め下に向かったライト
	//ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

	// ライトの設定
	//ChangeLightTypeDir({ 0.3f, -0.7f, 0.8f });

	// フォグ設定
	SetFogEnable(true);
	SetFogColor(5, 5, 5);
	SetFogStartEnd(10000.0f, 20000.0f);

}


void SceneManager::Update(void)
{

	if (scene_ == nullptr)return;

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	fader_->Update();
	if (isSceneChanging_){
		Fade();
	}
	else{
		scene_->Update();
	}

	// カメラ更新
	camera_->Update();
}

void SceneManager::Draw(void)
{
	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	//フロントバッファの画像を消去
	ClearDrawScreen();

	// カメラ設定
	camera_->SetBeforeDraw();

	//ゲーム内容描画
	// 描画
	scene_->Draw();

	// 暗転・明転
	fader_->Draw();

	////フロントバッファに書き出し
	//ScreenFlip();
}

void SceneManager::Destroy(void)
{

	scene_->Release();
	delete scene_;

	SoundManager::GetInstance().Destroy();

	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

std::shared_ptr<Camera> SceneManager::GetCamera(void) const
{
	return camera_;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;
	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;	
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 1.0f / 60.0f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
	auto& resM = ResourceManager::GetInstance();

	// リソースの解放
	resM.Release();
	SoundManager::GetInstance().Release();

	// シーンを変更する
	sceneId_ = sceneId;

	// 現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		resM.InitTitle();
		break;		
		
	case SCENE_ID::GAME:
		scene_ = new SceneGame();
		resM.InitGame();
		break;

	case SCENE_ID::GAMEOVER:
		scene_ = new SceneGameOver();
		resM.InitGameOver();
		break;

	case SCENE_ID::GAMECLEAR:
		scene_ = new SceneGameClear();
		resM.InitGameClear();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;
}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			// 完全に暗転してからシーン遷移
			DoChangeScene(waitSceneId_);
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}