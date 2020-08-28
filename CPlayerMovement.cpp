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

	gc<CAnimator3D>()->SetCurrentState("IDLE");
}

void CPlayerMovement::Start()
{
	CAMERA.Follow(go, 6.f);
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
	float NormalizeTime = gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime();

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


	if (INPUT.KeyDown('Z'))
		Anim_Attack = true;
	if (INPUT.KeyDown('X'))
		Anim_Kick = true;
	if (INPUT.KeyDown('W'))
		Anim_Skill02 = true;

	if (MoveDirection != Vector3(0, 0, 0))
	{
		Anim_Move = true;
	}

	if (CurrentAnimationState == "IDLE")
	{
		if (Anim_Move)
			gc<CAnimator3D>()->SetCurrentState("RUN");
		else if (Anim_Skill02)
		{
			gc<CRigidBody>()->AddForce(Vector3(Direction * 600, 800,0));
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
		Move(MoveDirection,400.F);

		if(Anim_Move == false)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
		else if (Anim_Skill02)
		{
			gc<CRigidBody>()->AddForce(Vector3(Direction * 600, 800, 0));
			gc<CAnimator3D>()->SetCurrentState("SKILL02");

		}
		else if (Anim_Attack)
		{
			gc<CAnimator3D>()->SetCurrentState("ATTACK01");
		}
		else if (Anim_Jump)
		{
			gc<CAnimator3D>()->SetCurrentState("JUMP");
			gc<CRigidBody>()->AddForce(Vector3(0, 1400, 0));
		}


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

		if (NormalizeTime >= 1.f &&TriggerAttackCombo == true)
		{
			TriggerAttackCombo = false;
			gc<CAnimator3D>()->SetCurrentState("ATTACK02");
		}
	}
	else if (CurrentAnimationState == "ATTACK02")
	{
		if (Anim_Attack == true)
		{
			TriggerAttackCombo = true;
		}

		if (NormalizeTime >= 1 &&TriggerAttackCombo == true)
		{
			TriggerAttackCombo = false;
			gc<CAnimator3D>()->SetCurrentState("ATTACK03");
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

		if (NormalizeTime >= 1 && TriggerAttackCombo == true)
		{
			TriggerAttackCombo = false;
			gc<CAnimator3D>()->SetCurrentState("KICK02");
		}
	}
	else if (CurrentAnimationState == "KICK02")
	{
		if (NormalizeTime >= 1)
			gc<CAnimator3D>()->SetCurrentState("IDLE");
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

	if (_vDirection.x != 0.f)
	{
		Direction = _vDirection.x;
		tf->m_quatRotation = my::QuatEular(Vector3(0, 90 * _vDirection.x, 0));
	}
}

void CPlayerMovement::OnLanding()
{
	string CurrentAnimationState = gc<CAnimator3D>()->GetCurrentState()->m_Name;
	float NormalizeTime = gc<CAnimator3D>()->GetCurrentState()->GetNormalizeTime();

	if (CurrentAnimationState == "SKILL02")
	{
		CGameObject *  Effecter = OBJ.Create();
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.f, tf->m_vPos + Vector3(100, 0, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 1.f);
			return false;
		}
		);
		Effecter->tf->sa->Delay(0.1f);
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.f, tf->m_vPos + Vector3(250, 0, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 1.f);
			return false;
		}
		);
		Effecter->tf->sa->Delay(0.1f);
		Effecter->tf->sa->Add([=]()->bool
		{
			CGameObject *  Effect = OBJ.Create();
			Effect->tf->m_vScale = Vector3(0.5f, 0.5f, 0.5f);
			Effect->ac<CEffect>()->Init("EFFECT_SKILL02_SPLASH", 0.f, tf->m_vPos + Vector3(400, 0, 0));
			Effect->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 1.f);
			return false;
		}
		);
	}
}
