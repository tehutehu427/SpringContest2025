#include<DxLib.h>
#include"StageUiFont.h"
#include"titleUiDraw.h"
#include"../Application.h"

//デフォルトコンストラクタ
titleUi::titleUi(void)
{
	frameCount_ = 0;		//フレーム制御
	isBlinking_ = false;	//点滅フラグ
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
	for (const auto& font : fontList_)
	{
		int textWidth = GetDrawStringWidth(font.message, static_cast<int>(strlen(font.message)));
		int xPos = (Application::SCREEN_SIZE_X - textWidth - (textWidth / 2)) / 2/*表示位置*/;
		int yPos = Application::SCREEN_SIZE_Y / 2 + 100/*表示位置*/;

		if (isBlinking_)
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
	isBlinking_ = (frameCount_ / blinkInterval_) % 2 ? true : false;

}

void titleUi::AddCharactor(const char* _char)
{
	fontList_.emplace_back(_char);
}