#include "DXUT.h"
#include "CTitleScene.h"
#include "CPlayerMovement.h"

CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	CGameObject * TitleBackground = OBJ.Create();
	TitleBackground->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI);
	TitleBackground->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);

	 BT_Start = OBJ.Create();
	BT_Start->ac<CButton>()->Init(SPRITE("TITLE_BT_START"), Vector3(WINSIZEX / 2.f + 600, 500,0), Vector3(1, 1, 1), [=]() {
		SCENE.ChangeScene("S_STAGE01");
	});

	BT_Howto = OBJ.Create();
	BT_Howto->ac<CButton>()->Init(SPRITE("TITLE_BT_HOWTO"), Vector3(WINSIZEX / 2.f + 600, 650, 0), Vector3(1, 1, 1), [=]() {
		m_pBlack->gc<CSpriteRenderer>()->m_bEnable = true;
		m_pWindowHowto->gc<CSpriteRenderer>()->m_bEnable = true;

	});
	
	 BT_Info = OBJ.Create();
	BT_Info->ac<CButton>()->Init(SPRITE("TITLE_BT_INFO"), Vector3(WINSIZEX / 2.f + 600, 800, 0), Vector3(1, 1, 1), [=]() {
		m_pBlack->gc<CSpriteRenderer>()->m_bEnable = true;
		m_pWindowInfo->gc<CSpriteRenderer>()->m_bEnable = true;
	});

	 BT_Exit = OBJ.Create();
	BT_Exit->ac<CButton>()->Init(SPRITE("TITLE_BT_EXIT"), Vector3(WINSIZEX / 2.f + 600, 950, 0), Vector3(1, 1, 1), [=]() {
		PostQuitMessage(0);
	});

	m_pBlack = OBJ.Create();
	m_pBlack->ac<CSpriteRenderer>()->Init(SPRITE("BLACK"), SortingLayer::SR_UI, RenderMode::RM_UI,Color(1,1,1,0.5f));
	m_pBlack->gc<CSpriteRenderer>()->m_bEnable = false;
	m_pBlack->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);

	m_pWindowInfo = OBJ.Create();
	m_pWindowInfo->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_WINDOW_INFO"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pWindowInfo->gc<CSpriteRenderer>()->m_bEnable = false;
	m_pWindowInfo->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.F, 0.f);

	m_pWindowHowto = OBJ.Create();
	m_pWindowHowto->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_WINDOW_HOWTO"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pWindowHowto->gc<CSpriteRenderer>()->m_bEnable = false;
	m_pWindowHowto->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.F, 0.f);
}



void CTitleScene::Update()
{
	if (INPUT.KeyDown(VK_RETURN))
	{
		m_pBlack->gc<CSpriteRenderer>()->m_bEnable = false;
		m_pWindowInfo->gc<CSpriteRenderer>()->m_bEnable = false;
		m_pWindowHowto->gc<CSpriteRenderer>()->m_bEnable = false;
	}
	if (m_pBlack->gc<CSpriteRenderer>()->m_bEnable == true)
	{
		BT_Exit->gc<CButton>()->m_bEnable = false;
		BT_Howto->gc<CButton>()->m_bEnable = false;
		BT_Info->gc<CButton>()->m_bEnable = false;
		BT_Start->gc<CButton>()->m_bEnable = false;
	}

	if (m_pBlack->gc<CSpriteRenderer>()->m_bEnable == false)
	{
		BT_Exit->gc<CButton>()->m_bEnable = true;
		BT_Howto->gc<CButton>()->m_bEnable = true;
		BT_Info->gc<CButton>()->m_bEnable = true;
		BT_Start->gc<CButton>()->m_bEnable = true;
	}
}

void CTitleScene::Render()
{
}

void CTitleScene::Release()
{
}
