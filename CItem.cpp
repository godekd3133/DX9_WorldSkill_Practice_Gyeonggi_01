#include "DXUT.h"
#include "CItem.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Awake()
{
}

void CItem::Start()
{
}

void CItem::Update()
{
	if(abs(tf->m_vPos.y - GAME.m_pPlayer->tf->m_vPos.y) < 200 )
	if (my::GetLength(GAME.m_pPlayer->tf->m_vPos, tf->m_vPos) < 700)
	{
		tf->MoveToward(Vector3(GAME.m_pPlayer->tf->m_vPos.x,tf->m_vPos.y, GAME.m_pPlayer->tf->m_vPos.z),2000 * dt);
	}
}

void CItem::LateUpdate()
{
}

void CItem::OnDestroy()
{
}

void CItem::OnCollision(CGameObject * _pObject)
{
	if (_pObject->m_Tag == Tag::Player)
	{

		if (m_Kind == ItemKind::IK_ITEM)
		{
			GRAPHICS.dPlay("ITEM");
			if(RandRange(0,100) > 50)
				GAME.GainHp(GAME.GetMaxHp() *0.2f);
			else
				GAME.GainExp(GAME.MaxExp *0.2f);

		}
		else if (m_Kind == ItemKind::IK_EXP)
		{
			GRAPHICS.dPlay("EXP");
			GAME.GainExp(250+ GAME.MaxExp * RandRange(1, 10)/ 100.f);
		}
		else if (m_Kind == ItemKind::IK_COIN)
		{
			GRAPHICS.dPlay("COIN");
			GAME.Score += 400;
		}
		go->Destroy();
	}
}

void CItem::Init(ItemKind _Kind, Vector3 _vPos)
{
	tf->m_vPos = _vPos;
	go->m_Tag = Tag::Item;
	m_Kind = _Kind;
	ac<CRigidBody>()->AddForce(Vector3(0, 2000,0));
	gc<CRigidBody>()->Offset = 100.f;
	ac<CCollider>()->Init(150);

	if (_Kind == ItemKind::IK_ITEM)
		ac<CMeshRenderer>()->Init(MESH("ITEM"));
	else if (_Kind == ItemKind::IK_EXP)
	{
		tf->m_vScale = Vector3(5, 5, 5);
		ac<CMeshRenderer>()->Init(MESH("EXP"));

	}
	else if (_Kind == ItemKind::IK_COIN)
	{
		tf->m_vScale = Vector3(5, 5, 5);
		ac<CMeshRenderer>()->Init(MESH("COIN"));
	}
}

