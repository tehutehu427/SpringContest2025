#pragma once

#include<memory>
#include "SceneBase.h"

class Grid;
class titleUi;

class SceneTitle : public SceneBase
{
public:
    //�R���X�g���N�^
    SceneTitle();

    //�f�X�g���N�^
    ~SceneTitle() = default;

    //������
    void Init(void)override;
    //�X�V
    void Update(void)override;
    //�`��
    void Draw(void)override;
    //���
    void Release(void)override;

private:

    //�O���b�h��
    Grid* grid_;

    //�^�C�g��UI
    std::unique_ptr<titleUi> ui_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

