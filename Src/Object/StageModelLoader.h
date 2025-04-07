#pragma once
#include<DxLib.h>

//���f�����Ǘ�����N���X
class StageModelLoader {
private:
	int modelHandle_;			//���f���̃n���h��
	VECTOR position_;			//���f���̈ʒu
	VECTOR compPos_;			//���f���̕⊮�p���W
	VECTOR rotation_;			//���f���̉�]�p
	VECTOR scale_;				//���f���̃X�P�[��

public:

	static constexpr VECTOR COMP_POS = { -110.0f,0.0f,110.0f };

	//�R���X�g���N�^
	StageModelLoader();
	
	//�f�X�g���N�^
	~StageModelLoader();

	//.x�t�@�C����ǂݍ���
	bool Load(const char* _filepath);

	//���f���n���h����Ԃ�
	const int GetModelId(void) { return modelHandle_; }

	//���f���̈ʒu��Ԃ�
	const VECTOR& GetPos(void) { return position_; }

	//���f���̈ʒu��ݒ�
	void SetPosition(float _x, float _y, float _z);

	//���f���̉�]��Ԃ�
	const VECTOR& GetRot(void) { return rotation_; }

	//���f���̉�]��ݒ�
	void SetRotation(float _x, float _y, float _z);

	//���f���̈ʒu��Ԃ�
	const VECTOR& GetScl(void) { return scale_; }

	//���f���̃X�P�[��
	void SetScale(float _x, float _y, float _z);

	//���f����`��
	void Draw();

	//���f�������
	void Release();

};
