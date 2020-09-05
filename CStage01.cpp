#include "DXUT.h"
#include "CStage01.h"


CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Init()
{
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE01"), SPRITE("MAP_STAGE01_MINIMAP"), SPRITE("MAP_STAGE01_COLISIONMAP"));

	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();


	for (int i = 0; i < 10; i++)
	{
		CGameObject * pEnemy = OBJ.Create("SEX", Tag::Enemy);
		pEnemy->ac<CEnemy01>()->Init(Vector3(-2000, 10000, 2000));
		CGameObject * pEnemy1 = OBJ.Create("SEX", Tag::Enemy);
		pEnemy1->ac<CEnemy02>()->Init(Vector3(-1000, 10000, 2000));
		CGameObject * pEnemy2 = OBJ.Create("SEX", Tag::Enemy);
		pEnemy2->ac<CEnemy03>()->Init(Vector3(-4000, 10000, 2000));
		CGameObject * pEnemy3 = OBJ.Create("SEX", Tag::Enemy);
		pEnemy3->ac<CEnemy04>()->Init(Vector3(-5000, 10000, 2000));
	}
	GAME.m_pMap = pMap->gc<CStageMap>();
}

void CStage01::Update()
{
}

void CStage01::Render()
{
}

void CStage01::Release()
{
}
