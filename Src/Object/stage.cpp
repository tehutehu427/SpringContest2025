#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "Stage.h"

//�R���X�g���N�g
Stage::Stage()
{

}

//�f�X�g���N�^
Stage::~Stage()
{

}

//����������
bool Stage::Init()
{
	//���f���̓ǂݍ���
	if (!model_.Load("Data/Model/Stage.mv1"))
	{
		MessageBox(NULL, "���f���̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	// ���f���̈ʒu�E�X�P�[����ݒ�
	model_.SetPosition(0.0f, 0.0f, 0.0f);
	model_.SetScale(0.3f, 0.3f, 0.3f);

	return true;
}

// �X�V����
void Stage::Update() 
{

}

// �`�揈��
void Stage::Draw() 
{
	// ���f����`��
	model_.Draw();
}