#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Timer.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
}

void SceneGame::Init(void)
{
}

void SceneGame::Update(void)
{
	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	float i = 0;
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG
}

void SceneGame::Release(void)
{
}

void SceneGame::DrawDebug(void)
{
	//�f�o�b�O
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xff0000, true);
	DrawString(0, 0, "SceneGame", 0xffffff);
}
