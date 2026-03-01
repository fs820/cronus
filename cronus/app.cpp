//--------------------------------------------
//
// ゲームの本体 [app.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "entry.h"
#include "game_loader.h"
#include "binary_stream.h"
#include "gui.h"
#include "log.h"
#include "window.h"
#include "title.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"

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
    bool onEvent(SDL_Event* event) override;

private:
};

//------------------------
// 開始
//------------------------
bool Cronus::onStart()
{
    spdlog::info("Cronusを開始します。"); // ログ出力

    // Cursorの変更をImGuiにさせないようにする
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    getWindow()->setIcon("bmp/ICON/icon.bmp");       // アイコンの設定
    getWindow()->setCursor("bmp/CURSOR/cursor.bmp"); // カーソルの設定

    Config config = file::loadConfig("data/custom.yaml");          // 設定ファイルの読み込み
    getWindow()->setTitle(config.title.c_str());                   // ウィンドウタイトルを設定
    getWindow()->setSize(config.windowWidth, config.windowHeight); // ウィンドウタイトルを設定

    getRenderer()->setPostProcessShaderMask(PostProcessShaderMask::FXAA | PostProcessShaderMask::Bloom); // アンチエイリアスとブルームを行う
    getRenderer()->setToneMappingType(ToneMappingType::Anime);                                           // アニメ調の色彩

    getTextureManager()->registerPath(Hash("logo"), u8"data/TEXTURE/test.png");
    getTextureManager()->load(1);
    getRenderer()->uploadTextures(*getTextureManager(), 1);

    getSceneManager()->addScene("Title", new TitleScene(this)); // タイトルシーンを追加
    getSceneManager()->changeScene("Title");                    // タイトルシーンに切り替え
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

    static float testValue = 0.0f;
    BinaryReader reader("data/test.bin");
    if(reader.isValid()) testValue = reader.read<float>();

    if (ImGui::Begin("File")) // ウィンドウ開始
    {
        ImGui::SliderFloat("test", &testValue, 0.0f, 1.0f);
    }
    ImGui::End(); // ウィンドウ終了
    BinaryWriter writer("data/test.bin");
    writer.write(testValue);

    static bool testInput = false;
    if (getInput()->isActionPressed(ActionCode::Attack, 0)) testInput = !testInput; // 入力のテスト
    if (ImGui::Begin("Input")) // ウィンドウ開始
    {
        ImGui::Checkbox("test", &testInput);
    }
    ImGui::End(); // ウィンドウ終了
#endif // _DEBUG
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
