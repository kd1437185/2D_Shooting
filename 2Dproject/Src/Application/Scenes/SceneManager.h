#pragma once
//シーンのベース
#include"SceneBase.h"


//マウスパーティクル
#include "Application/Praticle/MouseClick.h"

//マウスカーソル
#include "Application/Ui/MousePointerUi.h"


//////////////////////////////////////
//各シーンの実体を管理するクラス
//////////////////////////////////////

//前方宣言
class C_Title;
class C_Game;
class C_Result;
class C_GameOver;
class C_Manual;
class C_SettingKeyScreen;

class C_SceneManager
{
public:

	C_SceneManager();
	~C_SceneManager();



	void Init();
	void Draw();
	void Update();
	void Release();

	//マウス処理スクロール無し
	void GetMousePos(POINT* mousePos);

	//シーン切り替え関数
	void ChangeScene(SceneType type);
	//ひとつ前のシーンに戻る
	void GoBackOneScene();


	void ImGuiUpdate();

private:
	//現在のシーンを持たせる(SceneBaseを継承した子クラスのアドレスが入る)
	SceneBase* m_nowScene;
	//１つ前のシーンを保存する
	SceneBase* m_PreviousScene;

	SceneType scene;

	//各シーンのインスタンス
	C_Title* m_title;
	C_Game* m_game;
	C_Result* m_result;
	C_GameOver* m_gameover;
	C_Manual* m_manual;
	C_SettingKeyScreen* m_setting;
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//マウス関係

	//マウス座標(POINT...メンバにxとyを持つ型)
	POINT m_mouse;

	//クリックしたときのパーティクル画像
	KdTexture m_MouseClickTex;

	//クリックしたときのパーティクルインスタンス
	C_MouseClick m_MouseClick;

	//マウスカーソル画像
	KdTexture m_MousePointerTex;
	C_MousePointerUi m_MousePointer;

	bool MouseClickParticleFlg;

	bool ClickFlg;
};