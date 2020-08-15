#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	CurrentScene = nullptr;
	NextScene = nullptr;
}

SceneManager::~SceneManager()
{
	for (auto iter : mapScene)
	{
		iter->second->Release();
		SAFE_DELETE(iter->second);
	}
	mapScene.clear();
}

void SceneManager::AddScene(string _Key, Scene* _Scene)
{
}

void SceneManager::ChangeScene(string _Key)
{
	NextScene = mapScene[_Key];
}

void SceneManager::Update()
{
	if (CurrentScene)
		CurrentScene->Update();

	if (NextScene)
	{
		if (CurrentScene)
			CurrentScene->Release();
		NextScene->Init();
		CurrentScene = NextScene;
		NextScene = nullptr;
	}
}

void SceneManager::Render()
{
	if (CurrentScene)
		CurrentScene->Render();
}
