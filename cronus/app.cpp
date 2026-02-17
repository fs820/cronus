//--------------------------------------------
//
// ゲームの本体 [app.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "entry.h"
#include "gui.h"
#include "log.h"
#include "window.h"
#include "title.h"

//---------------------------------
// Cronus (ゲーム本体)
//---------------------------------
class Cronus : public Application
{
public:
    Cronus() {}
    ~Cronus() = default;

    bool onStart() override;
    void onEnd() override;
    bool onUpdate(float elapsedTime, float deltaTime) override;
    bool onRender(const Renderer& renderer) override;
    bool onEvent(SDL_Event* event) override;

private:
};

//------------------------
// 開始
//------------------------
bool Cronus::onStart()
{
    spdlog::info("Cronusを開始します。"); // ログ出力

    getWindow()->setTitle("Cronus");                      // ウィンドウタイトルを設定

    getSceneManager()->addScene("Title", new TitleScene); // タイトルシーンを追加
    getSceneManager()->changeScene("Title");              // タイトルシーンに切り替え
    return true;
}

//------------------------
// 終了
//------------------------
void Cronus::onEnd()
{
    spdlog::info("Cronusを終了します。"); // ログ出力
}

//------------------------
// 更新
//------------------------
bool Cronus::onUpdate(float elapsedTime, float deltaTime)
{
#ifdef _DEBUG
    if (ImGui::Begin("Time")) // ウィンドウ開始
    {
        ImGui::Text("Elapsed Time: %.3f sec", elapsedTime);
        ImGui::Text("Delta Time: %.3f sec", deltaTime);
    }
    ImGui::End(); // ウィンドウ終了
#endif // _DEBUG
    return true;
}

//------------------------
// 描画
//------------------------
bool Cronus::onRender(const Renderer& renderer)
{
    return true;
}

//------------------------
// イベント
//------------------------
bool Cronus::onEvent(SDL_Event* event)
{
    return true;
}

//-------------------------------
// 生成
//-------------------------------
Application* CreateApplication()
{
    return new Cronus;
}
