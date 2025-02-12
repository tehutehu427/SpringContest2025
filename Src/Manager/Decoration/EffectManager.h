#pragma once
#include<DxLib.h>
#include"SoundManager.h"
#include"../../Common/Quaternion.h"
#include<unordered_map>
#include<string>

//���ʂ̂Ȃ��悤�ɗv���P

class EffectManager
{
public:

	//�e��G�t�F�N�g�̏��
	static constexpr int NONE_MAX = 5;

	enum class EFFECT
	{
		//�g�p����G�t�F�N�g�𗅗�
		NONE,
		LIFE_UP,
		ATTACK_UP,
		DEFENCE_UP,
		SPEED_UP,
		FIREWORK,
		DAMAGE,
		//Enemy���g�p
		BOSS_PUNCH,
		BOSS_SHOUT,
		BOSS_SHOUT_ATK,
		STATE_DOWN,

		//KNIGHT
		GUARD,
		HIT2,	//�G�֓����������̃G�t�F�N�g

		//AXE
		CHARGE_AXE_HIT,

		//ARCHER
		ARROW_RED,		//��̃G�t�F�N�g(��)
		ARROW_WHITE,	//��̃G�t�F�N�g(��)

		//�`���[�W�X�L��
		CHARGE_SKILL,
	};


	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static EffectManager& GetInstance(void);

	/// <summary>
	/// �G�t�F�N�g�̒ǉ�
	/// </summary>
	/// <param name="_efc">�G�t�F�N�g��ޖ�</param>
	/// <param name="_data">�G�t�F�N�g�̃f�[�^</param>
	void Add(const EFFECT& _efc,int _data);

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="_efc">�G�t�F�N�g��ޖ�</param>
	/// <param name="_pos">�Đ��ʒu</param>
	/// <param name="_qua">�p�x</param>
	/// <param name="_size">�傫��</param>
	/// <param name="_sound">���ʉ�</param>
	void Play(const EFFECT& _efc,
		const VECTOR& _pos, const Quaternion& _qua, const float& _size,
		const SoundManager::SOUND _sound);

	/// <summary>
	/// �G�t�F�N�g�̍Đ���~
	/// </summary>
	/// <param name="_efc">�G�t�F�N�g��ޖ�</param>
	void Stop(const EFFECT& _efc);

	/// <summary>
	/// �G�t�F�N�g�̊e�p�����[�^����
	/// </summary>
	/// <param name="_efc">�G�t�F�N�g��</param>
	/// <param name="_pos">�ʒu���</param>
	/// <param name="_qua">��]���</param>
	/// <param name="_size">�傫��</param>
	void SyncEffect(const EFFECT& _efc, const VECTOR& _pos, const Quaternion& _qua, const float& _size);

	/// <summary>
	/// �G�t�F�N�g�̍Đ��m�F
	/// </summary>
	/// <param name="_efc">�G�t�F�N�g��</param>
	bool IsPlayEffect(const EFFECT& _efc);

	//�������
	void Release(void);

	//��������
	void Destroy(void);

private:
	//�C���X�^���X�p
	static EffectManager* instance_;

	//�G�t�F�N�g�f�[�^�i�[�p
	std::unordered_map<EFFECT,int> effectRes_;	//�����f�[�^
	std::unordered_map<EFFECT,int> effectPlay_;	//�Đ��f�[�^
	//std::unordered_map<EFFECT,int[]> effectTest_;	//�Đ��f�[�^
	std::unordered_map<EFFECT, int> effectMax_;		//�Đ��f�[�^�̍ő及����

	//�R���X�g���N�^���f�X�g���N�^
	EffectManager(void);
	~EffectManager() = default;
};

