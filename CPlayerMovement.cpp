#include "DXUT.h"
#include "CPlayerMovement.h"
#include "CBullet.h"
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
	tf->m_vScale = Vector3(1, 1, 1);
	tf->m_vPos = Vector3(-3000,-200, 3000);
	ac<CMeshRenderer>()->Init(MESH("PLAYER"));

	ac<CAnimator3D>()->AddState("IDLE", "PLAYER_IDLE", 20.f / 1000.f);
//	gc<CAnimator3D>()->AddState("RUN", "PLAYER_RUN", 20.f / 1000.f);
//	gc<CAnimator3D>()->AddState("JUMP", "PLAYER_JUMP", 20.f / 1000.f, false);
//	gc<CAnimator3D>()->AddState("ATTACK01", "PLAYER_ATTACK_01", 30.f / 1000.f, false );
//	gc<CAnimator3D>()->AddState("ATTACK02", "PLAYER_ATTACK_02", 30.f / 1000.f, false );
//	gc<CAnimator3D>()->AddState("ATTACK03", "PLAYER_ATTACK_03", 30.f / 1000.f, false );
//	gc<CAnimator3D>()->AddState("SKILL02", "PLAYER_GROUNDPUNCH", 30.f / 1000.f, false);
//	gc<CAnimator3D>()->AddState("KICK01", "PLAYER_KICK_01", 30.f / 1000.f, false);
//	gc<CAnimator3D>()->AddState("KICK02", "PLAYER_KICK_02", 30.f / 1000.f, false);
//	gc<CAnimator3D>()->AddState("HIT", "PLAYER_HIT", 30.f / 1000.f, false);
//	gc<CAnimator3D>()->AddState("SKILL01", "PLAYER_SKILL01", 30.f / 1000.f, false);
//
//
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}

void CPlayerMovement::Start()
{
	CAMERA.Follow(go,600.f);
}

void CPlayerMovement::Update()
{
	//Animation Various;
	tf->LerpRotation(Vector3(0, my::GetDirAngle(CAMERA.m_vCharactorAxis[Axis::Foward]),0), 12.f * dt);
	Vector3 MoveDirection = Vector3(0, 0, 0);


	if (INPUT.KeyPress('W'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Foward];
	else if (INPUT.KeyPress('S'))
		MoveDirection += CAMERA.m_vCharactorAxis[Axis::Back];
	if (INPUT.KeyPress(VK_LBUTTON))
	{
		CGameObject * pBullet = OBJ.Create();
		pBullet->ac<CBullet>()->Init(tf->m_vPos,tf->GetFoward(), 40.f);
	}
	if (INPUT.KeyDown(VK_SPACE))
	{
		gc<CRigidBody>()->AddForce(Vector3(0, 2000, 0));
	}

	if (INPUT.KeyPress(VK_RBUTTON))
	{

		CAMERA.m_fDistance = Lerp(CAMERA.m_fDistance, 2.f, 6 * dt);
		CAMERA.m_vOffset = Lerp(CAMERA.m_vOffset, Vector3(0.75f * ZoomDir, 0.f, 0.f), 6 * dt);

		if (INPUT.KeyDown('D'))
		{
			ZoomDir = 1;
		}
		else if (INPUT.KeyDown('A'))
		{
			ZoomDir = -1;
		}
	}
	else
	{
		if (INPUT.KeyPress('A'))
			MoveDirection += CAMERA.m_vCharactorAxis[Axis::Left];
		else if (INPUT.KeyPress('D'))
			MoveDirection += CAMERA.m_vCharactorAxis[Axis::Right];

		CAMERA.m_fDistance = Lerp(CAMERA.m_fDistance, 600.f, 6 * dt);
		CAMERA.m_vOffset = Lerp(CAMERA.m_vOffset, Vector3(0.f, 0.f, 0.f), 6 * dt);
	}

	if(MoveDirection != Vector3(0,0,0))
	Move(MoveDirection, 1000.F);

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
	CollisionInfo info;
	if (
		
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Foward], _MoveSpeed * dt + 150, info) == false &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Left], _MoveSpeed * dt + 150, info) == false &&
		m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), CAMERA.m_vCharactorAxis[Axis::Right], _MoveSpeed * dt + 150, info) == false
		)
	{
		if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), Vector3(_vDirection.x, 0, 0), _MoveSpeed * dt + 150, info) == false   )
		{
			tf->m_vPos.x += _vDirection.x * _MoveSpeed * dt;
		}
		if (m_pMap->GetCollisionInfoByRay(tf->GetWorldPos() + Vector3(0, 150, 0), Vector3(0, 0, _vDirection.z), _MoveSpeed * dt + 150, info) == false  )
		{
			tf->m_vPos.z += _vDirection.z * _MoveSpeed * dt;
		}
	}

}

void CPlayerMovement::OnLanding()
{
	/*string CurrentAnimationState = gc<CAnimator3D>()->GetCurrentState()->m_Name;
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
	}*/
}

void CPlayerMovement::OnStopSkill01Rush()
{
	HandEffect->Destroy();
	HandEffect = nullptr;
}
