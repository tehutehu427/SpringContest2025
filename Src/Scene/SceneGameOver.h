#pragma once

#include<memory>
#include "SceneBase.h"

class titleUi;

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

    //�Q�[���I�[�o�[���S
    int logo_;

    //�^�C�g��UI
    std::unique_ptr<titleUi> ui_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

