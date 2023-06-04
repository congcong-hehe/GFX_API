#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "D3DApp.h"

class GameApp : public D3DApp
{
public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    virtual bool OnInit();
    virtual void OnUpdate(float dt/*一帧的时间*/);
    virtual void OnDraw();

    void OnResize();
};


#endif