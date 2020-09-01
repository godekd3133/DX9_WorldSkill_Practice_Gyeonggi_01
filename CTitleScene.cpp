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
	pPlayer->tf->m_vPos = Vector3(0, 0, 0);
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
