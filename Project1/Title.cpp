﻿#include "Title.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "InputManger.h"
#include "NY_random.h"

using namespace myImgui;

Title::Title(ISceneChanger* changer) : BaseScene(changer) {


	titleMainSprite.Create(TexManager::LoadTexture("Resources/titr1.png"));
}

//初期化
void Title::Initialize() {

}

void Title::Finalize()
{

}

//更新
void Title::Update() {

}

//描画
void Title::Draw() {
	Raki_DX12B::Get()->StartDrawRenderTarget();
	Raki_DX12B::Get()->StartDrawBackbuffer();

	SpriteManager::Get()->SetCommonBeginDraw();
	titleMainSprite.DrawSprite(0, 0);
	titleMainSprite.Draw();


	/*ImguiMgr::Get()->StartDrawImgui("mouse", 150, 100);
	ImGui::Text("pos x : %f    y : %f", Input::getMousePos().x, Input::getMousePos().y);
	ImguiMgr::Get()->EndDrawImgui();*/

	// 描画処理
	//DrawGraph(0, 0, Back, true);
	//DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);


	//描画終了
	Raki_DX12B::Get()->CloseDraw();
}
