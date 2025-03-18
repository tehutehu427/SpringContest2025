#include<DxLib.h>
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/Generic/InputManager.h"
#include"../DrawUI/titleUiDraw.h"
#include"../Object/Grid.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	grid_ = nullptr;
}

void SceneTitle::Init(void)
{
	auto camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

	//グリッド線
	grid_ = new Grid();
	grid_->Init();

	//UI
	ui_ = std::make_unique<titleUi>();
}

void SceneTitle::Update(void)
{
	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}

void SceneTitle::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

	//グリッド線
	grid_->Draw();

#endif // SCENE_DEBUG

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
