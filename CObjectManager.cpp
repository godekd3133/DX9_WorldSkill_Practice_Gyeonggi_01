#include "DXUT.h"
#include "CObjectManager.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
	for (auto iter : m_listGameObject)
	{
		for (auto comp : iter->m_listComponent)
		{
			comp->OnDestroy();
		}
		for (auto comp2 : iter->m_listComponent)
		{
			SAFE_DELETE(comp2);
		}
		iter->m_listComponent.clear();

		SAFE_DELETE(iter);
	}
	m_listGameObject.clear();
}

void CObjectManager::Update()
{
	for (auto iter : m_listGameObject)
	{
		for (auto comp : iter->m_listComponent)
		{
			if (comp->m_bStart == false)
			{
				comp->m_bStart = true;
				comp->Start();
			}
		}

		if (iter->m_bEnable)
			for (auto comp : iter->m_listComponent)
			{
				if (comp->m_bEnable)
				{
					comp->sa->Update();
				comp->Update();

				}
			}
	}

	for (auto iter : m_listGameObject)
	{
		if (iter->m_bEnable)
			for (auto comp : iter->m_listComponent)
			{
				if (comp->m_bEnable)
					comp->LateUpdate();
			}
	}

	for (auto iter = m_listGameObject.begin(); iter != m_listGameObject.end(); )
	{
		if ((*iter)->m_bDestroy == true)
		{

			for (auto comp : (*iter)->m_listComponent)
			{
				comp->OnDestroy();
			
			}
			SAFE_DELETE(*iter);
			iter = m_listGameObject.erase(iter);
		}
		else iter++;
	}
}

void CObjectManager::Render()
{
	for (auto iter : m_listRenderer3D)
	{
		if(iter->go->m_Tag == Tag::Map)
		g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		if (iter->m_bEnable)
		{
			iter->OnRender();
		}
		g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	}

	m_listRenderer2D.sort([](CRenderer2D * _Prev, CRenderer2D * _Next)->bool {
		return (int)_Prev->m_SortingLayer < (int)_Next->m_SortingLayer;
	});

	for (auto iter : m_listRenderer2D)
	{
		if (iter->m_bEnable)
			iter->OnRender();
	}
}

CGameObject * CObjectManager::Create(string _Name, Tag _Tag)
{
	CGameObject * pObject = new CGameObject();
	pObject->m_Tag = _Tag;
	pObject->m_Name = _Name;
	pObject->tf = pObject->ac<CTransform>();

	m_listGameObject.push_back(pObject);
	return pObject;
}

bool CObjectManager::IsCollision(CCollider * _Prev, CCollider * _Next)
{
	return my::GetLength(_Prev->tf->GetWorldPos(), _Next->tf->GetWorldPos()) < _Prev->m_fRadius + _Next->m_fRadius;
}

CGameObject * CObjectManager::Find(string _Name)
{
	for (auto iter : m_listGameObject)
		if (iter->m_Name == _Name)
			return iter;
	return nullptr;
}

CGameObject * CObjectManager::Find(Tag _Tag)
{
	for (auto iter : m_listGameObject)
		if (iter->m_Tag == _Tag)
			return iter;
	return nullptr;
}

list <CGameObject * > CObjectManager::Finds(string _Name)
{
	list <CGameObject * > listFind;
	for (auto iter : m_listGameObject)
		if (iter->m_Name == _Name)
			listFind.push_back(iter);
	return listFind;
}

list <CGameObject * >CObjectManager::Finds(Tag _Tag)
{
	list <CGameObject*> listFind;
	for (auto iter : m_listGameObject)
		if (iter->m_Tag == _Tag)
			listFind.push_back(iter);
	return listFind;
}

bool CObjectManager::RayCast(CMeshRenderer * _pTarget, Vector3 _vPos, Vector3 _vDirection, float _fDistance, CollisionInfo& _Info)
{
	D3DXVECTOR3		vPickRayDir = _vDirection;				// Pick ray direction	
	D3DXVECTOR3		vPickRayOrig = _vPos;				// Pick ray origin
	D3DXVECTOR3					v;				// Vector used in computation	
	D3DXMATRIXA16				matProj;		// Retrieved projection matrix	
	D3DXMATRIXA16				matView, m;		// Retrieved view and computation matrices
	POINT						ptCursor;		// Cursor position	
	D3DXVECTOR3					vNear, vDir;
	D3DXMATRIX					invMat;
	BOOL						bHit;
	DWORD						dwIndex;
	float						uCoord, vCoord;
	float						dist;
	//LPDIRECT3DSURFACE9			pBackBuffer = NULL;
	//D3DSURFACE_DESC				Desc;	// Error check	
	//g_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//pBackBuffer->GetDesc(&Desc);
	//pBackBuffer->Release();	// Get the projection matrix

	D3DXMatrixInverse(&invMat, NULL, &_pTarget->tf->ToMatrix());
	D3DXVec3TransformCoord(&vNear, &vPickRayOrig, &invMat);
	D3DXVec3TransformNormal(&vDir, &vPickRayDir, &invMat);	// Test for intersection	
	

	D3DXIntersect(_pTarget->m_pMesh->m_pMesh, &vNear, &vDir, &bHit, &dwIndex, &uCoord, &vCoord, &dist, NULL, NULL);
	if (bHit == TRUE)
	{
		if (_fDistance == -1.f)
		{
				_Info.distance = dist;
				_Info.vPos = _vPos + _vDirection * dist;

			return TRUE;
		}
		else
		{
			if (dist <= _fDistance)
			{
				_Info.distance = dist;
				_Info.vPos = _vPos + _vDirection * dist;
				return true;
			}
		}

	}
		return FALSE;
}
