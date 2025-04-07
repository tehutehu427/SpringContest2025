#pragma once

#include<memory>
#include "SceneBase.h"

class titleUi;

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

    //�Q�[���I�[�o�[���S
    int logo_;

    //UI
    std::unique_ptr<titleUi> ui_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

