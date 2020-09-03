#include "DXUT.h"
#include "CTitleScene.h"
#include "CPlayerMovement.h"

CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	CGameObject * pMap = OBJ.Create("Map",Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE01"), nullptr, SPRITE("MAP_STAGE01_COLISIONMAP"));

	CGameObject * pPlayer = OBJ.Create("Player",Tag::Player);
	pPlayer->ac<CPlayerMovement>();
	

	CGameObject * pEnemy = OBJ.Create();
	pEnemy->ac<CEnemy01>()->Init(Vector3(-3000,10000,2000));
	GAME.m_pMap = pMap->gc<CStageMap>();
}

void CTitleScene::Update()
{
}

void CTitleScene::Render()
{
}

void CTitleScene::Release()
{
}
