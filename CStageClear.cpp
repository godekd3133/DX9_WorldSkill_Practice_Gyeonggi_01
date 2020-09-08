#include "DXUT.h"
#include "CStageClear.h"


CStageClear::CStageClear()
{
}


CStageClear::~CStageClear()
{
}

void CStageClear::Init()
{
	CGameObject * TitleBackground = OBJ.Create();
	TitleBackground->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI);
	TitleBackground->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
}

void CStageClear::Update()
{
	if (INPUT.KeyDown(VK_RETURN))
		SCENE.ChangeScene("S_STAGE01");
}

void CStageClear::Render()
{
}

void CStageClear::Release()
{
}
