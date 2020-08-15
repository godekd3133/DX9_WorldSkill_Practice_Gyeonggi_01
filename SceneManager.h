#pragma once
#include "Singleton.h"
#include "Scene.h"
class SceneManager :
    public Singleton< SceneManager>
{
public:
    SceneManager();
    ~SceneManager();

private:
    map<string, Scene*> mapScene;
   
    Scene* CurrentScene;
    Scene* NextScene;
public:
    void AddScene(string _Key, Scene* _Scene);
    void ChangeScene(string _Key);

public:
    void Update();
    void Render();
};

