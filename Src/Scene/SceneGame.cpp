#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Timer.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/System/Collision.h"
#include "../Object/MiniMap.h"
#include "../Object/Manager/ItemManager.h"
#include "../Object/Item.h"
#include "../Object/Manager/EnemyManager.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Object/Stage.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
}

void SceneGame::Init(void)
{
	//カメラ
	auto camera = SceneManager::GetInstance().GetCamera();

	//カメラを固定に設定
	camera->ChangeMode(Camera::MODE::FOLLOW_PERSPECTIVE);

	//ステージの初期化
	stage_ = std::make_unique<Stage>();
	stage_->Init();

	//プレイヤーの初期化
	player_ = std::make_unique<Player>();
	player_->Init();

	//敵の初期化
	enmMng_ = std::make_unique<EnemyManager>();
	enmMng_->Init();

	//アイテムの初期化
	itemMng_ = std::make_unique<ItemManager>();
	itemMng_->Init();

	//アイテムの初期化
	miniMap_ = std::make_unique<MiniMap>(player_.get(), enmMng_.get(), itemMng_.get());
	miniMap_->Init();

	//カメラをプレイヤーに追従
	camera->SetFollow(&player_->GetTransform());
	camera->SetRot(player_->GetRot());
}

void SceneGame::Update(void)
{
	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	//ステージの更新
	stage_->Update();

	//プレイヤーの更新
	player_->Update();

	//敵の更新
	enmMng_->Update();

	//アイテムの更新
	itemMng_->Update();

	//ミニマップの更新
	miniMap_->Update();

	//当たり判定
	Collision();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

#endif // SCENE_DEBUG

	//ステージの描画
	stage_->Draw();

	//プレイヤーの描画
	player_->Draw();

	//敵の描画
	enmMng_->Draw();

	//アイテムの描画
	itemMng_->Draw();

	//ミニマップの描画
	miniMap_->Draw();
}

void SceneGame::Release(void)
{
	//ミニマップの解放
	miniMap_->Release();

	//アイテムの解放
	itemMng_->Release();

	//敵の解放
	enmMng_->Release();

	//プレイヤーの解放
	player_->Release();
}

void SceneGame::DrawDebug(void)
{
	//デバッグ
	//DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xff0000, true);
	DrawString(0, 0, "SceneGame", 0xffffff);
}

void SceneGame::Collision(void)
{
	auto& col = Collision::GetInstance();

	//プレイヤーと敵の当たり判定
	//for(auto enm:enmMng_->)
	
	//if(col.IsHitUnitStageObject(stage_->GetModelId(),player_->GetPos(),Player::SIZE))
}
