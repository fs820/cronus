//--------------------------------------------
//
// ゲームの本体 [app.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "entry.h"

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
    return true;
}

//------------------------
// 終了
//------------------------
void Cronus::onEnd()
{

}

//------------------------
// 更新
//------------------------
bool Cronus::onUpdate(float elapsedTime, float deltaTime)
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
