#include<DxLib.h>
#include"../Application.h"
#include"../Common/Easing.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../Manager/System/Timer.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/System/Collision.h"
#include"../Object/SkyDome.h"
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
	//camera->ChangeMode(Camera::MODE::FREE);

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
	miniMap_ = std::make_unique<MiniMap>(player_.get(), enmMng_.get(), itemMng_.get(),stage_.get());
	miniMap_->Init();

	//スカイドームの初期化
	skyDome_ = std::make_unique<SkyDome>(player_->GetTransform());
	skyDome_->Init();

	//カメラをプレイヤーに追従
	camera->SetFollow(&player_->GetTransform());

	scrollBannerPos_ = Application::SCREEN_SIZE_X;
	scrollBannerTime_ = 0.0f;

	//サウンド
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GAME, res.Load(ResourceManager::SRC::BGM_GAME).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_GET, res.Load(ResourceManager::SRC::SE_GET).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_DAMAGE, res.Load(ResourceManager::SRC::SE_DAMAGE).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_GAME, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_GET, 50);
	sound.AdjustVolume(SoundManager::SOUND::SE_DAMAGE, 50);

	//初期BGM
	sound.Play(SoundManager::SOUND::BGM_GAME);
}

void SceneGame::Update(void)
{
	//バナーが流れ中か
	if (ScrollBanner())return;

	//スカイドームの更新
	skyDome_->Update();

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

	//ゲームクリア処理
	GameClear();

	//ゲームオーバー処理
	GameOver();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

#endif // SCENE_DEBUG

	//スカイドームの描画
	skyDome_->Draw();

	//ステージの描画
	stage_->Draw();

	//敵の描画
	enmMng_->Draw();

	//アイテムの描画
	itemMng_->Draw();

	//プレイヤーの描画
	player_->Draw();

	//ミニマップの描画
	miniMap_->Draw();

	//流れるバナーの描画
	int font = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_EDGE);

	DrawStringFToHandle(scrollBannerPos_, Application::SCREEN_SIZE_Y / 2, "敵を避けつつ、宝石を集めろ！！", 0xffffff, font);

	DeleteFontToHandle(font);
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

bool SceneGame::ScrollBanner(void)
{
	//流れている時間
	if (scrollBannerTime_ < SCROLL_BANNER_TIME)
	{
		scrollBannerTime_++;
		scrollBannerPos_ = SineOut(scrollBannerTime_
			, SCROLL_BANNER_TIME
			, Application::SCREEN_SIZE_X
			, -SCROLL_BANNER_SIZE_X *1.5);

		return true;
	}

	return false;
}

void SceneGame::Collision(void)
{
	CollisionPlayer();
	CollisionEnemy();
}

void SceneGame::CollisionPlayer(void)
{
	//サウンド
	auto& sound = SoundManager::GetInstance();

	//コライダ
	auto& col = Collision::GetInstance();

	player_->CollisionStage(stage_->GetModelId());

	for (auto& enemy : enmMng_->GetEnemys())
	{
		//プレイヤーと敵の当たり判定
		if (col.IsHitSpheres(player_->GetPos(), player_->GetRadius(), enemy->GetPos(), enemy->GetRadius()))
		{
			//攻撃してないなら
			if (!enemy->IsAtk())
			{
				//体力を下げる
				player_->SubHp();

				//再攻撃時間リセット
				enemy->Hit();

				//ダメージ音
				sound.Play(SoundManager::SOUND::SE_DAMAGE);
			}
		}
	}

	//プレイヤーとアイテムの当たり判定
	if (col.IsHitSpheres(player_->GetPos(), player_->GetRadius(), itemMng_->GetItem()->GetPos(), itemMng_->GetItem()->GetRadius()))
	{
		//アイテム取得数を増加
		player_->AddItemNum();

		//アイテムの再出現
		itemMng_->CreateItem();

		//取得音
		sound.Play(SoundManager::SOUND::SE_GET);
	}
}

void SceneGame::CollisionEnemy(void)
{
	//コライダ
	auto& col = Collision::GetInstance();

	enmMng_->CollisionStage(stage_->GetModelId());

	for (auto& enemy : enmMng_->GetEnemys())
	{

	}
}

void SceneGame::GameClear(void)
{
	//サウンド
	auto& sound = SoundManager::GetInstance();

	//ゲームクリア条件
	if (player_->GetItemNum() >= Player::ITEM_NUM)
	{
		//BGM停止
		sound.Stop(SoundManager::SOUND::BGM_GAME);

		//ゲームクリアに遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}

void SceneGame::GameOver(void)
{
	//サウンド
	auto& sound = SoundManager::GetInstance();

	//ゲームオーバー条件
	if (!player_->IsAlive())
	{
		//BGM停止
		sound.Stop(SoundManager::SOUND::BGM_GAME);

		//ゲームオーバーに遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}
}
