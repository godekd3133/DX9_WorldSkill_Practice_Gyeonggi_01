#include "DXUT.h"
#include "CPlayerUI.h"


CPlayerUI::CPlayerUI()
{
	m_Color = Color(1, 1, 1, 1);
	m_SortingLayer = SortingLayer::SR_UI2;
}


CPlayerUI::~CPlayerUI()
{
}

void CPlayerUI::Awake()
{
	CGameObject * PlayerStatusBG01 = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG01->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_01"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG01->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG01->tf->m_vPos = Vector3(50, 0, 0);

	CGameObject * PlayerStatusBG02 = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG02->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_02"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG02->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG02->tf->m_vPos = Vector3(50, 0, 0);

	CGameObject * PlayerStatusBG03 = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG03->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_03"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG03->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG03->tf->m_vPos = Vector3(50, 0, 0);

	m_pHpBar_Bg = OBJ.Create("UI", Tag::UI);
	m_pHpBar_Bg->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar_Bg->tf->m_vPos = Vector3(450, 120, 0);

	m_pHpBar_Yellow = OBJ.Create("UI", Tag::UI);
	m_pHpBar_Yellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR_YELLOW"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar_Yellow->tf->m_vPos = Vector3(450, 120, 0);

	m_pHpBar = OBJ.Create("UI", Tag::UI);
	m_pHpBar->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar->tf->m_vPos = Vector3(450, 120, 0);

	m_pExpBar_Bg = OBJ.Create("UI", Tag::UI);
	m_pExpBar_Bg->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_EXPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pExpBar_Bg->tf->m_vPos = Vector3(430, 150, 0);

	m_pExpBar = OBJ.Create("UI", Tag::UI);
	m_pExpBar->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_EXPBAR"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pExpBar->tf->m_vPos = Vector3(430,150, 0);

	m_pLevelText = OBJ.Create();
	m_pLevelText->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI, Color(1,1,0
		,1));
	m_pLevelText->tf->m_vPos = Vector3(350, 50, 0);
	m_pLevelText->tf->m_vScale = Vector3(0.4f, 0.4f, 0.4f);

	CGameObject * Minimap = OBJ.Create("UI", Tag::UI);
	Minimap->ac<CSpriteRenderer>()->Init(GAME.m_pMap->m_pMinimap, SortingLayer::SR_UI, RenderMode::RM_UI);
	Minimap->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 1);
	Minimap->tf->m_vPos = Vector3(0, WINSIZEY, 0);

	m_pSkillTree = OBJ.Create();
	m_pSkillTree->ac<CSkillTree>()->Disable();
}

void CPlayerUI::Start()
{
}

void CPlayerUI::Update()
{
	if (INPUT.KeyDown('K'))
		m_pSkillTree->gc<CSkillTree>()->Enable();
	if (INPUT.KeyDown(VK_ESCAPE))
		m_pSkillTree->gc<CSkillTree>()->Disable();

	m_pHpBar->gc<CSpriteRenderer>()->m_vFillAmount = Vector2((float)GAME.CurHp / (float)GAME.MaxHp, 1.f);
	m_pHpBar_Yellow->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pHpBar_Yellow->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurHp / (float)GAME.MaxHp, 1.f), dt  * 2.f);

	m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurExp / (float)GAME.CurExp, 1.f), dt  * 2.f);
	m_pLevelText->gc<CText>()->m_Text = "Lv. " + to_string(GAME.Level);
}

void CPlayerUI::LateUpdate()
{
}

void CPlayerUI::OnDestroy()
{
}

void CPlayerUI::OnRender()
{
	for (auto iter : OBJ.Finds(Tag::Enemy))
	{
		RenderEnemy(iter);
	}
		RenderPlayer(GAME.m_pPlayer);

}

void CPlayerUI::OnCollision(CGameObject * _pObject)
{
}

void CPlayerUI::RenderPlayer(CGameObject * _pPlayer)
{
	Vector3 vPos = Vector3(0, WINSIZEY - 399 +  (283) /2, 0);
	Vector3 vOffset = Vector3(20, 10,0);
	Vector3 EnemyPos = Vector3(-_pPlayer->tf->m_vPos.x / 35.f, _pPlayer->tf->m_vPos.z / 35.f, 0.f);
	GRAPHICS.Render_Sprite(SPRITE("UI_MINIMAP_PLAYER"), GRAPHICS.ToMatrix(vPos + EnemyPos + vOffset), Vector2(0.5f, 0.5f), Vector2(1.f, 1.f), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CPlayerUI::RenderEnemy(CGameObject * _pEnemy)
{
		Vector3 vPos = Vector3(0, WINSIZEY - 399+ (283 ) / 2, 0);
		Vector3 vOffset = Vector3(20,10, 0);
		Vector3 EnemyPos = Vector3(-_pEnemy->tf->m_vPos.x / 35.f, _pEnemy->tf->m_vPos.z/35.f,0.f);
		GRAPHICS.Render_Sprite(SPRITE("UI_MINIMAP_ENEMY"), GRAPHICS.ToMatrix(vPos + EnemyPos + vOffset), Vector2(0.5f, 0.5f), Vector2(1.f, 1.f), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

