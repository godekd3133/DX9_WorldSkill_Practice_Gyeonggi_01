#include "DXUT.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CStage01.h"
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
	
		AddMesh("PLAYER_IDLE", "Player/Animation/Idle/Idle", "Player",41);
		AddMesh("PLAYER_RUN", "Player/Animation/Run/Run", "Player", 15);
		AddMesh("PLAYER_HIT", "Player/Animation/Hit/Hit", "Player", 11);
//		AddMesh("PLAYER_DEAD", "Player/Animation/Dead/Dead", "Player",36);
		AddMesh("PLAYER_ATTACK01", "Player/Animation/Attack01/Attack01", "Player", 16);
		AddMesh("PLAYER_ATTACK02", "Player/Animation/Attack02/Attack02", "Player", 16);
		AddMesh("PLAYER_ATTACK03", "Player/Animation/Attack03/Attack03", "Player", 24);
		AddMesh("PLAYER_ATTACK04", "Player/Animation/Attack04/Attack04", "Player", 28);
		AddMesh("PLAYER_ATTACK05", "Player/Animation/Attack05/Attack05", "Player", 51);
		AddMesh("PLAYER_ATTACK06", "Player/Animation/Attack06/Attack06", "Player", 31);
		AddMesh("PLAYER_ATTACK07", "Player/Animation/Attack07/Attack07", "Player", 32);


		AddMesh("ENEMY01_IDLE", "Enemy01/Animation/Idle/Idle", "Enemy01", 41);
		AddMesh("ENEMY02_IDLE", "Enemy02/Animation/Idle/Idle", "Enemy02", 61);
		AddMesh("ENEMY03_IDLE", "Enemy03/Animation/Idle/Idle", "Enemy03", 61);
		AddMesh("ENEMY04_IDLE", "Enemy04/Animation/Idle/Idle", "Enemy04", 51);

		//	AddMesh("MAP_STAGE02", "Map/Stage02/Stage02", "Map/Stage02");
		AddSprite("MAP_STAGE01_COLISIONMAP", "Map/Stage01/NormalMap copy");
		AddSprite("MAP_STAGE01_MINIMAP", "Map/Stage01/NormalMap");
		AddSprite("MAP_STAGE01_PLAYER", "Map/Stage01/Player");


		AddSprite("EFFECT_PLAYERATTACK01", "Effect/PlayerAttack01/PlayerAttack01", 5);
		AddSprite("EFFECT_PLAYERATTACK02", "Effect/PlayerAttack02/PlayerAttack02", 5);
		AddSprite("EFFECT_PLAYERSKILL02", "Effect/PlayerSkill02/PlayerSkill02", 7);
	});

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.AddScene("S_STAGE01", new CStage01());
	SCENE.ChangeScene("S_STAGE01");

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
