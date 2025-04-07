#include<DxLib.h>
#include"StageUiFont.h"
#include"titleUiDraw.h"
#include"../Application.h"

//�f�t�H���g�R���X�g���N�^
titleUi::titleUi(void)
{
	frameCount_ = 0;		//�t���[������
	isBlinking_ = false;	//�_�Ńt���O
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
	for (const auto& font : fontList_)
	{
		int textWidth = GetDrawStringWidth(font.message, static_cast<int>(strlen(font.message)));
		int xPos = (Application::SCREEN_SIZE_X - textWidth - (textWidth / 2)) / 2/*�\���ʒu*/;
		int yPos = Application::SCREEN_SIZE_Y / 2 + 100/*�\���ʒu*/;

		if (isBlinking_)
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
	isBlinking_ = (frameCount_ / blinkInterval_) % 2 ? true : false;

}

void titleUi::AddCharactor(const char* _char)
{
	fontList_.emplace_back(_char);
}