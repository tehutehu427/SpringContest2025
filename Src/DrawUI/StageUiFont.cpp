#include<DxLib.h>
#include"StageUiFont.h"

//シングルトンインスタンスの初期化
StageUiFont* StageUiFont::instance_ = nullptr;

//コンストラクタ
StageUiFont::StageUiFont() : fontHanble_(-1), fontSize_(24), fontType_(DX_FONTTYPE_ANTIALIASING_EDGE), fontWeight_(3){}

//デストラクタ
StageUiFont::~StageUiFont()
{
	if (fontHanble_ != -1 && fontHanble_ != DX_DEFAULT_FONT_HANDLE)
	{
		DeleteFontToHandle(fontHanble_);		//フォントハンドルの解放
	}
}

//シングルトンインスタンス取得
StageUiFont& StageUiFont::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new StageUiFont();
	}
	return *instance_;
}

//フォント初期化
bool StageUiFont::Init()
{
	int fontFileSize = FileRead_size("ここにフォントファイル(.ttf)のファイルパス");		//フォントファイルのサイズ
	int fontFileHandle = FileRead_open("ここにフォントファイル(.ttf)のファイルパス");	//フォントファイルを開く

	//フォント読み込み失敗処理
	if (fontFileSize <= 0 || fontFileHandle == -1)
	{
		OutputDebugString("フォントファイルが見つかりません。");
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
		return false;
	}

	//フォントデータをメモリに読み込む
	void* Buffer = new char[fontFileSize];
	FileRead_read(Buffer, fontFileSize, fontFileHandle);

	DWORD font_num = 0;
	if (AddFontMemResourceEx(Buffer, fontFileSize, NULL, &font_num) == 0)
	{
		OutputDebugString("フォントファイルが読み込めませんでした。\n");
		delete[] Buffer;
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
		return false;
	}

	FileRead_close(fontFileHandle);		//フォントファイルを閉じる
	delete[] Buffer;					//メモリ解放

	//フォントハンドルを生成
	fontHanble_ = CreateFontToHandle("ここにフォントファイル(.ttf)のファイルパス", fontSize_, fontWeight_, DX_FONTTYPE_ANTIALIASING_EDGE);
	if (fontHanble_ == -1)
	{
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
	}
	return(fontHanble_ != DX_DEFAULT_FONT_HANDLE);

}

//フォント更新処理
void StageUiFont::Update()
{
	if (fontHanble_ != -1 && fontHanble_ != DX_DEFAULT_FONT_HANDLE)
	{
		DeleteFontToHandle(fontHanble_);
	}
	fontHanble_ = CreateFontToHandle("ここにフォントファイル(.ttf)のファイルパス", fontSize_, fontWeight_, fontType_);
	if (fontHanble_ == -1)
	{
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
	}
}

//フォントサイズの設定
void StageUiFont::SetFontSize(int _fontSize)
{
	if (fontSize_ != _fontSize)
	{
		fontSize_ = _fontSize;
		Update();
	}
}

//フォントタイプの設定
void StageUiFont::SetFontType(int _fontType)
{
	if (fontType_ != _fontType)
	{
		fontType_ = _fontType;
		Update();
	}
}

//フォント太さの設定
void StageUiFont::SetFontWeight(int _fontWeight)
{
	if (fontWeight_ != _fontWeight)
	{
		fontWeight_ = _fontWeight;
		Update();
	}
}

//テキスト描画
void StageUiFont::DrawText(int _x, int _y, const char* _text, int _color, int _fontSize, int _fontType, int _fontWeight)
{
	SetFontSize(_fontSize);
	SetFontType(_fontType);
	SetFontWeight(_fontWeight);
	if (fontHanble_ != -1)
	{
		DrawFormatStringToHandle(_x, _y, _color, fontHanble_, _text);
	}
}