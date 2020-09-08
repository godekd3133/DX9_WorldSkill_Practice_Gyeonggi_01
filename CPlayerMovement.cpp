#include "DXUT.h"
#include "CPlayerMovement.h"
CPlayerMovement::CPlayerMovement()
{
}


CPlayerMovement::~CPlayerMovement()
{
}

void CPlayerMovement::Awake()
{
	ac<CRigidBody>()->OnLanding.push_back([=]() {OnLanding(); });
	m_pMap = OBJ.Find(Tag::Map)->gc<CStageMap>();
	tf->m_vScale = Vector3(1.5, 1.5, 1.5);
	tf->m_vPos = Vector3(-2000,-200, 3000);
	ac<CMeshRenderer>()->Init(MESH("PLAYER"));

	ac<CAnimator3D>()->AddState("IDLE", "PLAYER_IDLE",30.f / 1000.f);
	gc<CAnimator3D>()->AddState("RUN", "PLAYER_RUN", 30.f / 1000.f);
	gc<CAnimator3D>()->AddState("ATTACK01", "PLAYER_ATTACK01", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("ATTACK02", "PLAYER_ATTACK02", 30.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("SKILL01", "PLAYER_ATTACK04", 25.f / 1000.f, false);
	gc<CAnimator3D>()->AddState("SKILL02", "PLAYER_ATTACK05",25.f / 1000.f, false);


	gc<CAnimator3D>()->SetCurrentState("IDLE");


	gc<CAnimator3D>()->GetState("ATTACK01")->AddEvent(4, [=]() {OnAttack01_Event();});
	gc<CAnimator3D>()->GetState("ATTACK01")->AddEvent(11, [=]() {OnAttack01_Event(); });
	gc<CAnimator3D>()->GetState("ATTACK02")->AddEvent(7, [=]() {OnAttack02_Event(); });
	gc<CAnimator3D>()->GetState("SKILL01")->AddEvent(15, [=]() {OnSkill01_Event(); });
	gc<CAnimator3D>()->GetState("SKILL02")->AddEvent(31, [=]() {OnSkill02_Event(); 	});
}

void CPlayerMovement::Start()
{
	CAMERA.Follow(go,1200.f);


	m_pShadow = OBJ.Create();
	m_pShadow->ac<CSpriteRenderer>()->Init(SPRITE("UI_SHADOW"), SortingLayer::SR_UI, RenderMode::RM_Default);
	m_pShadow->tf->SetRotation(Vector3(90, 0, 0));
}

void CPlayerMovement::Update()
{
	//Animation Various;
	bool bMove = false;
	bool bAttack = false;
	bool bSkill01 = false;
	bool bSkill02 = false;
	Vector3 MoveDirection = Vector3(0, 0, 0);

	if (INPUT.KeyPress('W'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Foward];
	else if (INPUT.KeyPress('S'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Back];
	if (INPUT.KeyPress('A'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Left];
	else if (INPUT.KeyPress('D'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Right];
	


	if (INPUT.KeyDown(VK_SPACE) && Jump == 0)
	{
		if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "IDLE" ||
			gc<CAnimator3D>()->GetCurrentState()->m_Name == "RUN")
		{
			gc<CRigidBody>()->AddForce(Vector3(0, 2000, 0));
			Jump++;
		}

	}
	if (INPUT.KeyDown(VK_LBUTTON))
		bAttack =true;
	if (INPUT.KeyDown('Q') && Jump == 0)
	{

			bSkill02 = true;
	}
	if (INPUT.KeyDown(VK_LSHIFT) && Jump == 0)
	{
			bSkill01 = true;
	}
	if (MoveDirection != Vector3(0, 0, 0))
		bMove = true;

	CAMERA.m_fDistance = Lerp(CAMERA.m_fDistance, m_fDistance, 6 * dt);
	CAMERA.m_vOffset = Lerp(CAMERA.m_vOffset, Vector3(0.f, 0.f, 600.f), 6 * dt);

	if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "IDLE")
	{
		if (bMove == true)
		{
			gc<CAnimator3D>()->SetCurrentState("RUN");
		}
		if (bAttack)
		{
			gc<CAnimator3D>()->SetCurrentState("ATTACK01");
		}
		if (bSkill01)
		{
		//	if (GAME.Skill01Timer >GAME.Skill01CoolTime)
			{
			//	GAME.Skill01Timer = 0.f;
				go->gc<CRigidBody>()->m_vImpulse = Vector3(0.35f, 0.f, 0.35f);
				gc<CRigidBody>()->m_vVelocity = ((CAMERA.m_vCharactorAxis[Axis::Foward] * 2000) + (Vector3(0, 1, 0) * 1000));
				gc<CAnimator3D>()->SetCurrentState("SKILL01");
			}
		}
		if (bSkill02)
		{
		//	if (GAME.Skill02Timer > GAME.Skill02CoolTime)
			{
			//	GAME.Skill02Timer = 0.f;
				go->gc<CRigidBody>()->m_vImpulse = Vector3(0.35f, 0.f, 0.35f);
				gc<CRigidBody>()->m_vVelocity = ((CAMERA.m_vCharactorAxis[Axis::Foward] * 1000) + (Vector3(0, 1, 0) * 2000));


				gc<CAnimator3D>()->SetCurrentState("SKILL02");
			}
		}
	}
	else if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "RUN")
	{
		Move(MoveDirection, 1000.F);
		tf->LerpRotation(Vector3(0, my::GetDirAngle(MoveDirection), 0), 12.f * dt);
		if (bMove == false)
		{
			gc<CAnimator3D>()->SetCurrentState("IDLE");
		}
		if (bAttack)
		{
			gc<CAnimator3D>()->SetCurrentState("ATTACK01");
		}
		if (bSkill01)
		{
			if (GAME.Skill01Timer >GAME.Skill01CoolTime)
			{
				GAME.Skill01Timer = 0.f;	
				go->gc<CRigidBody>()->m_vImpulse = Vector3(0.35f, 0.f, 0.35f);
				gc<CRigidBody>()->m_vVelocity = ((CAMERA.m_vCharactorAxis[Axis::Foward] * 2000) + (Vector3(0, 1, 0) * 1000));
				gc<CAnimator3D>()->SetCurrentState("SKILL01");
			}
		}
		if (bSkill02)
		{
 			if (GAME.Skill02Timer >GAME.Skill02CoolTime)
			{
				GAME.Skill02Timer = 0.f;
				go->gc<CRigidBody>()->m_vImpulse = Vector3(0.35f, 0.f, 0.35f);
				gc<CRigidBody>()->m_vVelocity = ((CAMERA.m_vCharactorAxis[Axis::Foward] * 1000) + (Vector3(0, 1, 0) * 2000));


				gc<CAnimator3D>()->SetCurrentState("SKILL02");
			}
		}

	}
	else if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK01")
	{
		if (bAttack == true)
			TriggerAttackCombo = true;

		tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]),0)); 
		if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
		{
			if (TriggerAttackCombo == true)
			{
				TriggerAttackCombo = false;
				gc<CAnimator3D>()->SetCurrentState("ATTACK02");
			}
			else 
			gc<CAnimator3D>()->SetCurrentState("IDLE");
		}

	}
	else if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "ATTACK02")
	{
		tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0));
		if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
		{
			gc<CAnimator3D>()->SetCurrentState("IDLE");
		}
	}
	
	else if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "SKILL01")
	{
	
			tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0));
			if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
			{
				gc<CAnimator3D>()->SetCurrentState("IDLE");
			}
	}

	else if (gc<CAnimator3D>()->GetCurrentState()->m_Name == "SKILL02")
	{

			tf->SetRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]), 0));
			if (gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime() >= 0.99f)
			{
				gc<CAnimator3D>()->SetCurrentState("IDLE");
			}
	}


	m_pShadow->tf->m_vPos = Vector3(tf->m_vPos.x, GAME.m_pMap->GetFloorY(tf->m_vPos) + 1, tf->m_vPos.z);

	float scale = 100.f / max(abs(GAME.m_pMap->GetFloorY(tf->m_vPos) - tf->m_vPos.y), 100);
	m_pShadow->tf->m_vScale = Vector3(scale, scale, 1.f);
}

void CPlayerMovement::LateUpdate()
{
}

void CPlayerMovement::OnDestroy()
{
	m_pShadow->Destroy();
}

void CPlayerMovement::OnCollision(CGameObject * _pObject)
{
}

void CPlayerMovement::Move(Vector3 _vDirection, float _MoveSpeed)
{
	Vector3 OldPos = tf->m_vPos;
	tf->m_vPos += Vector3(0.f, 0, _vDirection.z)  * _MoveSpeed * dt;

	if (m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall ||
		tf->m_vPos.y < m_pMap->GetFloorY(tf->m_vPos))
	{
		tf->m_vPos = OldPos;
	}

	 OldPos = tf->m_vPos;
	tf->m_vPos +=Vector3( _vDirection.x,0,0) * _MoveSpeed * dt;
	
	if (m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall ||
		tf->m_vPos.y < m_pMap->GetFloorY(tf->m_vPos))
	{
		tf->m_vPos = OldPos;
	}

	/*CollisionInfo info;
	CollisionInfo info2;
	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Left], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::Left], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::Left] * _MoveSpeed * dt;
			return;

		}
	}
	
	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Right], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::Right], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::Right] * _MoveSpeed * dt;
			return;

		}
	}

	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Foward], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::Foward], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::Foward] * _MoveSpeed * dt;
			return;

		}
	}

	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Back], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::Back], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::Back] * _MoveSpeed * dt;
			return;

		}
	}

	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::LF], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::LF], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::LF] * _MoveSpeed * dt;
			return;

		}
	}

	if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::RF], 150, info) == true &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 10, 0), CAMERA.m_vCharactorAxis[Axis::RF], 100, info2) == true)
	{
		float dis = info.vPos.z - info2.vPos.z;
		if (abs(dis) > 1)
		{
			tf->m_vPos -= CAMERA.m_vCharactorAxis[Axis::RF] * _MoveSpeed * dt;
			return;

		}
	}
	CAMERA.m_vCharactorDir = Vector3(0,0,0);
	CollisionInfo info3;
		if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 100, 0), Vector3(_vDirection.x, 0, 0), _MoveSpeed * dt + 10, info3) == false   )
		{
			tf->m_vPos.x += _vDirection.x * _MoveSpeed * dt;
			CAMERA.m_vCharactorDir.x = _vDirection.x;
		}
		if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 100, 0), Vector3(0, 0, _vDirection.z), _MoveSpeed * dt + 10, info3) == false  )
		{
			tf->m_vPos.z += _vDirection.z * _MoveSpeed * dt;
			CAMERA.m_vCharactorDir.z = _vDirection.z;
		}				
		*/
}

void CPlayerMovement::OnLanding()
{
	Jump = 0;
}

void CPlayerMovement::OnStopSkill01Rush()
{
	HandEffect->Destroy();
	HandEffect = nullptr;
}

void CPlayerMovement::OnAttack01_Event()
{
	Vector3 vDir = CAMERA.m_vCharactorAxis[Axis::Foward];
	float fDistance = 200;
	float fFinalDamage = m_fAttackDamage * my::RandRange(90,110)/ 100.f;
	
	go->gc<CRigidBody>()->m_vVelocity.x = vDir.x * 2400;
	go->gc<CRigidBody>()->m_vVelocity.z = vDir.z * 2400;
	go->gc<CRigidBody>()->m_vImpulse = Vector3(15.f, 0.f, 15.f);

	list<CGameObject *> listHitObject = OBJ.GetCollisionObject(this->tf->m_vPos + vDir * 50, 150, Tag::Enemy);//OBJ.RayCast(this->tf->m_vPos , vDir, Tag::Enemy,fDistance);

	for (auto iter : listHitObject)
	{
		if (iter->gc<CEnemy>()->m_bIsDead == false)
		{
			iter->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) * 500 + vDir *500* my::RandRange(4, 6);
			iter->gc<CEnemy>()->OnHit((int)fFinalDamage, vDir);
			EFFECT(iter->tf->m_vPos + Vector3(0, 100, 0), Vector3(0.25f, 0.25f, 0.25f), "EFFECT_PLAYERATTACK01");
		}
	}
}

void CPlayerMovement::OnAttack02_Event()
{
	Vector3 vDir = CAMERA.m_vCharactorAxis[Axis::Foward];
	float fDistance = 200;
	float fFinalDamage = m_fAttackDamage * my::RandRange(90, 110) / 100.f;

	go->gc<CRigidBody>()->m_vVelocity.x = vDir.x * 2800;
	go->gc<CRigidBody>()->m_vVelocity.z = vDir.z *2800;
	go->gc<CRigidBody>()->m_vImpulse = Vector3(15.f, 0.f, 15.f);


	list<CGameObject *> listHitObject = OBJ.GetCollisionObject(this->tf->m_vPos + vDir * 50, 150, Tag::Enemy);//OBJ.RayCast(this->tf->m_vPos , vDir, Tag::Enemy,fDistance);

	for (auto iter : listHitObject)
	{
		if (iter->gc<CEnemy>()->m_bIsDead == false)
		{
			iter->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) * 800 + vDir * 500 * my::RandRange(5, 9);
			iter->gc<CEnemy>()->OnHit((int)fFinalDamage, vDir);
			EFFECT(iter->tf->m_vPos + Vector3(0, 100, 0), Vector3(0.25f, 0.25f, 0.25f), "EFFECT_PLAYERATTACK02");
		}
	}
}

void CPlayerMovement::OnSkill01_Event()
{
	gc<CRigidBody>()->m_vVelocity = Vector3(0, 0, 0);
	Vector3 vDir = CAMERA.m_vCharactorAxis[Axis::Foward];
	float fDistance = 200;
	float fFinalDamage = m_fAttackDamage * my::RandRange(90, 110) / 100.f;

	list<CGameObject *> listHitObject = OBJ.GetCollisionObject(this->tf->m_vPos + vDir * 50, 150, Tag::Enemy);//OBJ.RayCast(this->tf->m_vPos , vDir, Tag::Enemy,fDistance);

	for (auto iter : listHitObject)
	{
		if (iter->gc<CEnemy>()->m_bIsDead == false)
		{
			iter->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) *400 + my::GetDirection(tf->m_vPos, iter->tf->m_vPos) * 2000;
			iter->gc<CEnemy>()->OnHit((int)fFinalDamage, vDir);
			EFFECT(iter->tf->m_vPos + Vector3(0, 100, 0), Vector3(0.25f, 0.25f, 0.25f), "EFFECT_PLAYERATTACK02");
		}
	}
	CGameObject * Effect = OBJ.Create();
	Effect->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
	Effect->ac<CEffect>()->Init("EFFECT_PLAYERSKILL02", 0.1f, tf->m_vPos + Vector3(0, 30, 0) + vDir * 200);
	Effect->gc<CSpriteRenderer>()->m_RenderMode = RenderMode::RM_Billboard;
	Effect->tf->SetRotation(Vector3(0, 0, 0));

}

void CPlayerMovement::OnSkill02_Event()
{
	gc<CRigidBody>()->m_vVelocity = Vector3(0, 0, 0);
	Vector3 vDir = CAMERA.m_vCharactorAxis[Axis::Foward];
	float fDistance = 200;
	float fFinalDamage = m_fAttackDamage * my::RandRange(90, 110) / 100.f;




	list<CGameObject *> listHitObject = OBJ.GetCollisionObject(this->tf->m_vPos + vDir * 50, 150, Tag::Enemy);//OBJ.RayCast(this->tf->m_vPos , vDir, Tag::Enemy,fDistance);

	for (auto iter : listHitObject)
	{
		if (iter->gc<CEnemy>()->m_bIsDead == false)
		{
			iter->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) * 900 + my::GetDirection(tf->m_vPos, iter->tf->m_vPos) * 5000;


			iter->gc<CEnemy>()->OnHit((int)fFinalDamage, vDir);
			EFFECT(iter->tf->m_vPos + Vector3(0, 100, 0), Vector3(0.25f, 0.25f, 0.25f), "EFFECT_PLAYERATTACK02");
		}
	}
	CGameObject * Effect = OBJ.Create(); 
	Effect->tf->m_vScale = Vector3(0.5f,0.5f,0.5f);
	Effect->ac<CEffect>()->Init("EFFECT_PLAYERSKILL02", 0.1f, tf->m_vPos + Vector3(0,30,0) + vDir * 200);
	Effect->gc<CSpriteRenderer>()->m_RenderMode = RenderMode::RM_Billboard;
	Effect->tf->SetRotation(Vector3(0, 0, 0));

}

