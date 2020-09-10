#include "DXUT.h"
#include "CEnemy03.h"


CEnemy03::CEnemy03()
{
}


CEnemy03::~CEnemy03()
{
}

void CEnemy03::Awake()
{
}

void CEnemy03::Start()
{
	m_pPlayer = OBJ.Find(Tag::Player);
	m_pEnemy = gc<CEnemy>();
	m_State = Enemy_State::IDLE;
}

void CEnemy03::Update()
{
	if (gc<CAnimator3D>()->GetCurrentState()->m_Name != "DEAD")
	{
		float dist = GetLength(tf->m_vPos, m_pPlayer->tf->m_vPos);
		switch (m_State)
		{
		case Enemy_State::IDLE:
			gc<CAnimator3D>()->SetCurrentState("IDLE");
			if (dist < 2000)
				m_State = Enemy_State::CHASE;


			break;
		case Enemy_State::CHASE:
			gc<CAnimator3D>()->SetCurrentState("RUN");
			if (dist <= 200)
				m_State = Enemy_State::ATTACK_PREPARE;
			else if (dist > 2500)
				m_State = Enemy_State::IDLE;
			else
			{
				m_pEnemy->Move(my::GetDirection(tf->m_vPos, m_pPlayer->tf->m_vPos));
				tf->LerpRotation(Vector3(0.f, my::GetDirAngle(my::GetDirection(tf->m_vPos, m_pPlayer->tf->m_vPos)), 0), 12.f * dt);

			}
			break;
		case Enemy_State::ATTACK_PREPARE:
			gc<CAnimator3D>()->SetCurrentState("IDLE");
			if (dist <= 200)
			{
				m_fAttackTime += dt;
				if (m_fAttackTime > m_fAttackDelay)
				{
					m_fAttackTime = 0.f;
					gc<CAnimator3D>()->SetCurrentState("ATTACK");
					m_pEnemy->m_bStance = true;
					m_State = Enemy_State::ATTACK;
				}
			}
			else if (dist > 200)
				m_State = Enemy_State::CHASE;
			break;
		case Enemy_State::ATTACK:
		{
			if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK")
			{
				if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
				{
					m_pEnemy->m_bStance = false;
					gc<CAnimator3D>()->SetCurrentState("IDLE");
					m_State = Enemy_State::IDLE;
				}
			}
		}

		}
	}
	else
	{
		if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
		{
			sa->Delay(0.5f);
			sa->Add([=]()->bool {go->Destroy(); GAME.Count++;  return false; });
			
		}
	}
}

void CEnemy03::LateUpdate()
{
}

void CEnemy03::OnDestroy()
{
}

void CEnemy03::OnCollision(CGameObject * _pObject)
{
}

void CEnemy03::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(3500, 60, 180, 900, 300, 10.f,0.75f,3);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("ATTACK", "ENEMY03_ATTACK", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("DEAD", "ENEMY03_DEAD", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("HIT", "ENEMY03_HIT", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("IDLE", "ENEMY03_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->AddState("RUN", "ENEMY03_RUN", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
	gc<CAnimator3D>()->GetState("ATTACK")->AddEvent(19, [=]() {gc<CEnemy>()->Attack(); });
}
