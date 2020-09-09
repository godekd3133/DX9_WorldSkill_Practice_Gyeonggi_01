#pragma once
#include "CComponent.h"
enum ItemKind{ IK_ITEM, IK_EXP, IK_COIN};
class CItem : public CComponent
{
public:
	CItem();
	~CItem();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;


public:
	ItemKind m_Kind;
	void Init(ItemKind  _Kind, Vector3 _vPos);
};

