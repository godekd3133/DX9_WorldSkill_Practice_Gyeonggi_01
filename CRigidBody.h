#pragma once
#include "CComponent.h"
class CRigidBody :
	public CComponent
{
public:
	CRigidBody();
	~CRigidBody();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;
	
public:
	Vector3 m_vVelocity;
	Vector3 m_vOldPos;
	bool m_bGravity = true;
public:
	void AddForce(Vector3 _vVelocitiy);
	CStageMap * m_pMap = nullptr;
	list < function<void()>> OnLanding;
};

