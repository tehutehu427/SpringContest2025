#pragma once

#include<vector>

class StageUiFont;

//�^�C�g��UI�\���N���X(�^�C�g��UI�\���I�u�W�F�N�g�̐݌v�})
class titleUi
{
public:
	
	//�����f�[�^
	struct FontData
	{
		const char* message;
	};

private:
	int frameCount_;		       //�t���[�����[�g����̂��߂̕ϐ�
	const int blinkInterval_ = 30; //�_�ŊԊu(�t���[����)
	bool isBlinking_;			   //�_�Ńt���O
	bool changeFlag_;       //�؂�ւ��t���O

	std::vector<FontData> fontList_;


public:
	//�f�t�H���g�R���X�g���N�^
	titleUi(void);

	//�f�X�g���N�^
	~titleUi(void);

	//�`�揈��(���t���[�����s)
	void Draw(void);

	//�t�H���g�ݒ�
	void FontSettings(void);

	//�t�H���g�`��
	void DrawFont(void);

	//������ǉ�
	void AddCharactor(const char* _char);

};
