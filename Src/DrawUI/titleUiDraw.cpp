#include<DxLib.h>
#include"StageUiFont.h"
#include"titleUiDraw.h"

//�f�t�H���g�R���X�g���N�^
titleUi::titleUi(void)
{
	frameCount_ = 0;		//�t���[������
	isBlinking_ = false;	//�_�Ńt���O
	selectedFont_ = FONT_TYPE::STATE;		//�f�t�H���g�͊J�n
	changeFlag_ = false;
}

//�f�X�g���N�^
titleUi::~titleUi(void)
{

}

//�`�揈��(���t���[�����s)
void titleUi::Draw(void)
{
	DrawFont();
}

//�t�H���g�̕`�揈��
void titleUi::DrawFont(void)
{
	struct FontData
	{
		const char* message;
		FONT_TYPE type;
	};

	FontData fontList[] = {
		{"�X�y�[�X�������ĊJ�n", FONT_TYPE::STATE},
		{"�������", FONT_TYPE::OPERATION},
		{"�V�ѕ�", FONT_TYPE::EXPLANATION},
		{"�N���W�b�g",FONT_TYPE::CREDIT}
	};


	for (const auto& font : fontList)
	{
		int textWidth = GetDrawStringWidth(font.message, static_cast<int>(strlen(font.message)));
		int xPos = 0 /*�\���ʒu*/;
		int yPos = 0 /*�\���ʒu*/;

		if (selectedFont_ == font.type && isBlinking_)
		{
			StageUiFont::GetInstance().DrawText(xPos, yPos, font.message, 0xFFFFFF, 24, StageUiFont::FONT_TYPE_EDGE, 3);  // �_�ł��镶���i���j
		}
		else
		{
			StageUiFont::GetInstance().DrawText(xPos, yPos, font.message, 0xAAAAAA, 24, StageUiFont::FONT_TYPE_EDGE, 3);  // �ʏ�\���i�O���[�j
		}
	}
}

//�t�H���g�ݒ�
void titleUi::FontSettings(void)
{
	//�X�V����
	frameCount_++;

	//�_�Ń^�C�~���O(���̃t���[�����ɐ؂�ւ�)
	isBlinking_ = (frameCount_ / blinkInterval_) % 2 == 0;

}
