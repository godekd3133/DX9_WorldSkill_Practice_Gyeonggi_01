#include "DXUT.h"
#include "CObjectManager.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
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
		if ((*iter)->m_bDestroy)
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
