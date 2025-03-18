#include<DxLib.h>
#include"StageUiFont.h"
#include"titleUiDraw.h"

//デフォルトコンストラクタ
titleUi::titleUi(void)
{
	frameCount_ = 0;		//フレーム制御
	isBlinking_ = false;	//点滅フラグ
	selectedFont_ = FONT_TYPE::STATE;		//デフォルトは開始
	changeFlag_ = false;
}

//デストラクタ
titleUi::~titleUi(void)
{

}

//描画処理(毎フレーム実行)
void titleUi::Draw(void)
{
	DrawFont();
}

//フォントの描画処理
void titleUi::DrawFont(void)
{
	struct FontData
	{
		const char* message;
		FONT_TYPE type;
	};

	FontData fontList[] = {
		{"スペースを押して開始", FONT_TYPE::STATE},
		{"操作説明", FONT_TYPE::OPERATION},
		{"遊び方", FONT_TYPE::EXPLANATION},
		{"クレジット",FONT_TYPE::CREDIT}
	};


	for (const auto& font : fontList)
	{
		int textWidth = GetDrawStringWidth(font.message, static_cast<int>(strlen(font.message)));
		int xPos = 0 /*表示位置*/;
		int yPos = 0 /*表示位置*/;

		if (selectedFont_ == font.type && isBlinking_)
		{
			StageUiFont::GetInstance().DrawText(xPos, yPos, font.message, 0xFFFFFF, 24, StageUiFont::FONT_TYPE_EDGE, 3);  // 点滅する文字（白）
		}
		else
		{
			StageUiFont::GetInstance().DrawText(xPos, yPos, font.message, 0xAAAAAA, 24, StageUiFont::FONT_TYPE_EDGE, 3);  // 通常表示（グレー）
		}
	}
}

//フォント設定
void titleUi::FontSettings(void)
{
	//更新処理
	frameCount_++;

	//点滅タイミング(一定のフレーム事に切り替え)
	isBlinking_ = (frameCount_ / blinkInterval_) % 2 == 0;

}
