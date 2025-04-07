#include <DxLib.h>
#include "../../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

}

void ResourceManager::InitTitle(void)
{
	//*********************************************
	// タイトルシーンで使うリソース
	//*********************************************

	Resource res;

	/*例*/

	//タイトルロゴ
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "TitleLogo.png");
	resourcesMap_.emplace(SRC::TITLE_LOGO, res);

	//タイトルBGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "Title.mp3");
	resourcesMap_.emplace(SRC::BGM_TITLE, res);

	//決定音
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

void ResourceManager::InitGame(void)
{
	//*********************************************
	// ゲームシーンで使うリソース
	//*********************************************

	Resource res;

	//スカイドーム
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Cave.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, res);
	
	////ステージ
	//res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage.mv1");
	//resourcesMap_.emplace(SRC::STAGE, res);

	//宝石
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Gem.mv1");
	resourcesMap_.emplace(SRC::GEM, res);

	//ミニマップ関係
	//--------------------------------------------

	//枠
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapFrame.png");
	resourcesMap_.emplace(SRC::MAP_FRAME, res);

	//枠内
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapGround.png");
	resourcesMap_.emplace(SRC::MAP_GROUND, res);

	//マスク処理用
	res = Resource(Resource::TYPE::MASK, Application::PATH_IMAGE + "MiniMap/MapMask.png");
	resourcesMap_.emplace(SRC::MAP_MASK, res);

	//マップ画像
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapImage.png");
	resourcesMap_.emplace(SRC::MAP_IMAGE, res);

	//ミニマップ用プレイヤー
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapPlayer.png");
	resourcesMap_.emplace(SRC::MAP_PLAYER, res);

	//ミニマップ用敵
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapEnemy.png");
	resourcesMap_.emplace(SRC::MAP_ENEMY, res);

	//サウンド
	//----------------------------------------------

	//タイトルBGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameScene.mp3");
	resourcesMap_.emplace(SRC::BGM_GAME, res);

	//ダメージ音
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "Damage.mp3");
	resourcesMap_.emplace(SRC::SE_DAMAGE, res);

	//取得音
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "Get.mp3");
	resourcesMap_.emplace(SRC::SE_GET, res);

	ResourcePlayer();
	ResourceEnemy();
}

void ResourceManager::InitGameOver(void)
{
	//*********************************************
	// ゲームオーバーシーンで使うリソース
	//*********************************************

	Resource res;

	//ゲームオーバー
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameOverLogo.png");
	resourcesMap_.emplace(SRC::GAMEOVER_LOGO, res);

	//ゲームオーバーBGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameOver.mp3");
	resourcesMap_.emplace(SRC::BGM_GAMEOVER, res);

	//決定音
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

void ResourceManager::InitGameClear(void)
{
	//*********************************************
	// ゲームクリアシーンで使うリソース
	//*********************************************

	Resource res;

	//ゲームクリア
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameClearLogo.png");
	resourcesMap_.emplace(SRC::GAMECLEAR_LOGO, res);

	//ゲームオーバーBGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameClear.mp3");
	resourcesMap_.emplace(SRC::BGM_GAMECLEAR, res);

	//決定音
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

//プレイヤー
//*************************************************************************************************************
void ResourceManager::ResourcePlayer(void)
{
	//*********************************************
	// プレイヤーが使うリソース
	//*********************************************

	Resource res;
}

//敵
//*************************************************************************************************************
void ResourceManager::ResourceEnemy(void)
{
	//*********************************************
	// 敵が使うリソース
	//*********************************************

	Resource res;

	//敵
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Zombie.mv1");
	resourcesMap_.emplace(SRC::ENEMY, res);
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second->Release();
		delete p.second;
	}

	loadedMap_.clear();
	resourcesMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	delete instance_;
}

Resource ResourceManager::Load(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res->handleId_);
	res->duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource* ResourceManager::_Load(SRC src)
{
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return nullptr;
	}

	rPair->second.Load();

	// 念のためコピーコンストラクタ
	Resource* ret = new Resource(rPair->second);
	loadedMap_.emplace(src, ret);

	return ret;
}
