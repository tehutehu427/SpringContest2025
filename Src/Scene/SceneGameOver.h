#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:

    //�R���X�g���N�^
    SceneGameOver();

    //�f�X�g���N�^
    ~SceneGameOver() = default;

    //������
    void Init(void)override;
    //�X�V
    void Update(void)override;
    //�`��
    void Draw(void)override;
    //���
    void Release(void)override;

private:

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

