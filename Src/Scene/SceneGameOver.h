#pragma once

#include<memory>
#include "SceneBase.h"

class titleUi;

class SceneGameOver : public SceneBase
{
public:

    //コンストラクタ
    SceneGameOver();

    //デストラクタ
    ~SceneGameOver() = default;

    //初期化
    void Init(void)override;
    //更新
    void Update(void)override;
    //描画
    void Draw(void)override;
    //解放
    void Release(void)override;

private:

    //ゲームオーバーロゴ
    int logo_;

    //タイトルUI
    std::unique_ptr<titleUi> ui_;

    //描画(デバッグ)
    void DrawDebug(void);
};

