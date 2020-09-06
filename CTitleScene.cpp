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
	CGameObject * Pivot = OBJ.Create();
	Pivot->tf->m_vPos = Vector3(-5000, -700, 2500);

	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE01"), SPRITE("MAP_STAGE01_MINIMAP"), SPRITE("MAP_STAGE01_COLISIONMAP"));

	CAMERA.Follow(Pivot, 800);
	CAMERA.m_vRotation = Vector2(50, 0);

}

void CTitleScene::Update()
{
	CAMERA.m_vRotation += Vector2(0, 40) * dt;
}

void CTitleScene::Render()
{
}

void CTitleScene::Release()
{
}
