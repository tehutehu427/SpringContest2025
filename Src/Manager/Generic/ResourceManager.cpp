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
	// �^�C�g���V�[���Ŏg�����\�[�X
	//*********************************************

	Resource res;

	/*��*/

	//�^�C�g�����S
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "TitleLogo.png");
	resourcesMap_.emplace(SRC::TITLE_LOGO, res);

	//�^�C�g��BGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "Title.mp3");
	resourcesMap_.emplace(SRC::BGM_TITLE, res);

	//���艹
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

void ResourceManager::InitGame(void)
{
	//*********************************************
	// �Q�[���V�[���Ŏg�����\�[�X
	//*********************************************

	Resource res;

	//�X�J�C�h�[��
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Cave.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, res);
	
	////�X�e�[�W
	//res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage.mv1");
	//resourcesMap_.emplace(SRC::STAGE, res);

	//���
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "Gem.mv1");
	resourcesMap_.emplace(SRC::GEM, res);

	//�~�j�}�b�v�֌W
	//--------------------------------------------

	//�g
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapFrame.png");
	resourcesMap_.emplace(SRC::MAP_FRAME, res);

	//�g��
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapGround.png");
	resourcesMap_.emplace(SRC::MAP_GROUND, res);

	//�}�X�N�����p
	res = Resource(Resource::TYPE::MASK, Application::PATH_IMAGE + "MiniMap/MapMask.png");
	resourcesMap_.emplace(SRC::MAP_MASK, res);

	//�}�b�v�摜
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapImage.png");
	resourcesMap_.emplace(SRC::MAP_IMAGE, res);

	//�~�j�}�b�v�p�v���C���[
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapPlayer.png");
	resourcesMap_.emplace(SRC::MAP_PLAYER, res);

	//�~�j�}�b�v�p�G
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "MiniMap/MapEnemy.png");
	resourcesMap_.emplace(SRC::MAP_ENEMY, res);

	//�T�E���h
	//----------------------------------------------

	//�^�C�g��BGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameScene.mp3");
	resourcesMap_.emplace(SRC::BGM_GAME, res);

	//�_���[�W��
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "Damage.mp3");
	resourcesMap_.emplace(SRC::SE_DAMAGE, res);

	//�擾��
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "Get.mp3");
	resourcesMap_.emplace(SRC::SE_GET, res);

	ResourcePlayer();
	ResourceEnemy();
}

void ResourceManager::InitGameOver(void)
{
	//*********************************************
	// �Q�[���I�[�o�[�V�[���Ŏg�����\�[�X
	//*********************************************

	Resource res;

	//�Q�[���I�[�o�[
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameOverLogo.png");
	resourcesMap_.emplace(SRC::GAMEOVER_LOGO, res);

	//�Q�[���I�[�o�[BGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameOver.mp3");
	resourcesMap_.emplace(SRC::BGM_GAMEOVER, res);

	//���艹
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

void ResourceManager::InitGameClear(void)
{
	//*********************************************
	// �Q�[���N���A�V�[���Ŏg�����\�[�X
	//*********************************************

	Resource res;

	//�Q�[���N���A
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameClearLogo.png");
	resourcesMap_.emplace(SRC::GAMECLEAR_LOGO, res);

	//�Q�[���I�[�o�[BGM
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "GameClear.mp3");
	resourcesMap_.emplace(SRC::BGM_GAMECLEAR, res);

	//���艹
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "StartPush.mp3");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

//�v���C���[
//*************************************************************************************************************
void ResourceManager::ResourcePlayer(void)
{
	//*********************************************
	// �v���C���[���g�����\�[�X
	//*********************************************

	Resource res;
}

//�G
//*************************************************************************************************************
void ResourceManager::ResourceEnemy(void)
{
	//*********************************************
	// �G���g�����\�[�X
	//*********************************************

	Resource res;

	//�G
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
		// �o�^����Ă��Ȃ�
		return nullptr;
	}

	rPair->second.Load();

	// �O�̂��߃R�s�[�R���X�g���N�^
	Resource* ret = new Resource(rPair->second);
	loadedMap_.emplace(src, ret);

	return ret;
}
