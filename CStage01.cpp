#include "DXUT.h"
#include "CStage01.h"
#include "CPlayerUI.h"

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Init()
{
	GRAPHICS.Play("BGM_STAGE01",true);
	GAME.Reset();
	CGameObject * pMap = OBJ.Create("Map", Tag::Map);
	pMap->ac<CStageMap>()->Init(MESH("MAP_STAGE01"), SPRITE("UI_MINIMAP_STAGE01"), SPRITE("MAP_STAGE01_COLISIONMAP"));
	GAME.m_pMap = pMap->gc<CStageMap>();
	CGameObject * pPlayer = OBJ.Create("Player", Tag::Player);
	pPlayer->ac<CPlayerMovement>();
	GAME.m_pPlayer = pPlayer;
	CGameObject * pUI = OBJ.Create("PLAYERUI");
	pUI->ac<CPlayerUI>();


	GAME.m_pMap = pMap->gc<CStageMap>();
}

void CStage01::Update()
{
	if (GAME.IsDead)
		SCENE.ChangeScene("S_GAMEOVER");
	if (GAME.Quest == 0)
	{
		Vector3 vPos[5] =
		{
			Vector3(-2400,-800, 2343),
			Vector3(-4090,-800, 4930),
			Vector3(-6739,-800, 5100),
			Vector3(-9832,-800, 4100),
			Vector3(-9630,-800, 1650),
		};



		m_fTime += dt;
		if (m_fTime >= 2.f)
		{
			m_fTime = 0.f;
			if (OBJ.Finds(Tag::Enemy).empty() == true)
			{
				for (int i = 0; i < 8; i++)
				{
					CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
					pEnemy->ac<CEnemy01>()->Init(vPos[idx]);
				}
				for (int i = 0; i < 2; i++)
				{
					CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
					pEnemy->ac<CEnemy02>()->Init(vPos[idx]);
				}
				idx++;
				if (idx > 4) idx = 0;
			}
		}

		if (GAME.Count >= 70)
		{
			GRAPHICS.dPlay("VFX_BOSS");
			CGameObject * pEnemy = OBJ.Create("1", Tag::Enemy);
			pEnemy->ac<CBoss02>()->Init(Vector3(-2387,1000, 2343));
			GAME.Quest++;
			GAME.Count = 0;
		}
	}
	if (GAME.Quest == 1)
	{
		if (GAME.Count >= 1)
		{
			GAME.Quest++;
			GAME.Count = 0;
			SCENE.ChangeScene("S_STAGECLEAR");
		}
	}


}

void CStage01::Render()
{
//	GRAPHICS.Render_Font("X : "  + to_string(GAME.m_pPlayer->tf->m_vPos.x) + "  Y : " + to_string(GAME.m_pPlayer->tf->m_vPos.y)  +"  Z : " + to_string(GAME.m_pPlayer->tf->m_vPos.z), GRAPHICS.ToMatrix(Vector3(100, 300, 0)), Color(1.f, 1.f, 1.f, 1.f), RenderMode::RM_UI);

}

void CStage01::Release()
{
	GRAPHICS.Stop("BGM_STAGE01");

}
