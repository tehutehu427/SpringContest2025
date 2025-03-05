#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Timer.h"
#include "../Object/ItemManager.h"
#include "../Object/Item.h"
#include "../Object/Stage.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
}

void SceneGame::Init(void)
{
	//ステージの初期化
	stage_ = std::make_unique<Stage>();
	stage_->Init();

	//アイテムの初期化
	itemMng_ = std::make_unique<ItemManager>();
	itemMng_->Init();
}

void SceneGame::Update(void)
{
	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	//ステージの更新
	stage_->Update();

	//アイテムの更新
	itemMng_->Update();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

#endif // SCENE_DEBUG

	//ステージの描画
	stage_->Draw();

	//アイテムの描画
	itemMng_->Draw();
}

void SceneGame::Release(void)
{
	//アイテムの解放
	itemMng_->Release();
}

void SceneGame::DrawDebug(void)
{
	//デバッグ
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xff0000, true);
	DrawString(0, 0, "SceneGame", 0xffffff);
}
