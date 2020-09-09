#include "DXUT.h"
#include "CGameOver.h"


CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
}

void CGameOver::Init()
{
	GRAPHICS.Play("BGM_GAMEEND", true);
	CAMERA.m_bScrolling = false;
	CGameObject * TitleBackground = OBJ.Create();
	TitleBackground->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI);
	TitleBackground->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);

	CGameObject * Window = OBJ.Create();
	Window->ac<CSpriteRenderer>()->Init(SPRITE("UI_WINDOW_GAMEOVER"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Window->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.F, 0.F);

}

void CGameOver::Update()
{
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (INPUT.KeyDown(i))
			text += i;
	}

	if (INPUT.KeyDown(VK_BACK))
		text.pop_back();

	if (INPUT.KeyDown(VK_RETURN))

	{

		UserInfo INFO;
		INFO.Name = text;
		INFO.Score = GAME.Score;
		GAME.AddData(INFO);
		SCENE.ChangeScene("S_TITLE");
	}
}

void CGameOver::Render()
{
	GRAPHICS.Render_Font(to_string(GAME.Score), GRAPHICS.ToMatrix(Vector3(875, 300, 0), Vector3(0.75f, 0.75f, 1.f)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);
	GRAPHICS.Render_Font(text, GRAPHICS.ToMatrix(Vector3(875, 490, 0), Vector3(0.75f, 0.75f, 1.f)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CGameOver::Release()
{
	GRAPHICS.Stop("BGM_GAMEEND");

}
