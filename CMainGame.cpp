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
	thread th = thread([=]() {
		AddMesh("MAP_STAGE01", "Map/Stage01/Stage01", "Map/Stage01");
		AddMesh("MAP_STAGE02", "Map/Stage02/Stage02", "Map/Stage02");
		AddMesh("PLAYER_ATTACK_01", "Player/Attack01/Attack01", "Player/Attack01", 9);
		AddMesh("PLAYER_ATTACK_02", "Player/Attack02/Attack02", "Player/Attack02", 10);
		AddMesh("PLAYER_ATTACK_03", "Player/Attack03/Attack03", "Player/Attack03", 15);

		AddMesh("PLAYER_IDLE", "Player/Idle/Idle", "Player/Idle", 32);
//		AddMesh("PLAYER_ATTACK_01", "Player/Attack01/Attack01", "Player/Attack01", 9);
	});

	th.join();
	//AddMesh("PLAYER_ATTACK_02", "Player/Attack02/Attack02", "Player/Attack02", 10);
	//AddMesh("PLAYER_ATTACK_03", "Player/Attack03/Attack03", "Player/Attack03", 15);

	//AddMesh("PLAYER_GROUNDKICK", "Player/GroundKick/GroundKick", "Player/GroundKick", 33);
	//AddMesh("PLAYER_GROUNDPUNCH", "Player/GroundPunch/GroundPunch", "Player/GroundPunch", 25);
	//AddMesh("PLAYER_HIT", "Player/Hit/Hit", "Player/Hit", 16);
	//AddMesh("PLAYER_IDLE", "Player/Idle/Idle", "Player/Idle", 32);
	//AddMesh("PLAYER_JUMP", "Player/Jump/Jump", "Player/Jump", 35);
	//AddMesh("PLAYER_JUMPKICK", "Player/JumpKick/JumpKick", "Player/JumpKick", 26);
	//AddMesh("PLAYER_KICK_01", "Player/Kick01/Kick01", "Player/JumpKick", 16);
	//AddMesh("PLAYER_KICK_02", "Player/Kick02/Kick02", "Player/JumpKick", 22);
	//AddMesh("PLAYER_RUN", "Player/Run/Run", "Player/Run", 23);
	//AddMesh("PLAYER_WALK", "Player/Walk/Walk", "Player/Walk", 31);

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.ChangeScene("S_TITLE");

}

void CMainGame::Update()
{
	CAMERA.Update();

	CAMERA.Update();

	SCENE.Update();

	INPUT->Update();

	OBJ.Update();
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
		string Path = _Path + ".png";
		GRAPHICS.AddSprite(_Key, _Path);
	}
	else
	{
		for (int i = 0; i < _Count; i++)
		{
			string Key = _Key + " (" + to_string(i + 1) + ")";
			string Path = _Path + " (" + to_string(i + 1) + ").png";
			GRAPHICS.AddSprite(Key, Path);
		}
	}
}

void CMainGame::AddMesh(string _Key, string _Path, string _MapPath, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" +  _Path + ".obj";
		string MapPath = "./resource/" +  _MapPath + "/";
		GRAPHICS.AddMesh(Key, Path, MapPath);
	}
	else
	{
		for (int i = 0; i < _Count; i++)
		{
			string Key = _Key + " (" + to_string(i + 1)  + ")";
			string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
			string MapPath = "./resource/" + _MapPath + "/";
			GRAPHICS.AddMesh(Key, Path,MapPath);
		}
	}
}
