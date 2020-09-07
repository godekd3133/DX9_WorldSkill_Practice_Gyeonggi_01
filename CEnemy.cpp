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

	m_pShadow = OBJ.Create();
	m_pShadow->ac<CSpriteRenderer>()->Init(SPRITE("UI_SHADOW"), SortingLayer::SR_UI, RenderMode::RM_Default);
	m_pShadow->tf->SetRotation(Vector3(90, 0, 0));

	auto HpGaugeBG = OBJ.Create();
	HpGaugeBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	go->AddChild(HpGaugeBG);
	HpGaugeBG->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	HpGaugeBG->tf->m_vScale.y = -HpGaugeBG->tf->m_vScale.y;
	HpGaugeBG->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGagueYellow = OBJ.Create();
	m_pHpGagueYellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_YELLOW"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	go->AddChild(m_pHpGagueYellow);
	m_pHpGagueYellow->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	m_pHpGagueYellow->tf->m_vScale.y = -m_pHpGagueYellow->tf->m_vScale.y;
	m_pHpGagueYellow->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGague = OBJ.Create();
	m_pHpGague->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	go->AddChild(m_pHpGague);
	m_pHpGague->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	m_pHpGague->tf->m_vScale.y = -m_pHpGague->tf->m_vScale.y;
	m_pHpGague->tf->m_vPos = Vector3(0, m_fHeight, 0);




	auto EnemyIcon = OBJ.Create();
	EnemyIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_MONSTER_HPICON"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	go->AddChild(EnemyIcon);
	EnemyIcon->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	EnemyIcon->tf->m_vScale.y = -EnemyIcon->tf->m_vScale.y;
	EnemyIcon->tf->m_vPos = Vector3(0, m_fHeight, 0);
	EnemyIcon->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + 99.f/77.f, 0.5f);

}

void CEnemy::Update()
{
	m_pHpGague->gc<CSpriteRenderer>()->m_vFillAmount = Vector2((float)m_iCurHp/(float)m_iMaxHp, 1.f);
	m_pHpGagueYellow->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pHpGagueYellow->gc<CSpriteRenderer>()->m_vFillAmount,  Vector2((float)m_iCurHp / (float)m_iMaxHp, 1.f),dt  * 2.f);

	m_pShadow->tf->m_vPos = Vector3(tf->m_vPos.x, GAME.m_pMap->GetFloorY(tf->m_vPos) +1 , tf->m_vPos.z);

	float scale = 100.f / max(abs(GAME.m_pMap->GetFloorY(tf->m_vPos) - tf->m_vPos.y),100);
	m_pShadow->tf->m_vScale = Vector3(scale, scale, 1.f);
}

void CEnemy::LateUpdate()
{

}


void CEnemy::OnDestroy()
{
	m_pShadow->Destroy();
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
	if (_pObject->m_Tag == Tag::Enemy && m_bIsDead == false)
	{
		Vector3 _vDir = my::GetDirection(tf->m_vPos, _pObject->tf->m_vPos);
		_vDir.y = 0.f;

		if (_vDir.x == 0.f && _vDir.z == 0.f)
		{
			_vDir.x = my::RandRange(-100, 100) / 100.f;
			_vDir.z = my::RandRange(-100, 100) / 100.f;
		}

		Move(-_vDir*dt*20);
	}
}

void CEnemy::OnHit(int _Damage, Vector3 _vDir)
{
		m_iCurHp -= _Damage;
		if (m_iCurHp <= 0.f)
		{
			go->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) * 1500 + _vDir * 1000 * my::RandRange(6,14) ;
			go->gc<CAnimator3D>()->SetCurrentState("DEAD");
			m_bIsDead =true;
		}
		else
		{
			if (m_bStance == false)
			{
				gc<CAnimator3D>()->SetCurrentState("HIT");
				gc<CAnimator3D>()->GetCurrentState()->m_bEnable = true;
				gc<CAnimator3D>()->GetCurrentState()->m_iCurFrame = 0;
			}
			CAMERA.Shake(0.075f, 12.f);
			CAMERA.m_fDistance = 1300.f;

			tf->sa->Add(
				[&]()->bool {
				INPUT.TimeScale = 0.05f;
				return true;
			}, 0.025F);


			auto DamageFont = OBJ.Create();
			DamageFont->tf->m_vScale = Vector3(0.4f, 0.4f, 0.f);
			DamageFont->ac<CDamageFont>()->Init(tf->m_vPos + Vector3(my::RandRange(-50, 50), my::RandRange(170, 280), 0), _Damage);
			DamageFont->gc<CDamageFont>()->SetTransform();
			gc<CMeshRenderer>()->sa->Add([=]()->bool {
				return gc<CMeshRenderer>()->LerpColor(Color(1.f, 0.f, 0.f, 1.f), 24.f * dt);
			});
			gc<CMeshRenderer>()->sa->Add([=]()->bool {
				return gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 1.f), 24.f * dt);
			});
		}
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

void CEnemy::Init(int _MaxHp, int _Damage, int _Size, float _fMoveSpeed, float _fHeight)
{
	go->m_Tag = Tag::Enemy;
	ac<CCollider>()->Init(_Size);
	m_fHeight = _fHeight;
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
				gc<CRigidBody>()->m_vVelocity = Vector3(0, 1400, 0);

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
				gc<CRigidBody>()->m_vVelocity = Vector3(0, 1400, 0);

			if (tf->m_vPos.y < GAME.m_pMap->GetFloorY(tf->m_vPos))
			{
				tf->m_vPos.z = OldPos.z;
				y = true;
			}
		}

		
	}
}
