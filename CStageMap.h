#pragma once
#include "CComponent.h"

enum MapCollision
{
	FirstFloor,
	Wall,
	Between,
	SecondFloor
};
class CStageMap :
	public CComponent
{
public:
	CStageMap();
	~CStageMap();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision() override;

private:
	CMesh * m_pMesh = nullptr;
	CSprite * m_pMinimap = nullptr;
	CSprite * m_pCollisionMap = nullptr;
	CGameObject * m_pPlayer = nullptr;
public:
	void Init(CMesh * _pMesh, CSprite * _pMinimap, CSprite * _pCollisionMap);
	MapCollision GetCollisionInfoByCollisionMap(Vector3 _vPos);
};

