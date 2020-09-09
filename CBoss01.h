#pragma once
#include "CComponent.h"
class CBoss01 :
	public CComponent
{
public:
	CBoss01();
	~CBoss01();

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
	float m_fAttackDelay = 1.f;
	Enemy_State m_State;
	CGameObject * m_pPlayer = nullptr;
	CEnemy * m_pEnemy = nullptr;
};

