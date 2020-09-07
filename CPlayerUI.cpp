#include "DXUT.h"
#include "CPlayerUI.h"


CPlayerUI::CPlayerUI()
{
}


CPlayerUI::~CPlayerUI()
{
}

void CPlayerUI::Awake()
{
	CGameObject * PlayerStatusBG = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG->tf->m_vPos = Vector3(0, 0, 0);

	CGameObject * Minimap = OBJ.Create("UI", Tag::UI);
	Minimap->ac<CSpriteRenderer>()->Init(SPRITE("UI_MINIMAP"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Minimap->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 1);
	Minimap->tf->m_vPos = Vector3(0, WINSIZEY, 0);

	
}

void CPlayerUI::Start()
{
}

void CPlayerUI::Update()
{
}

void CPlayerUI::LateUpdate()
{
}

void CPlayerUI::OnDestroy()
{
}

void CPlayerUI::OnCollision(CGameObject * _pObject)
{
}
