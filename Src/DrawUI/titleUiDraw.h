#pragma once
class StageUiFont;

//タイトルUI表示クラス(タイトルUI表示オブジェクトの設計図)
class titleUi
{
public:

private:
	int frameCount_;		       //フレームレート制御のための変数
	const int blinkInterval_ = 30; //点滅間隔(フレーム数)
	bool isBlinking_;			   //点滅フラグ
	bool changeFlag_;       //切り替えフラグ

public:
	//デフォルトコンストラクタ
	titleUi(void);

	//デストラクタ
	~titleUi(void);

	//描画処理(毎フレーム実行)
	void Draw(void);

	//フォント設定
	void FontSettings(void);

	//フォント描画
	void DrawFont(void);



};
