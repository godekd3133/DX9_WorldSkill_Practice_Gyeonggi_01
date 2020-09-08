#pragma once
#include "CComponent.h"

class CSkillTree :
	public CComponent
{
public:
	CSkillTree();
	~CSkillTree();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnCollision(CGameObject * _pObject) override;

	void Enable();
	void Disable();
private:
	int index = 0;
	
	CGameObject * m_pSkillTreeWindow = nullptr;
	CGameObject * m_pBlack = nullptr;
	CGameObject * m_pBtClose = nullptr;

	CGameObject * m_pBackground[8];
	CGameObject * m_pIcon[8];


	CGameObject * m_pSelectBackground;
	CGameObject * m_pSelectIcon;
	CGameObject * m_pSelectName;
	CGameObject * m_pSelectTooltip;
	CGameObject * m_pSelectName_Text;
	CGameObject * m_pSelectTooltip_Text;
	CGameObject * m_pLevelText;
	CGameObject * m_pSPText;
};

