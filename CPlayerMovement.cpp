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

	ac<CMeshRenderer>()->Init(MESH("PLAYER_ATTACK_01 (1)"));
	ac<CAnimator3D>()->AddState("IDLE", "PLAYER_IDLE", 20.f / 1000.f);
	ac<CAnimator3D>()->AddState("RUN", "PLAYER_RUN", 20.f / 1000.f);
	ac<CAnimator3D>()->AddState("JUMP", "PLAYER_JUMP", 20.f / 1000.f, false);

	ac<CAnimator3D>()->AddState("ATTACK01", "PLAYER_ATTACK_01", 30.f / 1000.f, false );
	ac<CAnimator3D>()->AddState("ATTACK02", "PLAYER_ATTACK_02", 30.f / 1000.f, false );
	ac<CAnimator3D>()->AddState("ATTACK03", "PLAYER_ATTACK_03", 30.f / 1000.f, false );
	
	ac<CAnimator3D>()->AddState("SKILL02", "PLAYER_GROUNDPUNCH", 30.f / 1000.f, false);

	ac<CAnimator3D>()->AddState("KICK01", "PLAYER_KICK_01", 30.f / 1000.f, false);
	ac<CAnimator3D>()->AddState("KICK02", "PLAYER_KICK_02", 30.f / 1000.f, false);

	ac<CAnimator3D>()->AddState("HIT", "PLAYER_HIT", 30.f / 1000.f, false);
	ac<CAnimator3D>()->AddState("SKILL01", "PLAYER_SKILL01", 30.f / 1000.f, false);


	gc<CAnimator3D>()->SetCurrentState("IDLE");
}

void CPlayerMovement::Start()
{
	CAMERA.Follow(go, 600.f);
}

void CPlayerMovement::Update()
{
	//Animation Various;
	bool Anim_Move = false;
	bool Anim_Attack = false;
	bool Anim_Jump = false;
	bool Anim_Kick = false;
	bool Anim_Skill02 = false;
	

	string CurrentAnimationState = gc<CAnimator3D>()->GetCurrentState()->m_Name;
	float  NormalizeTime = gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime();

	Vector3 MoveDirection = Vector3(0, 0, 0);

	if (INPUT.KeyPress(VK_LEFT))
		MoveDirection += Vector3(-1, 0, 0);
	if (INPUT.KeyPress(VK_RIGHT))
		MoveDirection += Vector3(1, 0, 0);
	if (INPUT.KeyPress(VK_UP))
		MoveDirection += Vector3(0, 0, 1);
	if (INPUT.KeyPress(VK_DOWN))
		MoveDirection += Vector3(0, 0, -1);
	if (INPUT.KeyDown(VK_SPACE))
		Anim_Jump = true;


	if (INPUT.KeyDown('Z') && ChargingSkill01 == false)
		Anim_Attack = true;
	if (INPUT.KeyDown('X') && ChargingSkill01 == false)
		Anim_Kick = true;
	if (INPUT.KeyDown('W') && ChargingSkill01 == false)
		Anim_Skill02 = true;
	if (INPUT.KeyDown('Q'))
	{
		if (CurrentAnimationState == "IDLE" ||
			CurrentAnimationState == "RUN" ||
			CurrentAnimationState == "JUMP")
		{
			ChargingTime = 0.f;
			ChargingSkill01 = true;

			Skill01Prepare = OBJ.Create();
			Skill01Prepare->tf->m_vScale = Vector3(1, 1, 1);
			Skill01Prepare->ac<CSpriteRenderer>()->Init(nullptr, SortingLayer::SR_Effect, RenderMode::RM_Billboard ,Color(1.f,1.f,1.f,0.8f));
			Skill01Prepare->ac<CAnimator2D>()->AddState("EFFECT", "EFFECT_SKILL01_PREPARE", 0.05f, TRUE);
			Skill01Prepare->gc<CAnimator2D>()->SetCurrentState("EFFECT");

			Skill01Prepare->tf->m_vPos = Vector3(0, 100, 0);
			go->AddChild(Skill01Prepare);
			Skill01Prepare->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 0.5f);
		}
	}
	else if (INPUT.KeyUp('Q'))
	{
		if (CurrentAnimationState == "IDLE" ||
			CurrentAnimationState == "RUN")
		{
			if(Skill01Prepare)
			Skill01Prepare->Destroy();
			Skill01Prepare = nullptr;
			ChargingSkill01 = false;	
			gc<CAnimator3D>()->SetCurrentState("SKILL01");	
			CurrentAnimationState = gc<CAnimator3D>()->GetCurrentState()->m_Name;
			NormalizeTime = gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime();
			gc<CRigidBody>()->AddForce(Vector3(Direction * 5000, 0, 0));

			HandEffect = OBJ.Create();
			HandEffect->tf->m_vScale = Vector3(0.25f* Direction, 0.25f, 0.15f);
			HandEffect->ac<CSpriteRenderer>()->Init(nullptr, SortingLayer::SR_Effect, RenderMode::RM_Billboard,Color(1,1,1,0.6f));
			HandEffect->ac<CAnimator2D>()->AddState("EFFECT" ,"EFFECT_SKILL01_HAND", 0.05f,TRUE);
			HandEffect->gc<CAnimator2D>()->SetCurrentState("EFFECT");
			HandEffect->tf->m_vPos = Vector3(80 * Direction, 120, 0);
			go->AddChild(HandEffect);
			HandEffect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 0.5f);


			auto Traill = OBJ.Create();
			Traill->tf->m_vScale = Vector3(0.35f* -Direction, 0.25f, 0.15f);
			Traill->ac<CEffect>()->Init("EFFECT_SKILL01_TRAIL", 0.1f, Vector3(20, 120.f,0));
			go->AddChild(Traill);
			Traill->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.f, 0.5f);
		}
		else
		{
			if(Skill01Prepare)
			Skill01Prepare->Destroy();
			Skill01Prepare = nullptr;
		}

	}
	if (ChargingSkill01)
	{
		ChargingTime += dt;
	}
	if (MoveDirection != Vector3(0, 0, 0) )
	{
		Anim_Move = true;
	}

	if (CurrentAnimationState == "IDLE")
	{
		if (Anim_Move)
			gc<CAnimator3D>()->SetCurrentState("RUN");
		else if (Anim_Skill02)
		{
			gc<CRigidBody>()->AddForce(Vector3(Direction * 1500, 900,0));
			gc<CAnimator3D>()->SetCurrentState("SKILL02");

		}
		else if (Anim_Attack)
		{	
			gc<CAnimator3D>()->SetCurrentState("ATTACK01");
		}
		else if (Anim_Kick)
		{
			gc<CAnimator3D>()->SetCurrentState("KICK01");
		}
		else if (Anim_Jump)
		{
			gc<CAnimator3D>()->SetCurrentState("JUMP");
			gc<CRigidBody>()->AddForce(Vector3(0, 1400, 0));
		}
	}
	else if (CurrentAnimationState == "RUN")
	{
		Move(Vector3(CAMERA.m_vCharactorForward.x,0,CAMERA.m_vCharactorForward.z),400.F);
		if (Anim_Attack)
		{
			gc<CAnimator3D>()->SetCurrentState("ATTACK01");
		}
		else if (Anim_Kick)
		{
			gc<CAnimator3D>()->SetCurrentState("KICK01");
		}
		else if (Anim_Jump)
		{
			gc<CAnimator3D>()->SetCurrentState("JUMP");
			gc<CRigidBody>()->AddForce(Vector3(0, 1400, 0));
		}
		else if (Anim_Skill02)
		{
			gc<CRigidBody>()->AddForce(Vector3(Direction * 1500, 900, 0));
			gc<CAnimator3D>()->SetCurrentState("SKILL02");

		}
		else if (Anim_Move == false)
			gc<CAnimator3D>()->SetCurrentState("IDLE");



	}
	else if (CurrentAnimationState == "JUMP")
	{
			Move(MoveDirection,400.F);

		if(gc<CRigidBody>()->m_vVelocity.y == 0.f)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
	}
	else if (CurrentAnimationState == "SKILL02")
	{
		if (NormalizeTime >= 1)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
	}
	else if (CurrentAnimationState == "ATTACK01")
	{
		if (Anim_Attack == true)
		{
			TriggerAttackCombo = true;
		}

		if (NormalizeTime >= 1.f)
		{
			if (TriggerAttackCombo == true)
			{
				TriggerAttackCombo = false;
				gc<CAnimator3D>()->SetCurrentState("ATTACK02");
			}
			else
			{
				gc<CAnimator3D>()->SetCurrentState("IDLE");
			}
		}
	}
	else if (CurrentAnimationState == "ATTACK02")
	{
		if (Anim_Attack == true)
		{
			TriggerAttackCombo = true;
		}

		if (NormalizeTime >= 1 )
		{
			if (TriggerAttackCombo == true)
			{
				TriggerAttackCombo = false;
				gc<CAnimator3D>()->SetCurrentState("ATTACK03");
			}
			else
			{
				gc<CAnimator3D>()->SetCurrentState("IDLE");

			}
		}
	}
	else if (CurrentAnimationState == "ATTACK03")
	{
		if(NormalizeTime >= 1)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
	}
	else if (CurrentAnimationState == "KICK01")
	{
		if (Anim_Kick == true)
		{
			TriggerAttackCombo = true;
		}

		if (NormalizeTime >= 1 )
		{
			if (TriggerAttackCombo == true)
			{
				TriggerAttackCombo = false;
				gc<CAnimator3D>()->SetCurrentState("KICK02");
			}
			else
			{
				gc<CAnimator3D>()->SetCurrentState("IDLE");

			}

		}
	}
	else if (CurrentAnimationState == "KICK02")
	{
		if (NormalizeTime >= 1)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
	}
	else if (CurrentAnimationState == "SKILL01")
	{
		if (NormalizeTime >= 1 && abs(gc<CRigidBody>()->m_vVelocity.x) < 10.f)
		{
			gc<CAnimator3D>()->SetCurrentState("IDLE");
			OnStopSkill01Rush();
		}
	}
}

void CPlayerMovement::LateUpdate()
{
}

void CPlayerMovement::OnDestroy()
{
}

void CPlayerMovement::OnCollision()
{
}

void CPlayerMovement::Move(Vector3 _vDirection, float _MoveSpeed)
{
	tf->m_vPos += _vDirection * _MoveSpeed * dt;

	//if (_vDirection.x != 0.f)
	{
		Direction = _vDirection.x;
		tf->m_quatRotation = my::QuatEular(Vector3(0,my::GetDirAngle(Vector2(_vDirection.z, _vDirection.x)), 0));
	}
}

void CPlayerMovement::OnLanding()
{
	string CurrentAnimationState = gc<CAnimator3D>()->GetCurrentState()->m_Name;
	float NormalizeTime = gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime();

	if (CurrentAnimationState == "SKILL02")
	{
		CGameObject *  GROUND01 = OBJ.Create();
		GROUND01->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
		GROUND01->ac<CEffect>()->Init("EFFECT_SKILL02_GROUND01", 0.08f,Vector3( tf->m_vPos.x + Direction * 50, -100.f, tf->m_vPos.z));
		GROUND01->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 0.f);

		CGameObject *  GROUND02 = OBJ.Create();
		GROUND02->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
		GROUND02->ac<CEffect>()->Init("EFFECT_SKILL02_GROUND02", 0.08f, Vector3(tf->m_vPos.x + Direction * 50, -100.f, tf->m_vPos.z));
		GROUND02->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 0.f);


		CGameObject *  Effecter = OBJ.Create();
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.75f, -0.8f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.04f, tf->m_vPos + Vector3(100 *	Direction, -50, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 1.f);
			return false;
		}
		);
		Effecter->tf->sa->Delay(0.15f);
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.75f, -0.8f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.04f, tf->m_vPos + Vector3(220 * Direction, -50, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f,1.f);
			return false;
		}
		);
		Effecter->tf->sa->Delay(0.15f);
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.75f, -0.8f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.04f, tf->m_vPos + Vector3(340 * Direction, -50, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f,1.f);
			return false;
		}
		);

		Effecter->tf->sa->Add([=]()->bool
		{
			Effecter->Destroy();
			return false;
		}
		);
	}
}

void CPlayerMovement::OnStopSkill01Rush()
{
	HandEffect->Destroy();
	HandEffect = nullptr;
}
