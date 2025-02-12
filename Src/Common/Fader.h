#pragma once

class Fader
{

public:

	//���ߍő�l
	static constexpr int ALPHA_MAX = 255;

	// ��ʂ������Â�����悤�̃A���t�@�l
	static constexpr int LITTLE_ALPHA = 150;

	// ��ʂ������Â����鎞�̃X�s�[�h
	static constexpr float LITTLE_FADE_OUT_SPEED = 2.0f;

	// �t�F�[�h���i�ޑ���
	static constexpr float SPEED_SCENE = 5.0f;	//�V�[���J��
	static constexpr float SPEED_PHASE = 2.0f;	//�t�F�[�Y�J��
	static constexpr float SPEED_ALPHA = 3.0f;
	

	// ���
	enum class STATE
	{
		NONE,			//�������Ă��Ȃ�
		FADE_OUT,		// ���X�ɈÓ]
		FADE_IN,		// ���X�ɖ��]	
		FADE_KEEP,		//���݂̏�Ԃ�ۂ�
		SET_FADE_OUT	// �A���t�@�l�����߂ĈÓ]
	};

	// ��Ԃ̎擾
	STATE GetState(void) const;

	// �t�F�[�h�������I�����Ă��邩
	bool IsEnd(void) const;

	// �w��t�F�[�h���J�n����
	void SetFade(STATE state);

	// �ǂꂭ�炢�Â����邩�̃A���t�@�l�����߂�
	void SetAlpha(float alpha);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);

protected:

	// ���
	STATE state_;

	// �Ó]�E���]�p�����x
	float alpha_;

	//�t�F�[�h���x
	float speed_;

	// �����x�̎w��l�p
	float alphaMax_;

	// ���(STATE)��ۂ����܂܏I��������s�����߁A
	// Update->Draw->Update��1�t���[������p
	bool isPreEnd_;

	// �t�F�[�h�����̏I������
	bool isEnd_;

private:
	
	//�}�X�N�摜�̈�
	int tmpScreen_;

	//�~�����̂���ʂ�����
	void CircleMask();

};