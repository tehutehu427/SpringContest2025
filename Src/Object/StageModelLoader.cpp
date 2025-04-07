#include<iostream>
#include"StageModelLoader.h"

//�R���X�g���N�^
StageModelLoader::StageModelLoader()
{
	modelHandle_ = -1;
	position_ = VGet(0, 0, 0);
	compPos_ = VGet(0, 0, 0);
	rotation_ = VGet(0, 0, 0);
	scale_ = VGet(1, 1, 1);
}

//�f�X�g���N�^
StageModelLoader::~StageModelLoader()
{
	Release();
}

//.mv1�t�@�C����ǂݍ���
bool StageModelLoader::Load(const char* _filepath)
{
	modelHandle_ = MV1LoadModel(_filepath);			//���f�������[�h
	if (modelHandle_ == -1) {
		std::cerr << "���f���̓ǂݍ��݂Ɏ��s���܂���: " << _filepath << std::endl;
		return false;
	}
	return true;
}

//���f���̈ʒu��ݒ�
void StageModelLoader::SetPosition(float _x, float _y, float _z)
{
	position_ = VGet(_x, _y, _z);
	compPos_ = VAdd(position_, COMP_POS);
	MV1SetPosition(modelHandle_, compPos_);		//�ʒu��K�p
}

//���f���̉�]��ݒ�
void StageModelLoader::SetRotation(float _x, float _y, float _z)
{
	rotation_ = VGet(_x, _y, _z);
	MV1SetRotationXYZ(modelHandle_, rotation_);		//��]��K�p
}

//���f���̃X�P�[����ݒ�
void StageModelLoader::SetScale(float _x, float _y, float _z)
{
	scale_ = VGet(_x, _y, _z);
	MV1SetScale(modelHandle_, scale_);		//�X�P�[���̓K�p
}

//���f����`��
void StageModelLoader::Draw()
{
	if (modelHandle_ != -1)
	{
		MV1DrawModel(modelHandle_);		//���f���̕`��
	}
}

//���f�������
void StageModelLoader::Release()
{
	if (modelHandle_ != -1)
	{
		MV1DeleteModel(modelHandle_);	//���f���̏���
		modelHandle_ = -1;
	}
}