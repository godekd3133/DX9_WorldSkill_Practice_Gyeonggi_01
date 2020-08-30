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
	pMap->ac<CMeshRenderer>()->Init(MESH("MAP_STAGE01"));
	pMap->tf->m_vScale = Vector3(-0.5f, 0.5f, 0.5f);
	pMap->tf->m_quatRotation = QuatEular(Vector3(0, 180, 0));
	pMap->tf->m_vPos = Vector3(0,0, 400);

	CGameObject * pPlayer = OBJ.Create();
	pPlayer->ac<CPlayerMovement>();
	pPlayer->tf->m_vPos = Vector3(0, 0, 500);
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
