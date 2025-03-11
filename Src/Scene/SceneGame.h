#pragma once

#include<memory>
#include "SceneBase.h"

class Stage;
class Player;
class EnemyManager;
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

    //�v���C���[
    std::unique_ptr<Player> player_;

    //�G�}�l�[�W���[
    std::unique_ptr<EnemyManager> enmMng_;

    //�A�C�e���}�l�[�W���[
    std::unique_ptr<ItemManager> itemMng_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);
};

