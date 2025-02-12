#pragma once
#include<unordered_map>


//Dxlib���ɉ����f�[�^��3D��ԏ�ɍĐ����鏈��������
//�ȒP�Ɍ����Ή����ɋ��������邱�Ƃ��\
//�����΂��蕡�G�����Ȃ̂Ō���ɉ�


class SoundManager
{
public:
	//�Đ��̎�ޕ�������Ƃ��Ɏg��
	enum class TYPE {
		NONE,
		BGM,
		SE
	};

	enum class SOUND {
		//�����Ɏg�p���鉹�y����ʉ��Ȃǂ𗅗�
		NONE,
	};

	struct SOUND_DATA
	{
		int data;		//�����f�[�^�i�[
		TYPE type;		//�����f�[�^�̎��	�����̗v�f�͍폜���邩��
		int playMode;	//�����f�[�^�̍Đ��^�C�v
	};

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SoundManager& GetInstance(void);

	/// <summary>
	/// �T�E���h�̒ǉ�
	/// </summary>
	/// <param name="_type">���̎�ޕ���(SE��BGM��)</param>
	/// <param name="_sound">��̓I�ȗp�r</param>
	/// <param name="_data">���̃f�[�^</param>
	void Add(const TYPE _type, const SOUND _sound, const int _data);

	/// <summary>
	/// �����f�[�^
	/// </summary>
	/// <param name="_sound">�����f�[�^</param>
	void Play(const SOUND _sound);

	/// <summary>
	/// ��~����
	/// </summary>
	/// <param name="_sound">�����f�[�^</param>
	void Stop(const SOUND _sound);

	//���
	void Release(void);

	/// <summary>
	/// ���ʒ���
	/// </summary>
	/// <param name="_sound">����</param>
	/// <param name="_persent">��������(0%�`100%)</param>
	void AdjustVolume(const SOUND _sound, const int _persent);

	void Destroy(void);
private:
	//�C���X�^���X�p
	static SoundManager* instance_;

	//�f�[�^�i�[�p
	std::unordered_map<SOUND, SOUND_DATA>sounds_;

	//�R���X�g���N�^���f�X�g���N�^
	SoundManager() = default;
	~SoundManager() = default;
};

