#pragma once

#include"../../Common/Vector2.h"

class Collision
{
public:
	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static Collision& GetInstance(void);

	void Init(void);

	/// <summary>
	/// �����`���m�̓����蔻��
	/// </summary>
	/// <param name="_box1">�l�p�`�P�̈ʒu</param>
	/// <param name="_box1Range">�l�p�`�P�̒���</param>
	/// <param name="_box2">�l�p�`�Q�̈ʒu</param>
	/// <param name="_box2Range">�l�p�`�Q�̒���</param>
	/// <returns>�������Ă��邩(true:�������Ă���)</returns>
	bool IsHitBoxes(const Vector2F _box1, const float _box1Range, const Vector2F _box2, const float _box2Range)const;

	// ���̓��m�̏Փ˔���
	static bool IsHitSpheres(
		const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	// ���̂ƃJ�v�Z���̏Փ˔���
	static bool IsHitSphereCapsule(
		const VECTOR& sphPos, float sphRadius,
		const VECTOR& capPos1, const VECTOR& capPos2, float capRadius);

	/// <summary>
	/// �X�e�[�W���f���ƃL�����N�^�[�̏Փ˔���
	/// </summary>
	/// <param name="_modelId"></param>�X�e�[�W���f��
	/// <param name="_pos"></param>�L�����N�^�[�̍��W
	/// <param name="_radius"></param>�L�����N�^�[�̔��a
	/// <returns></returns>
	const bool IsHitUnitStageObject(const int& _modelId, const VECTOR& _pos, const float& _radius)const;

private:
	//�R���X�g���N�^���f�X�g���N�^
	Collision(void) = default;
	~Collision(void) = default;
	//�C���X�^���X�p
	static Collision* instance_;
};

