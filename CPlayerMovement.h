#pragma once
#include "CComponent.h"
class CPlayerMovement :
	public CComponent
{
public:
	CPlayerMovement();
	~CPlayerMovement();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

	void Move(Vector3 _vDirection, float _MoveSpeed);

private:

	float Direction = 0.f;
	float m_fAttackDamage = 200.f;

public:
	void OnLanding();
	bool TriggerAttackCombo = false;
	bool ChargingSkill01 = false;
	float ChargingTime = 0.f;
	int ZoomDir = 1;

	Vector3 m_vMoveDirection = Vector3(0,0,0);
	
	CStageMap * m_pMap;
	CGameObject * HandEffect = nullptr;
	CGameObject * Skill01Prepare = nullptr;

	void OnStopSkill01Rush();

	void OnAttack01_Event();
	void OnAttack02_Event(); 
	void OnSkill01_Event();
	void OnSkill02_Event();

};

