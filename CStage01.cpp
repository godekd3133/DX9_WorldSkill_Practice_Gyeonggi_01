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
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE02"), SPRITE("MAP_STAGE02_MINIMAP"), SPRITE("MAP_STAGE02_COLISIONMAP"));

	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();

	CGameObject * pUI = OBJ.Create("UI");
	pUI->ac<CPlayerUI>();


	GAME.m_pMap = pMap->gc<CStageMap>();
}

void CStage01::Update()
{
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

void CStage01::Render()
{
	GRAPHICS.Render_Font(to_string((INT)DXUTGetFPS()), GRAPHICS.ToMatrix(Vector3(100, 300, 0)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CStage01::Release()
{
}
