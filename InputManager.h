#pragma once
#include "Singleton.h"
class InputManager :
    public Singleton< InputManager>
{
public:
    InputManager();
    ~InputManager();

public:
    bool CurInput[256] = { 0, };
    bool LastInput[256] = { 0, };

public:
    void Update();
    bool KeyDown(int _Key);
    bool KeyUp(int _Key);
    bool KeyPrss(int _Key);
};

#define INPUT (*InputManager::GetInstance())
