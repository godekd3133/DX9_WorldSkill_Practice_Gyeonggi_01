#pragma once
#include "CComponent.h"

enum class Enemy_State
{
	IDLE, CHASE, ATTACK_PREPARE ,ATTACK
};

class CEnemy :
	public CComponent
{
public:
	CEnemy();
	~CEnemy();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	int m_iCurHp;
	int m_iMaxHp;
	bool m_bBoss = false;
	bool CanMove = false;
	float m_fShield;
	int m_iDamage;
	bool m_bIsDead = false;
	float m_fMoveSpeed;
	int m_Size;

	bool m_bStance = false;
	void OnHit(int _Damage, Vector3 _vDir);
	bool Correction(Vector3 _vDir);
	bool Correction_Enemy(Vector3 _vDir);
	float m_fMass = 0.f;
	int m_fExp = 0.f;
	float m_fHeight = 0.f;
	void Init(int _MaxHp, int _Damage, int _Size, float _fMoveSpeed, float _fHeight, float _Shield ,float _Mass,int _Exp, bool _bBoss = false);
	void Move(Vector3 _vDirection);
	CGameObject * m_pPlayer= nullptr;

	CGameObject * m_pHpGague  = nullptr;
	CGameObject * m_pHpGagueYellow = nullptr;
	CGameObject * m_pShadow = nullptr;
	void Attack();
};

