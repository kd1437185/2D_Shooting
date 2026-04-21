#include "SceneManager.h"
#include "Title/Title.h"
#include "Game/Game.h"
#include "Result/Result.h"
#include "Application/main.h"
#include "Application/Ui/MousePointerUi.h"
#include "Application/Info/info.h"
#include"Application/Sound/Sound.h"
#include"../Ui/CommonTexture.h"
#include"Application/Ui/ConfirmationScreen.h"
#include"../Ui/Feed.h"


C_SceneManager::C_SceneManager()
{
}

C_SceneManager::~C_SceneManager()
{

}

void C_SceneManager::Init()
{
	//メモリ確保
	m_title = TitleAPP.GetO();
	m_game = GameAPP.GetO();
	m_result = Result.GetO();
	m_gameover = GameOverAPP.GetO();
	m_manual = ManualAPP.GetO();
	m_setting = SetingScreen.GetO();

	//オーナー(SceneManager)セット
	m_title->SetOwner(this);
	m_game->SetOwner(this);
	m_result->SetOwner(this);
	m_gameover->SetOwner(this);
	m_manual->SetOwner(this);
	ENDButton.SetOwner(this);
	m_setting->SetOwner(this);
	//共通テクスチャロード
	COMMONTEX.Load();

	//音量の初期化
	Info.VolInit();
	//Keyの初期化
	Info.PlayerKeyInit();
	SetingScreen.Init();
	SetingScreen.InitKeySet();

	//音読み込み
	Info.SoundInfoInit();
	Sound.SoundInit();

	//マウスクリック初期化
	m_MouseClickTex.Load("Texture/Mouse/Click.png");
	m_MouseClick.SetTex(&m_MouseClickTex);


	m_MousePointerTex.Load("Texture/Mouse/sprCursor.png");
	m_MousePointer.Init();
	m_MousePointer.SetTex(&m_MousePointerTex);
	ShowCursor(false);

	MouseClickParticleFlg = false;

	//タイトルからスタート
	ChangeScene(TITLE);

}

void C_SceneManager::Draw()
{
	//すべてのシーンの共通描画


	//タイトルでエフェクトを出す
	if (m_nowScene == m_title)
	{
		m_MousePointer.Draw();

		//クリックパーティクル
		m_MouseClick.Draw();
	}

	//設定画面なのか?
	//もし設定画面ならこのif分の中のみ描画
	if (m_nowScene->GetSettingScreenFlg())
	{
		//設定画面描画
		SetingScreen.Draw(scene);

		//クリックパーティクル
		m_MouseClick.Draw();

		m_MousePointer.Draw();

		Info.DrawKeyInfo();

		FEED.Draw();

		return;
	}




	//各シーンの描画処理

	if (m_nowScene == m_manual)
	{
		TitleAPP.DrawBack();
		m_nowScene->Draw();
	}
	else
	{
		m_nowScene->Draw();
	}


	FEED.Draw();

	//ゲーム画面かつマウス移動がオフかつショップじゃなかったら
	if (!Info.GetMouseMoveFlg() && m_nowScene == m_game && GameAPP.m_mode != ShopMode)
	{
		return;
	}

	m_MousePointer.Draw();

	//クリックパーティクル
	m_MouseClick.Draw();


	Info.DrawKeyInfo();
}

void C_SceneManager::Update()
{

	Info.SelectionModeChangeFlg = true;

	Info.KeyHit = false;

	//マウスの上が状態情報を初期化
	Info.m_isMouseOver = false;

	//各処理の中で初めにマウス座標を取る
	//マウス座標(スクロール処理無しのもの)を取っておく
	GetMousePos(&m_mouse);


	Info.UpdateKeyInfo();

	//マウスクリックパーティクル処理
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!MouseClickParticleFlg)
		{
			m_MouseClick.SetPraticle({ (float)m_mouse.x,(float)m_mouse.y }, { 0.0f,0.0f }, 15);
			Sound.MouseClickSound();
			MouseClickParticleFlg = true;
		}
	}
	else
	{
		MouseClickParticleFlg = false;
	}
	m_MouseClick.Update(m_mouse);


	//各シーンにマウス座標をセット
	m_nowScene->SetMouse(m_mouse);

	//設定画面なのかFlg情報をゲット
	//もし設定画面ならこのif分の中のみ処理
	if (m_nowScene->GetSettingScreenFlg())
	{
		//設定画面のFlg情報をセット
		m_nowScene->SettingScreenFlg(SetingScreen.Updata(m_mouse, &Info.mouseClickFlg, &Info.ESCFlg, scene));


		m_MousePointer.Update(m_mouse);

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			Info.f_ENTERKeyFlg = true;
			Info.f_ENTERKeyUseFlg = true;
		}

		return;
	}


	//各シーンの処理
	if (m_nowScene == m_manual)
	{
		TitleAPP.UpdateBack();
		m_nowScene->Update();
	}
	else
	{
		m_nowScene->Update();
	}

	//フェードエンドフラグ初期化
	FEED.SetFeedEnd(false);

	//マウスがどの常態か判別
	m_MousePointer.Update(m_mouse);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Info.f_ENTERKeyFlg = true;
		Info.f_ENTERKeyUseFlg = true;
	}
}

void C_SceneManager::Release()
{
	//共通テクスチャ解放
	COMMONTEX.Release();

	m_MouseClickTex.Release();
	m_MousePointerTex.Release();
	Info.PlayerKeySave();
	Info.VolSave();
}

void C_SceneManager::ChangeScene(SceneType type)
{
	if (type != MANUAL)
	{
		FEED.FeedInInit(40);
	}

	Info.m_KeyDrawFlg = true;

	scene = type;

	//引数で指定されたシーンをセットする
	switch (type)
	{
	case TITLE:
		Sound.StopBGM();
		Sound.TitleBGMSound();
		m_nowScene = m_title;
		break;
	case GAME:
		Sound.StopBGM();
		Sound.GameBGMSound();
		m_nowScene = m_game;
		break;
	case RESULT:
		Sound.AllSESoundStop();
		Sound.StopBGM();
		Sound.ResultBGMSound();
		m_nowScene = m_result;
		break;
	case GAMEOVER:
		Sound.StopBGM();
		m_nowScene = m_gameover;
		m_nowScene->Init();
		break;
	case MANUAL:
		if (Info.m_SettingKeyScreenFlg)
		{
			FEED.FeedInInit(40);
		}
		Info.m_SettingKeyScreenFlgkeep = Info.m_SettingKeyScreenFlg;
		m_PreviousScene = m_nowScene;
		m_nowScene = m_manual;
		m_nowScene->Init();
		break;
	}
}

void C_SceneManager::GoBackOneScene()
{
	if (Info.m_SettingKeyScreenFlgkeep)
	{
		FEED.FeedInInit(40);
	}
	if (m_PreviousScene != nullptr)
	{
		m_nowScene = m_PreviousScene;
		m_PreviousScene = nullptr;
	}
	//シーン遷移前設定画面だったなら
	if (Info.m_SettingKeyScreenFlgkeep)
	{
		Info.m_SettingKeyScreenFlg = true;
	}
}

void C_SceneManager::GetMousePos(POINT* mousePos)
{	//ディスプレイ状のマウス座標を取得(pc画面の左上が(0,0))
	GetCursorPos(mousePos);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上が(0,0))
	ScreenToClient(APP.m_window.GetWndHandle(), mousePos);

	//マウスの座標系を実行ウィンドウの座標敬(中心が(0,0)に補正)
	mousePos->x -= Info.ScrWidth / 2;
	mousePos->y -= Info.ScrHeight / 2;
	mousePos->y *= -1;
}


void C_SceneManager::ImGuiUpdate()
{
	float a = Info.m_mouse.x;
	float b = Info.m_mouse.y;
	ImGui::Text(u8"マウス座標 X%.2f", a);
	ImGui::Text(u8"マウス座標 Y%.2f", b);

	SetingScreen.ImGuiUPdate();

	m_nowScene->ImGuiUpdate();
}