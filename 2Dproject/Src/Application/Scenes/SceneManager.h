#pragma once

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

	


	void ImGuiUpdate();

private:
	
};