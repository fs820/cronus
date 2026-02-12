//--------------------------------------------
//
// アプリケーション [application.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once

//---------------------------------------------------------------------
// アプリケーションクラス
// SDLのエントリーポイントにより生成され各MainSystemを持つ基底クラス
// これを継承し各ゲームのmainのクラスを作成する
//---------------------------------------------------------------------
class Application
{
public:
    Application() {}
    ~Application() = default;

    bool init(int argc, char* argv[]);
    void uninit();
    SDL_AppResult update();
    SDL_AppResult handleEvent(SDL_Event* event);

private:
};
