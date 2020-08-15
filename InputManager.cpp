#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    memcpy(LastInput, CurInput, sizeof(LastInput));
    
    for (int i = 0; i < 256; i++)
    {
        CurInput[i] = GetAsyncKeyState(i);
    }
}

bool InputManager::KeyDown(int _Key)
{
    return CurInput[_Key] && LastInput[_Key] == false;
}

bool InputManager::KeyUp(int _Key)
{
    return CurInput[_Key] == false && LastInput[_Key] == true;
}

bool InputManager::KeyPrss(int _Key)
{
    return CurInput[_Key] && LastInput[_Key];
}
