#pragma once
#include "SceneBase.h"

class SceneGameClear : public SceneBase
{
public:

    //�R���X�g���N�^
    SceneGameClear();

    //�f�X�g���N�^
    ~SceneGameClear() = default;

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

