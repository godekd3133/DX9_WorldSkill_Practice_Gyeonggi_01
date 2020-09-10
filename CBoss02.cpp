#include "DXUT.h"
#include "CBoss02.h"


CBoss02::CBoss02()
{
}


CBoss02::~CBoss02()
{
}

void CBoss02::Awake()
{
}

void CBoss02::Start()
{
	m_pPlayer = OBJ.Find(Tag::Player);
	m_pEnemy = gc<CEnemy>();
	m_State = Enemy_State::IDLE;
}

void CBoss02::Update()
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
					gc<CAnimator3D>()->SetCurrentState("ATTACK0" + to_string(my::RandRange(1, 4)));
					m_pEnemy->m_bStance = true;
					m_State = Enemy_State::ATTACK;
				}
			}
			else if (dist > 200)
				m_State = Enemy_State::CHASE;
			break;
		case Enemy_State::ATTACK:
		{
			if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK01" ||
				gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK02" ||
				gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK03")
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
			sa->Delay(1.5f);
			sa->Add([=]()->bool {go->Destroy(); GAME.Count++; return false; });

		}
	}
}

void CBoss02::LateUpdate()
{
}

void CBoss02::OnDestroy()
{
}

void CBoss02::OnCollision(CGameObject * _pObject)
{
}

void CBoss02::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(2.5f,2.5f, 2.5f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(15000, 500, 100, 1000, 500,25.f,0.15f, true);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("ATTACK01", "BOSS02_ATTACK01", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("ATTACK02", "BOSS02_ATTACK02", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("ATTACK03", "BOSS02_ATTACK03", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("DEAD", "BOSS02_DEAD", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("HIT",  "BOSS02_HIT", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("IDLE", "BOSS02_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->AddState("RUN",  "BOSS02_RUN", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
	gc<CAnimator3D>()->GetState("ATTACK01")->AddEvent(17, [=]() {gc<CEnemy>()->Attack(); });
	gc<CAnimator3D>()->GetState("ATTACK02")->AddEvent(16, [=]() {gc<CEnemy>()->Attack(); });
	gc<CAnimator3D>()->GetState("ATTACK03")->AddEvent(18, [=]() {gc<CEnemy>()->Attack(); });

}
