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

	CGameObject * Skill01BG = OBJ.Create("UI", Tag::UI);
	Skill01BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Skill01BG->tf->m_vPos = Vector3(1500, 840, 0);

	CGameObject * Skill02BG = OBJ.Create("UI", Tag::UI);
	Skill02BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Skill02BG->tf->m_vPos = Vector3(1680, 840, 0);

	CGameObject * Skill01CoolTime = OBJ.Create("UI", Tag::UI);
	Skill01CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill01CoolTime->tf->m_vPos = Vector3(1500, 840, 0);

	CGameObject * Skill02CoolTime = OBJ.Create("UI", Tag::UI);
	Skill02CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill02CoolTime->tf->m_vPos = Vector3(1680, 840, 0);


	m_pSkill01 = OBJ.Create("UI", Tag::UI);
	m_pSkill01->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON01"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill01->tf->m_vPos = Vector3(1500, 840, 0);
	
	m_pSkill02 = OBJ.Create("UI", Tag::UI);
	m_pSkill02->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON02"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill02->tf->m_vPos = Vector3(1680, 840, 0);

	m_pComboBG = OBJ.Create("UI", Tag::UI);
	m_pComboBG->ac<CSpriteRenderer>()->Init(SPRITE("UI_COMBO"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pComboBG->tf->m_vPos = Vector3(1630, 510, 0);

	m_pComboText = OBJ.Create("UI", Tag::UI);


	CGameObject * Skill01Key = OBJ.Create("UI", Tag::UI);
	Skill01Key->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON01_KEY"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Skill01Key->tf->m_vPos = Vector3(1500, 915, 0);

	CGameObject * Skill02Key = OBJ.Create("UI", Tag::UI);
	Skill02Key->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILLICON02_KEY"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Skill02Key->tf->m_vPos = Vector3(1690, 915, 0);

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

	m_pQuest = OBJ.Create("UI", Tag::UI);
	m_pQuest->ac<CSpriteRenderer>()->Init(SPRITE("UI_QUEST"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pQuest->tf->m_vPos = Vector3(1753, 161, 0);

	m_pQuestText = OBJ.Create();
	m_pQuestText->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1));
	m_pQuestText->tf->m_vPos = Vector3(1530, 120, 0);
	m_pQuestText->tf->m_vScale = Vector3(0.4f, 0.4f, 0.4f);

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

	m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurExp / (float)GAME.MaxExp, 1.f), dt  * 4.f);
	m_pLevelText->gc<CText>()->m_Text = "Lv. " + to_string(GAME.Level);

	char str[100];
	sprintf(str, GAME.QuestString[GAME.Quest].c_str(), GAME.Count);
	m_pQuestText->gc<CText>()->m_Text = str;


	if (GAME.Skill02Timer <= GAME.Skill02CoolTime)
		GAME.Skill02Timer += dt;
	
	if (GAME.SkillLevel[3] > 0)
	{
		if (GAME.Skill01Timer <= GAME.Skill01CoolTime)
			GAME.Skill01Timer += dt;
		m_pSkill01->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f,GAME.Skill01Timer / GAME.Skill01CoolTime);

	}
	else 
		m_pSkill01->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f,0.f);

	m_pSkill02->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f,GAME.Skill02Timer / GAME.Skill02CoolTime);
}

void CPlayerUI::LateUpdate()
{
	if (m_pComboText != nullptr)
	{
		if (m_pComboText->m_bDestroy == true)
			m_pComboText = nullptr;
	}
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

void CPlayerUI::AddCombo(int _Combo)
{
	if(m_pComboText != nullptr)
	m_pComboText->Destroy();
	m_pComboText = nullptr;
	m_pComboText = OBJ.Create();
	GAME.Combo += _Combo;
	if (GAME.Combo > GAME.MaxCombo) GAME.MaxCombo = GAME.Combo;
	m_pComboText->ac<CDamageFont>()->InitCombo("UI_COMBOFONT", Vector3(1520, 480, 0), GAME.Combo);
}

