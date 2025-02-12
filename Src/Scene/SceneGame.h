#pragma once
#include "SceneBase.h"

class SceneGame : public SceneBase
{
public:

    //�R���X�g���N�^
    SceneGame();

    //�f�X�g���N�^
    ~SceneGame() = default;

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

