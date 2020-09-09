#include "DXUT.h"
#include "CBoss01.h"


CBoss01::CBoss01()
{
}


CBoss01::~CBoss01()
{
}

void CBoss01::Awake()
{
}

void CBoss01::Start()
{
	m_pPlayer = OBJ.Find(Tag::Player);
	m_pEnemy = gc<CEnemy>();
	m_State = Enemy_State::IDLE;

}

void CBoss01::Update()
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
					gc<CAnimator3D>()->SetCurrentState("ATTACK0" + to_string(my::RandRange(1,4)));
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
				gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK03" )
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

void CBoss01::LateUpdate()
{
}

void CBoss01::OnDestroy()
{
}

void CBoss01::OnCollision(CGameObject * _pObject)
{
}

void CBoss01::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(150.f, 150.f, 150.f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(30000, 30, 100, 800, 500, 50.f,0.4f, true);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("ATTACK01", "BOSS01_ATTACK01", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("ATTACK02", "BOSS01_ATTACK02", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("ATTACK03", "BOSS01_ATTACK03", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("DEAD", "BOSS01_DEAD", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("HIT",  "BOSS01_HIT", 30.F / 1000.F, FALSE);
	gc<CAnimator3D>()->AddState("IDLE", "BOSS01_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->AddState("RUN",  "BOSS01_RUN", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
	gc<CAnimator3D>()->GetState("ATTACK01")->AddEvent(16, [=]() {gc<CEnemy>()->Attack(); });
	gc<CAnimator3D>()->GetState("ATTACK02")->AddEvent(19, [=]() {gc<CEnemy>()->Attack(); });
	gc<CAnimator3D>()->GetState("ATTACK03")->AddEvent(27, [=]() {gc<CEnemy>()->Attack(); });

}
