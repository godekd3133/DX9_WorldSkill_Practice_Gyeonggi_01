#pragma once
#include "CComponent.h"
class CPlayerUI :
	public CComponent
{
public:
	CPlayerUI();
	~CPlayerUI();


public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

};

