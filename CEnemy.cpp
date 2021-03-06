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
	if (my::RandRange(0, 1000) > 900)
	{
		CGameObject * Item = OBJ.Create();
		Item->ac<CItem>()->Init(ItemKind::IK_ITEM, tf->m_vPos);
	}
	for (int i = 0; i < my::RandRange(0, m_fExp); i++)
	{
		CGameObject * Exp = OBJ.Create();
		Exp->ac<CItem>()->Init(ItemKind::IK_EXP, tf->m_vPos + Vector3(0, 150, 0));
		Exp->gc<CRigidBody>()->m_vImpulse = Vector3(15.f, 0.f, 15.f);
		Exp->gc<CRigidBody>()->AddForce(Vector3(my::RandRange(-10, 10) / 10.f, 0, my::RandRange(-10, 10) / 10.f) * 3500);
	}

	for (int i = 0; i < my::RandRange(1, 2 ); i++)
	{
		CGameObject * Exp = OBJ.Create();
		Exp->ac<CItem>()->Init(ItemKind::IK_COIN, tf->m_vPos + Vector3(0,150,0));
		Exp->gc<CRigidBody>()->m_vImpulse = Vector3(15.f, 0.f, 15.f);
		Exp->gc<CRigidBody>()->AddForce(Vector3(my::RandRange(-10, 10) / 10.f, 0, my::RandRange(-10, 10) / 10.f) * 3500);
	}
	m_pShadow->Destroy();
}

void CEnemy::OnCollision(CGameObject * _pObject)
{
	if (_pObject->m_Tag == Tag::Enemy && m_bIsDead == false && m_bStance == false)
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
	GRAPHICS.dPlay("VFX_HIT0" + to_string(RandRange(1,3)));
	_Damage = (float)_Damage * min(100.f, (100.f - (m_fShield - (float)GAME.GetValue(5))))/100.f;
		m_iCurHp -= _Damage;
		if (m_iCurHp <= 0.f)
		{
			go->gc<CRigidBody>()->m_vVelocity = Vector3(0, 1, 0) * 1200 * m_fMass  + _vDir * 600 * m_fMass * my::RandRange(4,8) ;
			go->gc<CAnimator3D>()->SetCurrentState("DEAD");
			m_bIsDead =true;
		}
		else
		{
			if (m_bStance == false && m_bBoss == false)
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



		}
		auto DamageFont = OBJ.Create();
		DamageFont->tf->m_vScale = Vector3(0.4f, 0.4f, 0.f);
		DamageFont->ac<CDamageFont>()->Init("UI_DAMAGEFONT", tf->m_vPos + Vector3(my::RandRange(-50, 50), my::RandRange(170, 280), 0), _Damage);
		DamageFont->gc<CDamageFont>()->SetTransform();
		gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return gc<CMeshRenderer>()->LerpColor(Color(1.f, 0.f, 0.f, 1.f), 24.f * dt);
		});
		gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 1.f), 24.f * dt);
		});
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



void CEnemy::Init(int _MaxHp, int _Damage, int _Size, float _fMoveSpeed, float _fHeight, float _Shield, float _Mass,int _Exp, bool _bBoss)
{
	m_fExp = _Exp;
	m_fMass = _Mass;
	m_fShield = _Shield;
	m_bBoss = _bBoss;
	go->m_Tag = Tag::Enemy;
	ac<CCollider>()->Init(_Size);
	m_fHeight = _fHeight;
	m_iCurHp = _MaxHp;
	m_fMoveSpeed = _fMoveSpeed;
	m_iMaxHp = _MaxHp;
	m_iDamage = _Damage;

	auto HpGaugeBG = OBJ.Create();
	if (m_bBoss == false)
		HpGaugeBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	else
		HpGaugeBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_Billboard);

	go->AddChild(HpGaugeBG);
	HpGaugeBG->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	HpGaugeBG->tf->m_vScale.y = -HpGaugeBG->tf->m_vScale.y;
	HpGaugeBG->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGagueYellow = OBJ.Create();
	if (m_bBoss == false)
		m_pHpGagueYellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR_YELLOW"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	else
		m_pHpGagueYellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR_YELLOW"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	go->AddChild(m_pHpGagueYellow);
	m_pHpGagueYellow->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	m_pHpGagueYellow->tf->m_vScale.y = -m_pHpGagueYellow->tf->m_vScale.y;
	m_pHpGagueYellow->tf->m_vPos = Vector3(0, m_fHeight, 0);

	m_pHpGague = OBJ.Create();
	if (m_bBoss == false)
		m_pHpGague->ac<CSpriteRenderer>()->Init(SPRITE("UI_HPBAR"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
	else
		m_pHpGague->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSSHPBAR"), SortingLayer::SR_UI, RenderMode::RM_Billboard);


	go->AddChild(m_pHpGague);
	m_pHpGague->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	m_pHpGague->tf->m_vScale.y = -m_pHpGague->tf->m_vScale.y;
	m_pHpGague->tf->m_vPos = Vector3(0, m_fHeight, 0);

	auto EnemyIcon = OBJ.Create();
	if (m_bBoss == false)
	{
		EnemyIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_MONSTER_HPICON"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
		EnemyIcon->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + 99.f / 77.f, 0.5f);

	}
	else
	{
		EnemyIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_BOSS_HPICON"), SortingLayer::SR_UI, RenderMode::RM_Billboard);
		EnemyIcon->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + 199.f / 99.f, 0.5f);

	}
	go->AddChild(EnemyIcon);
	EnemyIcon->tf->m_vScale = Vector3(0.5f, 0.5f, 0.f);
	EnemyIcon->tf->m_vScale.y = -EnemyIcon->tf->m_vScale.y;
	EnemyIcon->tf->m_vPos = Vector3(0, m_fHeight, 0);
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

void CEnemy::Attack()
{

	float fFinalDamage = m_iDamage * (min(100, (100.f - GAME.GetValue(7))) / 100.f) * (my::RandRange(80,120) / 100.f);


	list<CGameObject *> listHitObject = OBJ.GetCollisionObject(tf->m_vPos + my::GetDirection(this->tf->m_vPos, GAME.m_pPlayer->tf->m_vPos ) * 75, 250, Tag::Player);//OBJ.RayCast(this->tf->m_vPos , vDir, Tag::Enemy,fDistance);

	if (listHitObject.empty() == false)
	{
		GRAPHICS.dPlay("VFX_HIT0" + to_string(RandRange(1, 3)));
		GAME.Hit(fFinalDamage);
		auto DamageFont = OBJ.Create();
		DamageFont->tf->m_vScale = Vector3(0.75f, 0.75f, 0.f);
		DamageFont->ac<CDamageFont>()->Init("UI_HITFONT", GAME.m_pPlayer->tf->m_vPos + Vector3(my::RandRange(-50, 50), my::RandRange(170, 280), 0), (int)fFinalDamage);
		DamageFont->gc<CDamageFont>()->SetTransform();
		gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return gc<CMeshRenderer>()->LerpColor(Color(1.f, 0.f, 0.f, 1.f), 24.f * dt);
		});
		gc<CMeshRenderer>()->sa->Add([=]()->bool {
			return gc<CMeshRenderer>()->LerpColor(Color(1.f, 1.f, 1.f, 1.f), 24.f * dt);
		});
	}

}
