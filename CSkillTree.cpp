#include "DXUT.h"
#include "CSkillTree.h"


CSkillTree::CSkillTree()
{
}


CSkillTree::~CSkillTree()
{
}

void CSkillTree::Awake()
{
	m_pBlack = OBJ.Create();
	m_pBlack->ac<CSpriteRenderer>()->Init(SPRITE("BLACK"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI, Color(1,1,1,0.5f));
	m_pBlack->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.f, 0.f);

	m_pSkillTreeWindow = OBJ.Create();
	m_pSkillTreeWindow->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_BACKGROUND"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSkillTreeWindow->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.f, 0.f);

	m_pBtClose = OBJ.Create();
	m_pBtClose->ac<CButton>()->Init(
		SPRITE("UI_ST_BT_CLOSE"), 
		Vector3(m_pSkillTreeWindow->tf->m_vPos.x + SPRITE("UI_ST_BACKGROUND")->GetWidth()/2.f, m_pSkillTreeWindow->tf->m_vPos.y -SPRITE("UI_ST_BACKGROUND")->GetHeight() / 2.f, 0), Vector3(1, 1, 1), [=]() {
		Disable();
	});
	m_pBtClose->gc<CSpriteRenderer>()->m_SortingLayer = SortingLayer::SR_SCREEEN;
	for (int i = 0; i < 8; i++)
	{
		m_pBackground[i] = OBJ.Create();
		m_pBackground[i]->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_ICON_BACKGROUND"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
		m_pIcon[i] = OBJ.Create();
		m_pIcon[i]->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_ICON_0" + to_string(i+1)), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	
		if (i < 4)
		{
			m_pBackground[i]->tf->m_vPos = Vector3(330 + 175 * (i % 4), 300, 0);
			m_pIcon[i]->tf->m_vPos = Vector3(330 + 175 *( i %4), 300, 0);
		}
		else
		{
			m_pBackground[i]->tf->m_vPos = Vector3(330 + 175 * (i% 4), 500, 0);
			m_pIcon[i]->tf->m_vPos = Vector3(330 + 175 *(i % 4), 500, 0);
		}


	}

	m_pSelectBackground = OBJ.Create();
	m_pSelectBackground->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_SELECT_BACKGROUND"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectBackground->tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	m_pSelectBackground->tf->m_vPos = Vector3(WINSIZEX / 2.F + 370, WINSIZEY / 2.f - 300, 0.f);

	m_pSelectIcon = OBJ.Create();
	m_pSelectIcon->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_SELECT_BACKGROUND"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectIcon->tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	m_pSelectIcon->tf->m_vPos = Vector3(WINSIZEX / 2.F + 370, WINSIZEY / 2.f - 300, 0.f);

	m_pSelectName = OBJ.Create();
	m_pSelectName->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_SELECT_NAME"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectName->tf->m_vPos = Vector3(WINSIZEX / 2.F + 370, WINSIZEY / 2.f-100, 0.f);

	m_pSelectName_Text = OBJ.Create();
	m_pSelectName_Text->ac<CText>()->Init("", SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectName_Text->tf->m_vPos = Vector3(WINSIZEX / 2.F + 250, WINSIZEY / 2.f-130, 0.f);

	m_pSelectTooltip = OBJ.Create();
	m_pSelectTooltip->ac<CSpriteRenderer>()->Init(SPRITE("UI_ST_SELECT_TOOLTIP"), SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectTooltip->tf->m_vPos = Vector3(WINSIZEX / 2.F + 370, WINSIZEY / 2.f + 250, 0.f);

	m_pSelectTooltip_Text = OBJ.Create();
	m_pSelectTooltip_Text->ac<CText>()->Init("", SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSelectTooltip_Text->tf->m_vPos = Vector3(WINSIZEX / 2.F + 100, WINSIZEY / 2.f + 170, 0.f);
	m_pSelectTooltip_Text->tf->m_vScale = Vector3(0.5f, 0.5f, 1.f);
	//m_pSelectTooltip_Text;
	m_pLevelText = OBJ.Create();
	m_pLevelText->ac<CText>()->Init("adsda", SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pLevelText->tf->m_vPos = Vector3(WINSIZEX / 2.F + 150, WINSIZEY / 2.f + 0, 0.f);


	m_pSPText = OBJ.Create();
	m_pSPText->ac<CText>()->Init("남은 포인트 : ", SortingLayer::SR_SCREEEN, RenderMode::RM_UI);
	m_pSPText->tf->m_vPos = Vector3(WINSIZEX / 2.F - 550, WINSIZEY / 2.f + 270, 0.f);
}

void CSkillTree::Start()
{
	m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND_SELECT");

}

void CSkillTree::Update()
{

	if (GAME.SkillPoint == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			m_pIcon[i]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_0" + to_string(i + 1) + "_DISABLE");
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			m_pIcon[i]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_0" + to_string(i +1) );
		}
		if (GAME.SkillLevel[2] < 3)
		{
			m_pIcon[3]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_04_DISABLE");

		}
		else
		{
			m_pIcon[3]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_04");

		}
	}

	if (INPUT.KeyDown(VK_LEFT))
	{

		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND");
		index--;
		if (index < 0)
			index = 7;
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND_SELECT");
	}
	else 	if (INPUT.KeyDown(VK_RIGHT))
	{
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND");
		index++;
		if (index >= 8)
			index = 0;
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND_SELECT");
	}
	else if (INPUT.KeyDown(VK_DOWN))
	{
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND");
		if(index > 3)
		index -= 4;
		else index += 4;
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND_SELECT");
	}
	else if (INPUT.KeyDown(VK_UP))
	{
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND");
		if (index > 3)
			index -= 4;
		else index += 4;
		m_pBackground[index]->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_BACKGROUND_SELECT");
	}
	else if (INPUT.KeyDown(VK_RETURN))
	{
		if (GAME.SkillPoint > 0)
		{
			if (index == 3)
			{
				if (GAME.SkillLevel[2] >= 3)
				{
					GAME.SkillPoint--;
					GAME.SkillLevel[index]++;
				}
			}
			else
			{
				GAME.SkillPoint--;
				GAME.SkillLevel[index]++;
			}
		}
	}
	m_pSelectIcon->gc<CSpriteRenderer>()->m_pSprite = SPRITE("UI_ST_ICON_0" + to_string(index + 1));
	m_pSelectName_Text->gc<CText>()->m_Text = GAME.SkillName[index];
	char text[100];
	sprintf(text, GAME.SkillTooltip[index].c_str(), (int)GAME.GetValue(index));
	m_pSelectTooltip_Text->gc<CText>()->m_Text = text;
	m_pLevelText->gc<CText>()->m_Text = "[" + to_string(GAME.SkillLevel[index]) + " 레벨]";
	m_pSPText->gc<CText>()->m_Text = "남은 포인트 : " + to_string(GAME.SkillPoint);

}


void CSkillTree::LateUpdate()
{
}

void CSkillTree::OnDestroy()
{
}

void CSkillTree::OnCollision(CGameObject * _pObject)
{
}

void CSkillTree::Enable()
{
	m_bEnable = true;
	CAMERA.m_bScrolling = false;
	INPUT.TimeScale = 0.f;
	m_pSkillTreeWindow->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pBlack->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pBtClose->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pBtClose->gc<CButton>()->m_bEnable = true;
	for (int i = 0; i < 8; i++)
	{
		m_pIcon[i]->gc<CSpriteRenderer>()->m_bEnable = true;
		m_pBackground[i]->gc<CSpriteRenderer>()->m_bEnable = true;
	}

	m_pSelectBackground->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pSelectIcon->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pSelectName->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pSelectTooltip->gc<CSpriteRenderer>()->m_bEnable = true;
	m_pSelectName_Text->gc<CText>()->m_bEnable = true;
	m_pSelectTooltip_Text->gc<CText>()->m_bEnable = true;
	m_pLevelText->gc<CText>()->m_bEnable = true;
	m_pSPText->gc<CText>()->m_bEnable = true;
}

void CSkillTree::Disable()
{
	m_bEnable = false;
	CAMERA.m_bScrolling = true;
	INPUT.GetDeltaMousePos();
	INPUT.TimeScale = 1.f;
	m_pSkillTreeWindow->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pBlack->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pBtClose->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pBtClose->gc<CButton>()->m_bEnable = FALSE;
	for (int i = 0; i < 8; i++)
	{
		m_pIcon[i]->gc<CSpriteRenderer>()->m_bEnable = FALSE;
		m_pBackground[i]->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	}

	m_pSelectBackground->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pSelectIcon->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pSelectName->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pSelectTooltip->gc<CSpriteRenderer>()->m_bEnable = FALSE;
	m_pSelectName_Text->gc<CText>()->m_bEnable = FALSE;
	m_pSelectTooltip_Text->gc<CText>()->m_bEnable = FALSE;
	m_pLevelText->gc<CText>()->m_bEnable = FALSE;
	m_pSPText->gc<CText>()->m_bEnable = FALSE;

}
