#pragma once
#include "CComponent.h"
class CBoss02 :
	public CComponent
{
public:
	CBoss02();
	~CBoss02();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

public:
	void Init(Vector3 _vPos);

	float m_fAttackTime = 0.f;
	float m_fAttackDelay = 2.f;
	Enemy_State m_State;
	CGameObject * m_pPlayer = nullptr;
	CEnemy * m_pEnemy = nullptr;
};

