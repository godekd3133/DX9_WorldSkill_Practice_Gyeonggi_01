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
		else if (dist > 2500)
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

	//while (OBJ.IsCollision(_pObject->gc<CCollider>(), gc<CCollider>()))
	//{
	//	Vector3 _vDir = my::GetDirection(tf->m_vPos, _pObject->tf->m_vPos);
	//	tf->m_vPos += _vDir;
	//}
}

void CEnemy::OnHit(int _Damage)
{
}

bool CEnemy::Correction(Vector3 _vDir)
{
	CollisionInfo info;
	CollisionInfo info2;
	if (GAME.m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 50, 0), _vDir, 100, info) == true &&
		GAME.m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), _vDir, 50, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 0.f)
		{
			tf->m_vPos -= _vDir * 400 * dt;
			return true;

		}
	}
	return false;
}

bool CEnemy::Correction_Enemy(Vector3 _vDir)
{
	if (OBJ.RayCast(tf->GetWorldPos() + Vector3(0, 50, 0), _vDir,Tag::Enemy,50).empty() == false)
	{
		tf->m_vPos -= _vDir * 400 * dt;
		return true;
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
	if (abs(tf->m_vPos.y - m_pPlayer->tf->m_vPos.y) < 250)
		tf->m_vPos += _vDirection * 400 * dt;
	if (Correction(_vDirection)||
	Correction(Vector3(1, 0, 0))||
	Correction(Vector3(0.5f, 0, 0.5f))||
	Correction(Vector3(-0.5f, 0, 0.5f)))
	{
		if(abs(tf->m_vPos.y - m_pPlayer->tf->m_vPos.y) < 250)
		gc<CRigidBody>()->m_vVelocity = Vector3(0, 2500, 0);

	}

	Correction_Enemy(_vDirection);
	Correction_Enemy(Vector3(1, 0, 0));
	Correction_Enemy(Vector3(-1, 0, 0));
	Correction_Enemy(Vector3(0.5f, 0, 0.5f));
	Correction_Enemy(Vector3(-0.5f, 0, 0.5f));
	Correction_Enemy(Vector3(-0.5f, 0, -0.5f));
	Correction_Enemy(Vector3(0.f, 0, -1.f));
	Correction_Enemy(Vector3(0.5f, 0, -0.5f));
}
