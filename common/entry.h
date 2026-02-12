//--------------------------------------------
//
// エントリーポイント [entry.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#define SDL_MAIN_USE_CALLBACKS 1 // エントリーポイントをSDLに任せる
#include <SDL3/SDL_main.h>       // SLDのエントリーポイントなどのコールバックを定義するためのh
#include "application.h"         // アプリケーションクラス

// 必ず実装しなければならない関数
// アプリケーションクラスを継承したゲームのmainクラスのインスタンスを生成する
extern Application* CreateApplication();

// SDLのエントリーポイント定義

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    // ユーザー定義の関数を呼んでアプリを生成
    Application* app = CreateApplication();
    *appstate = app;

    if (!app || !app->init(argc, argv))
    {
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    Application* app = (Application*)appstate;
    return app->update();
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    Application* app = (Application*)appstate;
    return app->handleEvent(event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    if (appstate) {
        Application* app = (Application*)appstate;
        app->uninit();
        delete app;
    }
}
