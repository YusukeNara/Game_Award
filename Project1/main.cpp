﻿#include "Raki_DX12B.h"
#include "FPS.h"
#include "Audio.h"
#include "TexManager.h"

#include "NY_Object3DMgr.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "Raki_imguiMgr.h"

#include "ActFlag.h"
#include "InputManger.h"
#include "RenderTargetManager.h"
#include "SChangeDir.h"

using namespace DirectX;
using namespace Microsoft::WRL;

//-----------RakiEngine_Alpha.ver-----------//


//コンソール表示用エントリーポイント切り替え
//Releaseでもコンソールしたい場合、プロパティ->リンカー->サブシステムをコンソールに切り替えてから、WinMainをmainにする
#ifdef _DEBUG
int main()
#else
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{

#pragma region GameValue

    Raki_WinAPI *rakiWinApp;
    rakiWinApp = new Raki_WinAPI;
    rakiWinApp->CreateGameWindow();

    Raki_DX12B::Get()->Initialize(rakiWinApp);

    myImgui::InitializeImGui(Raki_DX12B::Get()->GetDevice(), Raki_WinAPI::GetHWND());

    //オブジェクト管理
    NY_Object3DManager::Get()->CreateObject3DManager();
    SpriteManager::Get()->CreateSpriteManager(Raki_DX12B::Get()->GetDevice(), Raki_DX12B::Get()->GetGCommandList(),
        rakiWinApp->window_width, rakiWinApp->window_height);

    TexManager::InitTexManager();

    //マウスを使えるようにする
    ActFlag::SetMouseFlag(false);

    //音
    Audio::Init();

    //シーン管理
    SceneManager *smgr;
    smgr = new SceneManager;

    SChangeDir::Get()->Init();
    SChangeDir::Get()->PlayChangedDirection();

#pragma endregion GameValue

    FPS::Get()->Start();

    while (true)  // ゲームループ
    {
        if (rakiWinApp->ProcessMessage()) { break; }

        //更新
        InputManger::Update();

        if (smgr->isEndApp()) { break; }

        smgr->Update();

        SChangeDir::Get()->Update();

#ifdef _DEBUG
        if (InputManger::Get()->Escape())
        {
            break;
        }
#endif //_DEBUG

        RenderTargetManager::GetInstance()->CrearAndStartDraw();

        smgr->Draw();

        SChangeDir::Get()->Draw();

        RenderTargetManager::GetInstance()->SwapChainBufferFlip();

        FPS::Get()->run();
    }

    smgr->Finalize();

    //imgui終了
    myImgui::FinalizeImGui();

    // ウィンドウクラスを登録解除
    rakiWinApp->DeleteGameWindow();

    delete smgr;
    smgr = nullptr;
    delete rakiWinApp;
    rakiWinApp = nullptr;

    return 0;
}


