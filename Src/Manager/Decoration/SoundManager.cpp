#include<DxLib.h>
#include<cassert>
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr) {
		instance_ = new SoundManager();
	}
}

SoundManager& SoundManager::GetInstance(void)
{
	return *instance_;
}

/// <summary>
/// �T�E���h�̒ǉ�
/// </summary>
/// <param name="_type">���̎�ޕ���(SE��BGM��)</param>
/// <param name="_sound">��̓I�ȗp�r</param>
/// <param name="_data">���̃f�[�^</param>
void SoundManager::Add(const TYPE _type, const SOUND _sound, const int _data)
{
	//�A�z�z����ɂ��łɗv�f�������Ă��邩������
	//�����Ă����珈���I��
	if (sounds_.find(_sound) != sounds_.end())return;


	//�Đ�����Ƃ��f�[�^�̎�ނɂ����
	//���[�v�Đ����P�����𔻒f����
	int mode = -1;
	if (_type == TYPE::BGM) mode = DX_PLAYTYPE_LOOP;
	else mode = DX_PLAYTYPE_BACK;

	//�V�K�f�[�^�̂��ߏ���ǉ�
	sounds_.emplace(_sound, SOUND_DATA{ _data,_type ,mode});
}

/// <summary>
/// �����f�[�^
/// </summary>
/// <param name="_sound">�����f�[�^</param>
void SoundManager::Play(const SOUND _sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(_sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ��������Đ����悤�Ƃ��Ă��܂��B");

	//�Đ�����
	PlaySoundMem(sounds_[_sound].data, sounds_[_sound].playMode);
}

///<summary>
///��~����
///</summary>
///<param name="_sound">�����f�[�^</param>
void SoundManager::Stop(const SOUND _sound)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(_sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ��������~���悤�Ƃ��Ă��܂��B");
	StopSoundMem(sounds_[_sound].data);
}

void SoundManager::Release(void)
{
	//�z��v�f�P�폜
	sounds_.clear();
}

/// <summary>
/// ���ʒ���
/// </summary>
/// <param name="_sound">����</param>
/// <param name="_persent">��������(0%�`100%)</param>
void SoundManager::AdjustVolume(const SOUND _sound, const int _persent)
{
	//���f�[�^���Ȃ��Ƃ��͌x��
	if (sounds_.find(_sound) == sounds_.end())assert("�ݒ肵�Ă��Ȃ�������ݒ肵�悤�Ƃ��Ă��܂��B");
	ChangeVolumeSoundMem(255 * _persent / 100, sounds_[_sound].data);
}

void SoundManager::Destroy(void)
{
	Release();
	delete instance_;
}
