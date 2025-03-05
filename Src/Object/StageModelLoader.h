#pragma once
#include<DxLib.h>

//���f�����Ǘ�����N���X
class StageModelLoader {
private:
	int modelHandle_;			//���f���̃n���h
	VECTOR position_;			//���f���̈ʒu
	VECTOR rotation_;			//���f���̉�]�p
	VECTOR scale_;				//���f���̃X�P�[��

public:
	//�R���X�g���N�^
	StageModelLoader();
	
	//�f�X�g���N�^
	~StageModelLoader();

	//.x�t�@�C����ǂݍ���
	bool Load(const char* _filepath);

	//���f���̈ʒu��ݒ�
	void SetPosition(float _x, float _y, float _z);

	//���f���̉�]��ݒ�
	void SetRotation(float _x, float _y, float _z);

	//���f���̃X�P�[��
	void SetScale(float _x, float _y, float _z);

	//���f����`��
	void Draw();

	//���f�������
	void Release();

};
