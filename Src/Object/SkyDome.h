#pragma once
#include <map>
#include <functional>
#include "Common/Transform.h"
#include "UnitBase.h"

class SkyDome : public UnitBase
{

public:

	static constexpr float SCALE = 1.0f;
	static constexpr VECTOR SCALES = { SCALE, SCALE, SCALE };

	// ���
	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	// �R���X�g���N�^
	SkyDome(const Transform& syncTransform);

	// �f�X�g���N�^
	~SkyDome(void)override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// ���@�̏��
	const Transform& syncTransform_;

	// ���
	STATE state_;
	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;
	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void(void)> stateUpdate_;

	// ��ԑJ��
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStateStay(void);
	void ChangeStateFollow(void);

	// �X�V�X�e�b�v
	void UpdateNone(void);
	void UpdateStay(void);
	void UpdateFollow(void);

};
