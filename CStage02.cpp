#include "DXUT.h"
#include "CStage02.h"
#include "CPlayerUI.h"


CStage02::CStage02()
{
}


CStage02::~CStage02()
{
}

void CStage02::Init()
{
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE02"), SPRITE("UI_MINIMAP_STAGE02"), SPRITE("MAP_STAGE02_COLISIONMAP"));
	GAME.m_pMap = pMap->gc<CStageMap>();
	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();
	GAME.m_pPlayer = pPlayer;
	CGameObject * pUI = OBJ.Create("UI");
	pUI->ac<CPlayerUI>();


	GAME.m_pMap = pMap->gc<CStageMap>();
	GAME.Quest = 2;
}

void CStage02::Update()
{
	if (GAME.Quest == 2)
	{
		if (GAME.Count >= 100)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CBoss02>()->Init(Vector3(-2000, 10000, 2000));
			GAME.Quest++;
			GAME.Count = 0;
		}
	}
	if (GAME.Quest == 3)
	{
		if (GAME.Count >= 1)
		{
			GAME.Quest++;
			GAME.Count = 0;
			SCENE.ChangeScene("S_GAMECLEAR");
		}
	}
	if (INPUT.KeyDown('1'))
	{
		for (int i = 0; i < 10; i++)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CEnemy01>()->Init(Vector3(-2000, 10000, 2000));
		}
	}
	if (INPUT.KeyDown('2'))
	{
		for (int i = 0; i < 10; i++)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CEnemy02>()->Init(Vector3(-2000, 10000, 2000));
		}
	}

	if (INPUT.KeyDown('3'))
	{
		for (int i = 0; i < 10; i++)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CEnemy03>()->Init(Vector3(-2000, 10000, 2000));

		}
	}

	if (INPUT.KeyDown('4'))
	{
		for (int i = 0; i < 10; i++)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CEnemy04>()->Init(Vector3(-2000, 10000, 2000));
		}
	}


}

void CStage02::Render()
{
}

void CStage02::Release()
{
}
