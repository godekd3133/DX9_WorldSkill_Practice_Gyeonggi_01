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
		AddMesh("MAP_STAGE01", "Map/Stage01/Stage01_2", "Map/Stage01");
		AddMesh("MAP_STAGE02", "Map/Stage02/Stage02", "Map/Stage02");

		AddMesh("PLAYER_IDLE", "Player/Idle/Idle", "Player/Idle", 32);
		AddMesh("PLAYER_RUN", "Player/Run/Run", "Player/Run", 23);
		AddMesh("PLAYER_JUMP", "Player/Jump/Jump", "Player/Jump", 35);
		AddMesh("PLAYER_HIT", "Player/Hit/Hit", "Player/Hit", 16);

		AddMesh("PLAYER_ATTACK_01", "Player/Attack01/Attack01", "Player/Attack01", 9);
		AddMesh("PLAYER_ATTACK_02", "Player/Attack02/Attack02", "Player/Attack02", 10);
		AddMesh("PLAYER_ATTACK_03", "Player/Attack03/Attack03", "Player/Attack03", 15);

		AddMesh("PLAYER_KICK_01", "Player/Kick01/Kick01", "Player/JumpKick", 16);
		AddMesh("PLAYER_KICK_02", "Player/Kick02/Kick02", "Player/JumpKick", 22);
		AddMesh("PLAYER_SKILL01", "Player/Skill01/Skill01", "Player/Skill01", 5);
		AddMesh("PLAYER_GROUNDPUNCH", "Player/GroundPunch/GroundPunch", "Player/GroundPunch", 25);
		//Enemy01

		//AddMesh("ENEMY01_ATTACK01", "Enemy/Enemy01/Attack01/Attack01", "Enemy/Enemy01/Attack01", 23);
		//AddMesh("ENEMY01_ATTACK02", "Enemy/Enemy01/Attack02/Attack02", "Enemy/Enemy01/Attack02", 23);
		//AddMesh("ENEMY01_HIT", "Enemy/Enemy01/Hit/Hit", "Enemy/Enemy01/Hit", 17);
		//AddMesh("ENEMY01_IDLE", "Enemy/Enemy01/Idle/Idle", "Enemy/Enemy01/Idle", 31);
		//AddMesh("ENEMY01_DEAD", "Enemy/Enemy01/KnockDown/KnockDown", "Enemy/Enemy01/KnockDown", 51);
		//AddMesh("ENEMY01_WALK", "Enemy/Enemy01/Walk/Walk", "Enemy/Enemy01/Walk", 31);
		//Enemy02

	//	AddMesh("ENEMY02_ATTACK01", "Enemy/Enemy02/Attack01/Attack01", "Enemy/Enemy02/Attack01", 67);
	//	AddMesh("ENEMY02_ATTACK02", "Enemy/Enemy02/Attack02/Attack02", "Enemy/Enemy02/Attack02", 56);
	//	AddMesh("ENEMY02_HIT", "Enemy/Enemy02/Hit/Hit", "Enemy/Enemy02/Hit", 56);

		AddSprite("EFFECT_SKILL01_HAND", "Effect/Skill01/Hand/Hand", 4);
		AddSprite("EFFECT_SKILL01_HIT", "Effect/Skill01/Hit/Hit", 5);
		AddSprite("EFFECT_SKILL01_PREPARE", "Effect/Skill01/Prepare/Prepare", 25);
		AddSprite("EFFECT_SKILL01_TRAIL", "Effect/Skill01/Trail/Trail", 6);

		AddSprite("EFFECT_SKILL02_SPLASH", "Effect/Skill02/Splash/Splash", 29);
		AddSprite("EFFECT_SKILL02_GROUND01", "Effect/Skill02/Ground01/Ground01", 6);
		AddSprite("EFFECT_SKILL02_GROUND02", "Effect/Skill02/Ground02/Ground02", 7);
		//AddMesh("ENEMY02_IDLE", "Enemy/Enemy02/Idle/Idle", "Enemy/Enemy02/Idle", 63);
		//AddMesh("ENEMY02_DEAD", "Enemy/Enemy02/Dead/Dead", "Enemy/Enemy02/Dead", 56);
		//AddMesh("ENEMY02_WALK", "Enemy/Enemy02/Walk/Walk", "Enemy/Enemy02/Walk", 41);
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
