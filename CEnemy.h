#pragma once
#include "CComponent.h"

enum class Enemy_State
{
	IDLE, CHASE, ATTACK 
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
	bool CanMove = false;
	int m_iDamage;
	float m_fMoveSpeed;
	int m_Size;

	void OnHit(int _Damage);
	bool Correction(Vector3 _vDir);
	bool Correction_Enemy(Vector3 _vDir);

	void Init(int _MaxHp, int _Damage, int _Size, float _fMoveSpeed);
	void Move(Vector3 _vDirection);
	Enemy_State m_State;
	CGameObject * m_pPlayer= nullptr;
};

