#include<DxLib.h>
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../DrawUI/titleUiDraw.h"
#include"../Object/Grid.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	logo_ = -1;
	grid_ = nullptr;
}

void SceneTitle::Init(void)
{
	//カメラ設定
	auto camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

	//タイトルロゴ
	logo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_LOGO).handleId_;

	//グリッド線
	grid_ = new Grid();
	grid_->Init();

	//UI
	ui_ = std::make_unique<titleUi>();
	ui_->AddCharactor("Spaceを押して開始");

	//サウンド
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	//初期BGM
	sound.Play(SoundManager::SOUND::BGM_TITLE);
}

void SceneTitle::Update(void)
{
	auto& sound = SoundManager::GetInstance();

	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		//決定音
		sound.Play(SoundManager::SOUND::SE_PUSH);

		//BGM停止
		sound.Stop(SoundManager::SOUND::BGM_TITLE);

		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		
		//処理終了
		return;
	}

	//点滅
	ui_->FontSettings();
}

void SceneTitle::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

	//グリッド線
	grid_->Draw();

#endif // SCENE_DEBUG

	//タイトルロゴ
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0, 0.0, logo_, true);

	int font = CreateFontToHandle(NULL, 10, 10);

	//隠し要素
	DrawStringFToHandle(0.0f, 0.0f, "音源探してくれた人:要注意人物", 0x222222, font);

	DeleteFontToHandle(font);

	//UI
	ui_->Draw();
}

void SceneTitle::Release(void)
{
	grid_->Release();
	delete grid_;
	grid_ = nullptr;
}

void SceneTitle::DrawDebug(void)
{
	//デバッグ
	//DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xffffff, true);
	DrawString(0, 0, "SceneTitle", 0xffffff);
}
