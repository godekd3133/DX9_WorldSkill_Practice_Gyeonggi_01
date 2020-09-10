#include "DXUT.h"
#include "CStage02.h"
#include "CPlayerUI.h"

#include "CGameClear.h"

CStage02::CStage02()
{
}


CStage02::~CStage02()
{
}

void CStage02::Init()
{
	GRAPHICS.Play("BGM_STAGE02", true);

	GAME.MaxCombo = 0;
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE02"), SPRITE("UI_MINIMAP_STAGE02"), SPRITE("MAP_STAGE02_COLISIONMAP"));
	GAME.m_pMap = pMap->gc<CStageMap>();
	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();
	GAME.m_pPlayer = pPlayer;
	CGameObject * pUI = OBJ.Create("PLAYERUI");
	pUI->ac<CPlayerUI>();


	GAME.m_pMap = pMap->gc<CStageMap>();
	GAME.Quest = 2;
}

void CStage02::Update()
{
	if (GAME.IsDead)
		SCENE.ChangeScene("S_GAMEOVER"); 
	if (GAME.Quest == 2)
	{
		Vector3 vPos[4] =
		{
			Vector3(-2400,-800, 1830),
			Vector3(-2620,-800, 5900),
			Vector3(-8000,-800, 5100),
			Vector3(-8700,-800, 1800),
		};



		m_fTime += dt;
		if (m_fTime >= 2.f)
		{
			m_fTime = 0.f;
			if (OBJ.Finds(Tag::Enemy).empty() == true)
			{
				for (int i = 0; i <7; i++)
				{
					CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
					pEnemy->ac<CEnemy03>()->Init(vPos[idx]);
				}
				for (int i = 0; i < 3; i++)
				{
					CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
					pEnemy->ac<CEnemy04>()->Init(vPos[idx]);
				}
				idx++;
				if (idx > 3) idx = 0;
			}
		}

		if (GAME.Count >= 100)
		{
			GRAPHICS.dPlay("VFX_BOSS");
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CBoss01>()->Init(Vector3(-8000, -800, 5100));
			GAME.Quest++;
			GAME.Count = 0;
		}
	}
	if (GAME.Quest == 3)
	{
		if (GAME.Count >= 1)
		{
			GAME.Quest++;
			GAME.Count = 0;
			SCENE.ChangeScene("S_GAMECLEAR");
		}
	}


}

void CStage02::Render()
{
	//GRAPHICS.Render_Font("X : " + to_string(GAME.m_pPlayer->tf->m_vPos.x) + "  Y : " + to_string(GAME.m_pPlayer->tf->m_vPos.y) + "  Z : " + to_string(GAME.m_pPlayer->tf->m_vPos.z), GRAPHICS.ToMatrix(Vector3(100, 300, 0)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);
}

void CStage02::Release()
{
	GRAPHICS.Stop("BGM_STAGE02");

}
