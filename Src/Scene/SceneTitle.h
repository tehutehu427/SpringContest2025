#pragma once

#include<memory>
#include "SceneBase.h"

class Grid;
class titleUi;

class SceneTitle : public SceneBase
{
public:
    //コンストラクタ
    SceneTitle();

    //デストラクタ
    ~SceneTitle() = default;

    //初期化
    void Init(void)override;
    //更新
    void Update(void)override;
    //描画
    void Draw(void)override;
    //解放
    void Release(void)override;

private:

    //グリッド線
    Grid* grid_;

    //タイトルUI
    std::unique_ptr<titleUi> ui_;

    //描画(デバッグ)
    void DrawDebug(void);
};

