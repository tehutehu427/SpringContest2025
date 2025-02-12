#include <DxLib.h>
#include "../Application.h"
#include "Fader.h"

Fader::STATE Fader::GetState(void) const
{
	return state_;
}

bool Fader::IsEnd(void) const
{
	return isEnd_;
}

void Fader::SetFade(STATE state)
{
	state_ = state;
	if (state_ != STATE::NONE)
	{
		isPreEnd_ = false;
		isEnd_ = false;
	}
}

void Fader::SetAlpha(float alpha)
{
	alphaMax_ = alpha_;
}

void Fader::Init(void)
{
	state_ = STATE::NONE;
	alpha_ = 0;
	alphaMax_ = 0;
	isPreEnd_ = true;
	isEnd_ = true;

	tmpScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		true
	);
}

void Fader::Update(void)
{
	if (isEnd_)
	{
		return;
	}

	switch (state_)
	{
	case STATE::NONE:
	case STATE::FADE_KEEP:
		return;

	case STATE::FADE_OUT:
		alpha_ += SPEED_ALPHA;
		if (alpha_ > ALPHA_MAX)
		{
			// �t�F�[�h�I��
			alpha_ = ALPHA_MAX;
			if (isPreEnd_)
			{
				// 1�t���[����(Draw��)�ɏI���Ƃ���
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}

		break;

	case STATE::FADE_IN:
		alpha_ -= SPEED_SCENE;
		if (alpha_ < 0)
		{
			// �t�F�[�h�I��
			alpha_ = 0;
			if (isPreEnd_)
			{
				// 1�t���[����(Draw��)�ɏI���Ƃ���
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}
		break;

	case STATE::SET_FADE_OUT:
		alpha_ += SPEED_ALPHA;
		if (alpha_ > alphaMax_)
		{
			// �t�F�[�h�I��
			alpha_ = LITTLE_ALPHA;
			if (isPreEnd_)
			{
				// 1�t���[����(Draw��)�ɏI���Ƃ���
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}
		break;

	default:
		return;
	}

}

void Fader::Draw(void)
{

	switch (state_)
	{
	case STATE::NONE:
		return;

	case STATE::FADE_KEEP:
	case STATE::SET_FADE_OUT:
	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		CircleMask();
		break;
	}
}

void Fader::CircleMask()
{
	// �`��̈���}�X�N�摜�̈�ɐ؂�ւ���
	// ���X�́A�w�ʃX�N���[���ɂȂ��Ă���
	SetDrawScreen(tmpScreen_);

	//��ʑS�̂����ɓh��
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x000000,
		true);

	//���F�̉~��`�悷��
	//alpha�l�𗘗p���đ傫���𐧌�
	DrawCircle(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		(ALPHA_MAX - alpha_) * 4,
		0xffffff,
		true);

	//�`��̈�����ɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);

	//�`���F�̏�Z���[�h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_MUL, 0);

	//���X�̃Q�[����ʂɃ}�X�N�摜��`�悷��
	DrawGraph(0, 0, tmpScreen_, false);

	//�`�惂�[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
