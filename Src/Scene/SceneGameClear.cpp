#include<DxLib.h>
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include "SceneGameClear.h"

SceneGameClear::SceneGameClear()
{
}

void SceneGameClear::Init(void)
{
}

void SceneGameClear::Update(void)
{
	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
}

void SceneGameClear::Draw(void)
{
#ifdef SCENE_DEBUG

	//デバッグ
	DrawDebug();

#endif // SCENE_DEBUG
}

void SceneGameClear::Release(void)
{
}

void SceneGameClear::DrawDebug(void)
{
	//デバッグ
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0x00ff00, true);
	DrawString(0, 0, "SceneGameClear", 0xffffff);
}
