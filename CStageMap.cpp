#include "DXUT.h"
#include "CStageMap.h"


CStageMap::CStageMap()
{
}


CStageMap::~CStageMap()
{
}

void CStageMap::Awake()
{
}

void CStageMap::Start()
{
	//m_pPlayer = OBJ.Create();
	//m_pPlayer->ac<CSpriteRenderer>()->Init(SPRITE("MAP_STAGE01_PLAYER"), SortingLayer::SR_Effect, RenderMode::RM_UI);
	

}

void CStageMap::Update()
{
	//Vector3 _vPos = OBJ.Find(Tag::Player)->tf->GetWorldPos();
	//int PosX = (INT)(-_vPos.x / 10.f);
	//int PosY = (INT)(_vPos.z / 10.f);
	//m_pPlayer->tf->m_vPos = Vector3(PosX, PosY, 0.f);
}

void CStageMap::LateUpdate()
{
}

void CStageMap::OnDestroy()
{
}

void CStageMap::OnCollision()
{
}

void CStageMap::Init(CMesh * _pMesh, CSprite * _pMinimap, CSprite * _pCollisionMap)
{
	m_pMesh = _pMesh;
	m_pMinimap = _pMinimap;
	m_pCollisionMap = _pCollisionMap;
	ac<CMeshRenderer>()->Init(m_pMesh);
	CGameObject * pMinimap = OBJ.Create();
	//pMinimap->ac<CSpriteRenderer>()->Init(_pCollisionMap, SortingLayer::SR_Default, RenderMode::RM_UI);
	//pMinimap->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	tf->m_vScale = Vector3(-1.f, 1.f, 1.f);
	tf->m_vPos = Vector3(0, 0, 0);
}

MapCollision CStageMap::GetCollisionInfoByCollisionMap(Vector3 _vPos)
{
	D3DLOCKED_RECT lR;
	m_pCollisionMap->m_pTexture->LockRect(0, &lR, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lR.pBits);
	
	int PosX = (INT)(-_vPos.x /  10.f);
	int PosY = (INT)(_vPos.z / 10.f);
	

	if (PosX < 0 || PosX > m_pCollisionMap->m_Info.Width ||
		PosY < 0 || PosY > m_pCollisionMap->m_Info.Height)
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}

	D3DXCOLOR color = dwColor[(PosY * m_pCollisionMap->m_Info.Width ) + PosX];
//	dwColor[(PosY * m_pCollisionMap->m_Info.Width) + PosX] = Color(1, 1, 1, 1);
	OutputDebugStringA(("r : " + to_string(color.r) + " g : "  + to_string(color.g) + " b : " + to_string(color.b) + " a : " + to_string(color.a) + "\n").c_str());
	OutputDebugStringA(("X : " + to_string(PosX) + "Y" + to_string(PosY) +  "\n").c_str());

	if (color == Color(1, 0, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Wall;
	}
	else if (color == Color(1, 1, 0, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::Between;
	}
	else if (color == Color(0, 1, 1, 1))
	{
		m_pCollisionMap->m_pTexture->UnlockRect(0);
		return MapCollision::SecondFloor;
	}
	m_pCollisionMap->m_pTexture->UnlockRect(0);
	return MapCollision::FirstFloor;
}

