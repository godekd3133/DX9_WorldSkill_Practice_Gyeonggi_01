#include "DXUT.h"
#include "CEnemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Awake()
{
}

void CEnemy::Start()
{
	m_pPlayer = OBJ.Find(Tag::Player);
	m_State = Enemy_State::IDLE;
}

void CEnemy::Update()
{
	float dist = GetLength(tf->m_vPos, m_pPlayer->tf->m_vPos);
	switch (m_State)
	{
	case Enemy_State::IDLE: 
		if (dist < 2000)
			m_State = Enemy_State::CHASE;


		break;
	case Enemy_State::CHASE:
		if (dist <= 200)
			m_State = Enemy_State::ATTACK;
		else if( dist > 2500)
			m_State = Enemy_State::IDLE;
		else
			Move(my::GetDirection(tf->m_vPos, m_pPlayer->tf->m_vPos));
		break;
	case Enemy_State::ATTACK:
		if (dist <= 200)
			m_State = Enemy_State::ATTACK;
		else if (dist > 600)
			m_State = Enemy_State::CHASE;
		break;
	}


}

void CEnemy::LateUpdate()
{
}

void CEnemy::OnDestroy()
{
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
}

void CEnemy::OnHit(int _Damage)
{
}

bool CEnemy::Correction(Vector3 _vDir)
{
	CollisionInfo info;
	CollisionInfo info2;
	if (GAME.m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 100, 0), _vDir, 200, info) == true &&
		GAME.m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), _vDir, 120, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= _vDir * 400 * dt;
			return true;

		}
	}
	return false;
}

void CEnemy::Init(int _MaxHp, int _Damage, int _Size)
{
	go->m_Tag = Tag::Enemy;
	ac<CCollider>()->Init(_Size);
	m_iCurHp = _MaxHp;
	m_iMaxHp = _MaxHp;
	m_iDamage = _Damage;
}

void CEnemy::Move(Vector3 _vDirection)
{
	tf->m_vPos += _vDirection * 400 * dt;
	if (Correction(_vDirection))
		gc<CRigidBody>()->AddForce(Vector3(0, 3000, 0));

}
