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
	GRAPHICS.Play("BGM_GAMEEND", true);
	CAMERA.m_bScrolling = false;
	CGameObject * TitleBackground = OBJ.Create();
	TitleBackground->ac<CSpriteRenderer>()->Init(SPRITE("TITLE_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI);
	TitleBackground->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);

	CGameObject * Window = OBJ.Create();
	Window->ac<CSpriteRenderer>()->Init(SPRITE("UI_WINDOW_STAGECLEAR"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Window->tf->m_vPos = Vector3(WINSIZEX / 2.F, WINSIZEY / 2.F, 0.F);
}

void CStageClear::Update()
{

	if (INPUT.KeyDown(VK_RETURN))
	{
		SCENE.ChangeScene("S_STAGE02");
		GAME.Combo += GAME.Level * 10000;
		GAME.Combo += GAME.MaxCombo * 100;
	}


}

void CStageClear::Render()
{
	GRAPHICS.Render_Font(to_string(GAME.Score), GRAPHICS.ToMatrix(Vector3(920, 370, 0), Vector3(0.75f, 0.75f, 1.f)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);
	GRAPHICS.Render_Font(to_string(GAME.Level * 10000), GRAPHICS.ToMatrix(Vector3(920, 480, 0), Vector3(0.75f, 0.75f, 1.f)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);
	GRAPHICS.Render_Font(to_string(GAME.MaxCombo * 100), GRAPHICS.ToMatrix(Vector3(920, 590, 0), Vector3(0.75f, 0.75f, 1.f)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CStageClear::Release()
{
	GRAPHICS.Stop("BGM_GAMEEND");

}
