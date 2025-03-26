#pragma once
#include<DxLib.h>
#include<string>

class StageUiFont
{
private:
	static StageUiFont* instance_;    //シングルトンインスタンス
	int fontHanble_;				  //フォントハンドル
	int fontSize_;                    //フォントサイズ
	int fontType_;					  //フォントタイプ
	int fontWeight_;				  //フォントの太さ
	StageUiFont();					  //コンストラクタはプライベート
public:
	//フォントの値
	static constexpr int FONT_TYPE_NORMAL = DX_FONTTYPE_NORMAL;                             //通常のフォント
	static constexpr int FONT_TYPE_EDGE = DX_FONTTYPE_EDGE;                                 //縁取りフォント
	static constexpr int FONT_TYPE_ANTIALIASING = DX_FONTTYPE_ANTIALIASING;                 //アンチエイリアスフォント
	static constexpr int FONT_TYPE_ANTIALIASING_EDGE = DX_FONTTYPE_ANTIALIASING_EDGE;       //アンチエイリアス + 縁取りフォント

	~StageUiFont();					  //デストラクタ
	static StageUiFont& GetInstance();//インスタンス取得
	bool Init();					  //フォントの初期化
	void Update();					  //フォント更新処理
	void SetFontSize(int _fontSize);  //フォントサイズの設定	
	void SetFontType(int _fontType);  //フォントタイプの設定
	void SetFontWeight(int _fontWeight);//フォントの太さ設定
	void DrawText(int _x, int _y, const char* _text, int _color, int _fontSize, int _fontType, int _fontWeight);//テキスト描画
};