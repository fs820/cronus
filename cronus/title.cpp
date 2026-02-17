//--------------------------------------------
//
// タイトル [title.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "title.h"
#include "gui.h"

//-----------------------------
// 
// タイトルシーン
// 
//-----------------------------

//------------------------
// シーンに入るときの処理
//------------------------
void TitleScene::onEnter()
{
}

//------------------------
// シーンから出るときの処理
//------------------------
void TitleScene::onExit()
{
}

//------------------------
// 更新処理
//------------------------
void TitleScene::update(float elapsedTime, float deltaTime)
{
#ifdef _DEBUG
    if (ImGui::Begin("Title Scene")) // ウィンドウ開始
    {
        ImGui::Text("This is the Title Scene.");
    }
    ImGui::End(); // ウィンドウ終了
#endif // _DEBUG
}

//------------------------
// 描画処理
//------------------------
void TitleScene::render(const Renderer& renderer)
{

}
