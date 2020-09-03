#include "DXUT.h"
#include "CMainGame.h"
#include "CTitleScene.h"

CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{

	std::future<void> a =
		std::async(launch::async, [=]() {
		AddMesh("MAP_STAGE01", "Map/Stage01/Stage01", "Map/Stage01");
		AddMesh("PLAYER_IDLE", "Player/Animation/Attack01/Attack01", "Player",1);
	
		AddMesh("ENEMY01_IDLE", "Enemy01/Animation/Idle/Idle", "Enemy01", 1);
		AddMesh("ENEMY02_IDLE", "Enemy02/Animation/Idle/Idle", "Enemy02", 1);
		AddMesh("ENEMY03_IDLE", "Enemy03/Animation/Idle/Idle", "Enemy03", 1);
		AddMesh("ENEMY04_IDLE", "Enemy04/Animation/Idle/Idle", "Enemy04", 1);

		//	AddMesh("MAP_STAGE02", "Map/Stage02/Stage02", "Map/Stage02");
		AddSprite("MAP_STAGE01_COLISIONMAP", "Map/Stage01/NormalMap copy");
		AddSprite("MAP_STAGE01_PLAYER", "Map/Stage01/Player");
	});

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.ChangeScene("S_TITLE");

}

void CMainGame::Update()
{

	INPUT.Update();

	SCENE.Update();

	OBJ.Update();

	CAMERA.Update();
}

void CMainGame::Render()
{

	CAMERA.SetTransform();

	SCENE.Render();

	OBJ.Render();
}

void CMainGame::Release()
{
	CInputManager::ReleaseInstance();
	CGraphicsManager::ReleaseInstance();
	CSceneManager::ReleaseInstance();
	CObjectManager::ReleaseInstance();
	CCameraManager::ReleaseInstance();
}

void CMainGame::OnLostDevice()
{
	GRAPHICS.OnLostDevice();
}

void CMainGame::OnResetDevice()
{
	GRAPHICS.OnResetDevice();
}

void CMainGame::AddSprite(string _Key, string _Path, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".png";
		GRAPHICS.AddSprite(Key, Path);
		OutputDebugStringA((Key + "\n").c_str());
	}
	else
	{
		for (int i = 0; i < _Count; i++)
		{
			string Key = _Key + " (" + to_string(i + 1) + ")";
			string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").png";
			GRAPHICS.AddSprite(Key, Path);
			OutputDebugStringA((Key + "\n").c_str());

		}
	}
}

void CMainGame::AddMesh(string _Key, string _Path, string _MapPath, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".obj";
		string MapPath = "./resource/" + _MapPath + "/";
		GRAPHICS.AddMesh(Key, Path, MapPath);
//	OutputDebugStringA((Key + "\n").c_str());
	}
	else
	{
			for (int i = 0; i < _Count; i++)
		{


					string Key = _Key + " (" + to_string(i + 1) + ")";
					string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
					string MapPath = "./resource/" + _MapPath + "/";
					GRAPHICS.AddMesh(Key, Path, MapPath);
		//			OutputDebugStringA((Key + "\n").c_str());
		}

	}
}
