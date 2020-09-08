#include "DXUT.h"
#include "CStage01.h"
#include "CPlayerUI.h"

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Init()
{
	GAME.Reset();
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE01"), SPRITE("UI_MINIMAP_STAGE01"), SPRITE("MAP_STAGE01_COLISIONMAP"));
	GAME.m_pMap = pMap->gc<CStageMap>();
	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();
	GAME.m_pPlayer = pPlayer;
	CGameObject * pUI = OBJ.Create("UI");
	pUI->ac<CPlayerUI>();


	GAME.m_pMap = pMap->gc<CStageMap>();
}

void CStage01::Update()
{

	if (GAME.Quest == 0)
	{
		if (GAME.Count >= 100)
		{
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CBoss01>()->Init(Vector3(-2000, 10000, 2000));
			GAME.Quest++;
			GAME.Count = 0;
		}
	}
	if (GAME.Quest == 1)
	{
		if (GAME.Count >= 1)
		{
			GAME.Quest++;
			GAME.Count = 0;
			SCENE.ChangeScene("S_STAGECLEAR");
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

	if (INPUT.KeyDown('5'))
	{
	}
	if (INPUT.KeyDown('6'))
	{
	}

}

void CStage01::Render()
{
	GRAPHICS.Render_Font(to_string((INT)DXUTGetFPS()), GRAPHICS.ToMatrix(Vector3(100, 300, 0)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CStage01::Release()
{
}
