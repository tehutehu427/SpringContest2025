#pragma once

#include<memory>
#include "SceneBase.h"
#include"../Application.h"

class SkyDome;
class Stage;
class Player;
class EnemyManager;
class ItemManager;
class MiniMap;

class SceneGame : public SceneBase
{
public:

    //�����o�i�[�̑傫��
    static constexpr int SCROLL_BANNER_SIZE_X = 600;
    static constexpr int SCROLL_BANNER_SIZE_Y = 200;

    //�����o�i�[�̏o�Ă��鎞��
    static constexpr float SCROLL_BANNER_TIME = Application::DEFAULT_FPS * 6.0f;


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

    //�X�J�C�h�[��
    std::unique_ptr<SkyDome> skyDome_;

    //�X�e�[�W
    std::unique_ptr<Stage> stage_;

    //�v���C���[
    std::unique_ptr<Player> player_;

    //�G�}�l�[�W���[
    std::unique_ptr<EnemyManager> enmMng_;

    //�A�C�e���}�l�[�W���[
    std::unique_ptr<ItemManager> itemMng_;

    //�~�j�}�b�v
    std::unique_ptr<MiniMap> miniMap_;

    //�o�i�[�p
    float scrollBannerPos_;
    float scrollBannerTime_;

    //�`��(�f�o�b�O)
    void DrawDebug(void);

    /// <summary>
    /// �����o�i�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���ꒆ</returns>
    bool ScrollBanner(void);

    //�����蔻��
    void Collision(void);

    //�v���C���[�̓����蔻��
    void CollisionPlayer(void);
    //�v���C���[�̓����蔻��
    void CollisionEnemy(void);

    //�Q�[���̃N���A����
    void GameClear(void);

    //�Q�[���I�[�o�[����
    void GameOver(void);
};