#pragma once

#include<memory>
#include "SceneBase.h"

class Stage;
class ItemManager;

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

    //�X�e�[�W
    std::unique_ptr<Stage> stage_;

    //�A�C�e���}�l�[�W���[
    std::unique_ptr<ItemManager> itemMng_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

