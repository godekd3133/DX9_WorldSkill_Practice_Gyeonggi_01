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
//	{
	if (_pObject->m_Tag == Tag::Enemy)
	{


		Vector3 _vDir = my::GetDirection(tf->m_vPos, _pObject->tf->m_vPos);
		_vDir.y = 0.f;

		if (_vDir.x == 0.f && _vDir.z == 0.f)
		{
			_vDir.x = my::RandRange(-100, 100) / 100.f;
			_vDir.z = my::RandRange(-100, 100) / 100.f;
		}

		Move(-_vDir);
	}
		//	}
}

void CEnemy::OnHit(int _Damage)
{
}

bool CEnemy::Correction(Vector3 _vDir)
{
	if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos + _vDir * 5) == MapCollision::Wall ||
		tf->m_vPos.y < GAME.m_pMap->GetFloorY(tf->m_vPos + _vDir * 5))
		{
		tf->m_vPos -= _vDir * m_fMoveSpeed * dt;
		return true;
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

void CEnemy::Init(int _MaxHp, int _Damage, int _Size, float _fMoveSpeed)
{
	go->m_Tag = Tag::Enemy;
	ac<CCollider>()->Init(_Size);
	m_iCurHp = _MaxHp;
	m_fMoveSpeed = _fMoveSpeed;
	m_iMaxHp = _MaxHp;
	m_iDamage = _Damage;
}

void CEnemy::Move(Vector3 _vDirection)
{
	_vDirection.y = 0.f;
	bool x = false;
	bool y = false;
	if (abs(tf->m_vPos.y - m_pPlayer->tf->m_vPos.y) < 250)
	{
		Vector3 OldPos = tf->m_vPos;
		tf->m_vPos += Vector3(_vDirection.x,0,0)* m_fMoveSpeed * dt;

		if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall ||
			GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Between )
		{
			if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Between  && 
				GAME.m_pMap->GetCollisionInfoByCollisionMap(OldPos) == MapCollision::FirstFloor)
				gc<CRigidBody>()->m_vVelocity = Vector3(0, 2500, 0);

			if (tf->m_vPos.y < GAME.m_pMap->GetFloorY(tf->m_vPos))
			{
				tf->m_vPos.x = OldPos.x;
				x = true;
			}
		}

		OldPos = tf->m_vPos;
		tf->m_vPos += Vector3(0, 0, _vDirection.z)* m_fMoveSpeed * dt;

		if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall ||
			GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Between)
		{
			if (GAME.m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Between  &&
				GAME.m_pMap->GetCollisionInfoByCollisionMap(OldPos) == MapCollision::FirstFloor)
				gc<CRigidBody>()->m_vVelocity = Vector3(0, 2500, 0);

			if (tf->m_vPos.y < GAME.m_pMap->GetFloorY(tf->m_vPos))
			{
				tf->m_vPos.z = OldPos.z;
				y = true;
			}
		}
	}
	//if (x == true)
	//	Move(Vector3(_vDirection.x, 0, 0));
	//if(y == true)
	//	Move(Vector3(0, 0, _vDirection.z));

	//Correction_Enemy(_vDirection);
	//Correction_Enemy(Vector3(1, 0, 0));
	//Correction_Enemy(Vector3(-1, 0, 0));
	//Correction_Enemy(Vector3(0.5f, 0, 0.5f));
	//Correction_Enemy(Vector3(-0.5f, 0, 0.5f));
	//Correction_Enemy(Vector3(-0.5f, 0, -0.5f));
	//Correction_Enemy(Vector3(0.f, 0, -1.f));
	//Correction_Enemy(Vector3(0.5f, 0, -0.5f));
}
