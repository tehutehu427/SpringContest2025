#include<DxLib.h>
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
}

void SceneGameOver::Init(void)
{
}

void SceneGameOver::Update(void)
{
	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
}

void SceneGameOver::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG
}

void SceneGameOver::Release(void)
{
}

void SceneGameOver::DrawDebug(void)
{
	//�f�o�b�O
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0x0000ff, true);
	DrawString(0, 0, "SceneGameOver", 0xffffff);
}
