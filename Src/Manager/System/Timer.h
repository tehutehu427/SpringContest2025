#pragma once
#include"../Generic/SceneManager.h"

class Timer
{
public:

	void Update();
	void Draw();
	void Reset();	//�f�o�b�O�p

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static Timer& GetInstance(void);

	/// <summary>
	/// �f���^�^�C���ŃJ�E���g�A�b�v
	/// </summary>
	/// <param name="_value">�A�b�v������l</param>
	void CntUp(float& _value)const;
	
	/// <summary>
	/// �f���^�^�C���ŃJ�E���g�_�E��
	/// </summary>
	/// <param name="_value">�A�b�v������l</param>
	void CntDown(float& _value)const;

private:

	static Timer* instance_;
	
	void ReduceTime(void);

	Timer(void);
	~Timer(void);
};