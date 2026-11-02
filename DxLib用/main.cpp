/*
   - main.cpp - (KrLib_Dx用)
   ver.2026/10/14

   プログラムの開始テンプレ.
*/
#include "KrLib_Dx/KR_Global.h"
#include "KrLib_Dx/KR_App.h"
#include "KrLib_Dx/KR_Debug.h"
#include "KrLib_Dx/KR_Input.h"
#include "KrLib_Dx/KR_Object.h"
#include "KrLib_Dx/KR_ObjectList.h"
#include "KrLib_Dx/KR_ManagerBase.h"
#include "KrLib_Dx/KR_ManagerInsts.h"
#include "KrLib_Dx/KR_SceneMng.h"
#include "KrLib_Dx/KR_Sound.h"
#include "KrLib_Dx/KR_TimerMng.h"
using namespace KR;

/*
   [オブジェクト]
   ObjectCirやObjectBoxを継承することを推奨.
   ObjectListで管理することで、配列でのオブジェクト管理がしやすくなる.
*/
class Object : public ObjectCir
{
private:
public:
	//初期化.
	void Init() override {
	}
	//更新.
	void Update() override {
		Debug::Log(_T("test"));
	}
	//描画.
	void Draw() override {
	}
	//消滅条件(必要なら設定)
	bool IsErase() const override {
		return false;
	}
};

/*
   [管理クラス]
   必ずManagerBaseを継承する.
   ManagerInstsにこのクラスを登録することで、自動実行されるようになる.
*/
class GameManager : public ManagerBase
{
private:
	ObjectList<Object> objects;

public:
	//コンストラクタ.
	GameManager(){}

	//初期化.
	void Init() override {
		//オブジェクト生成.
		objects.NewObject();
	}
	//リセット.
	void Reset() override {
	}
	//更新.
	void Update() override {
		//オブジェクト更新.
		objects.Update();
	}
	//描画.
	void Draw() override {
		//オブジェクト描画.
		objects.Draw();
	}
};

int WINAPI WinMain(
	_In_     HINSTANCE hinstance,
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
){
	/*
	   [管理クラス生成]
	   生成した順にInitやUpdateなどが自動で実行される.
	*/
	//KrLibに実装されている管理クラスを登録.
	ManagerInsts::NewManager<InputMng>();
	ManagerInsts::NewManager<SoundMng>();
	ManagerInsts::NewManager<SceneMng>();
	ManagerInsts::NewManager<TimerMng>();
	//それ以外の管理クラスを登録.
	ManagerInsts::NewManager<GameManager>();

	//初期化処理.
	App::InitDx(800, 640, true, 60, false);
	//ループ処理.
	App::LoopDx();

	return 0;
}