#include "DXUT.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CStage01.h"
CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{

	std::future<void> a =
		std::async(launch::async, [=]() {
		AddMesh("MAP_STAGE01", "Map/Stage01/Stage01", "Map/Stage01");
		AddMesh("MAP_STAGE02", "Map/Stage02/Stage02", "Map/Stage02");
		AddSprite("UI_MINIMAP_STAGE01", "UI/Minimap_Stage01");
		AddSprite("UI_MINIMAP_STAGE02", "UI/Minimap_Stage02");
		AddSprite("UI_MINIMAP_PLAYER", "UI/Minimap_Player");
		AddSprite("UI_MINIMAP_ENEMY", "UI/Minimap_Enemy");

		AddMesh("PLAYER_IDLE", "Player/Animation/Idle/Idle", "Player",41);
		AddMesh("PLAYER_RUN", "Player/Animation/Run/Run", "Player", 15);
		AddMesh("PLAYER_HIT", "Player/Animation/Hit/Hit", "Player", 11);
		AddMesh("PLAYER_DEAD", "Player/Animation/Dead/Dead", "Player",36);
		AddMesh("PLAYER_ATTACK01", "Player/Animation/Attack01/Attack01", "Player", 16);
		AddMesh("PLAYER_ATTACK02", "Player/Animation/Attack02/Attack02", "Player", 16);
		AddMesh("PLAYER_ATTACK03", "Player/Animation/Attack03/Attack03", "Player", 24);
		AddMesh("PLAYER_ATTACK04", "Player/Animation/Attack04/Attack04", "Player", 28);
		AddMesh("PLAYER_ATTACK05", "Player/Animation/Attack05/Attack05", "Player", 51);
		AddMesh("PLAYER_ATTACK06", "Player/Animation/Attack06/Attack06", "Player", 31);
		AddMesh("PLAYER_ATTACK07", "Player/Animation/Attack07/Attack07", "Player", 32);
		
		//BOSS01
		AddMesh("BOSS01_ATTACK01", "BOSS01/Animation/Attack01/Attack01", "Boss01",31);
		AddMesh("BOSS01_ATTACK02", "BOSS01/Animation/Attack02/Attack02", "Boss01", 41);
		AddMesh("BOSS01_ATTACK03", "BOSS01/Animation/Attack03/Attack03", "Boss01", 41);
		AddMesh("BOSS01_ATTACK04", "BOSS01/Animation/Attack04/Attack04", "Boss01", 51);
		AddMesh("BOSS01_DEAD", "BOSS01/Animation/Dead/Dead", "Boss01", 61);
		AddMesh("BOSS01_HIT", "BOSS01/Animation/Hit/Hit", "Boss01", 16);
		AddMesh("BOSS01_IDLE", "BOSS01/Animation/Idle/Idle", "Boss01", 31);// 41);
		AddMesh("BOSS01_RUN", "BOSS01/Animation/Run/Run", "Boss01", 31);
		
		//BOSS02
		AddMesh("BOSS02_ATTACK01", "BOSS02/Animation/Attack01/Attack01", "Boss02", 41);
		AddMesh("BOSS02_ATTACK02", "BOSS02/Animation/Attack02/Attack02", "Boss02", 38);
		AddMesh("BOSS02_ATTACK03", "BOSS02/Animation/Attack03/Attack03", "Boss02", 41);
		AddMesh("BOSS02_DEAD", "BOSS02/Animation/Dead/Dead", "Boss02", 36);
		AddMesh("BOSS02_HIT", "BOSS02/Animation/Hit/Hit", "Boss02", 11);
		AddMesh("BOSS02_IDLE", "BOSS02/Animation/Idle/Idle", "Boss02", 61);// 41);
		AddMesh("BOSS02_RUN", "BOSS02/Animation/Run/Run", "Boss02", 25);
		
		//ENEMY01
		AddMesh("ENEMY01_ATTACK", "Enemy01/Animation/Attack/Attack", "Enemy01", 16);
		AddMesh("ENEMY01_DEAD", "Enemy01/Animation/Dead/Dead", "Enemy01", 31);
		AddMesh("ENEMY01_HIT", "Enemy01/Animation/Hit/Hit", "Enemy01", 11);
		AddMesh("ENEMY01_IDLE", "Enemy01/Animation/Idle/Idle", "Enemy01",41);// 41);
		AddMesh("ENEMY01_RUN", "Enemy01/Animation/Run/Run", "Enemy01", 16);
		
		//ENEMY02
		AddMesh("ENEMY02_ATTACK", "Enemy02/Animation/Attack01/Attack01", "Enemy02", 36);
		AddMesh("ENEMY02_DEAD", "Enemy02/Animation/Dead/Dead", "Enemy02", 36);
		AddMesh("ENEMY02_HIT", "Enemy02/Animation/Hit/Hit", "Enemy02", 11);
		AddMesh("ENEMY02_IDLE", "Enemy02/Animation/Idle/Idle", "Enemy02", 61);// 41);
		AddMesh("ENEMY02_RUN", "Enemy02/Animation/Run/Run", "Enemy02", 29);
		
		//ENEMY03
		AddMesh("ENEMY03_ATTACK", "Enemy03/Animation/Attack/Attack", "Enemy03", 41);
		AddMesh("ENEMY03_DEAD", "Enemy03/Animation/Dead/Dead", "Enemy03", 82);
		AddMesh("ENEMY03_HIT", "Enemy03/Animation/Hit/Hit", "Enemy03", 12);
		AddMesh("ENEMY03_IDLE", "Enemy03/Animation/Idle/Idle", "Enemy03", 61);// 41);
		AddMesh("ENEMY03_RUN", "Enemy03/Animation/Run/Run", "Enemy03", 31);
		
		//ENEMY04
		AddMesh("ENEMY04_ATTACK", "Enemy04/Animation/Attack/Attack", "Enemy04", 16);
		AddMesh("ENEMY04_DEAD", "Enemy04/Animation/Dead/Dead", "Enemy04", 61);
		AddMesh("ENEMY04_HIT", "Enemy04/Animation/Hit/Hit", "Enemy04", 11);
		AddMesh("ENEMY04_IDLE", "Enemy04/Animation/Idle/Idle", "Enemy04", 51);// 41);
		AddMesh("ENEMY04_RUN", "Enemy04/Animation/Run/Run", "Enemy04", 15);

		//MAP
		AddSprite("MAP_STAGE01_COLISIONMAP", "Map/Stage01/NormalMap copy");
		AddSprite("MAP_STAGE01_MINIMAP", "Map/Stage01/NormalMap");
		AddSprite("MAP_STAGE01_PLAYER", "Map/Stage01/Player");
		//MAP
		AddSprite("MAP_STAGE02_COLISIONMAP", "Map/Stage02/NormalMap copy");
		AddSprite("MAP_STAGE02_MINIMAP", "Map/Stage02/NormalMap");
		AddSprite("MAP_STAGE02_PLAYER", "Map/Stage02/Player");


		//EFFECT
		AddSprite("EFFECT_PLAYERATTACK01", "Effect/PlayerAttack01/PlayerAttack01", 5);
		AddSprite("EFFECT_PLAYERATTACK02", "Effect/PlayerAttack02/PlayerAttack02", 5);
		AddSprite("EFFECT_PLAYERSKILL02", "Effect/PlayerSkill02/PlayerSkill02", 7);

		AddSprite("UI_DAMAGEFONT", "UI/Font/Combo03/Damage",10);

		AddSprite("UI_HPBAR_BG", "UI/hp_ui_1");
		AddSprite("UI_HPBAR", "UI/enemy_hpbar");
		AddSprite("UI_HPBAR_YELLOW", "UI/enemy_hpbar_yellow");
		AddSprite("UI_MONSTER_HPICON", "UI/enemy_hp");
		AddSprite("UI_SHADOW", "UI/Shadow");

		AddSprite("UI_PLAYERSTATUS_01", "UI/PlayerStatus_01");
		AddSprite("UI_PLAYERSTATUS_02", "UI/PlayerStatus_02");
		AddSprite("UI_PLAYERSTATUS_03", "UI/PlayerStatus_03");
		AddSprite("UI_PLAYERSTATUS_HPBAR", "UI/hp_bar");
		AddSprite("UI_PLAYERSTATUS_HPBAR_YELLOW", "UI/hp_bar_Yellow");
		AddSprite("UI_PLAYERSTATUS_HPBAR_BG", "UI/HpBarBackground");
		AddSprite("UI_PLAYERSTATUS_EXPBAR", "UI/exp_bar");
		AddSprite("UI_PLAYERSTATUS_EXPBAR_BG", "UI/ExpBarBackground");




		AddSprite("UI_ST_BACKGROUND", "UI/SkillTree/ST_Background");
		AddSprite("UI_ST_BT_CLOSE", "UI/SkillTree/ST_BtClose");

		AddSprite("UI_ST_ICON_01", "UI/SkillTree/ST_Icon_01");
		AddSprite("UI_ST_ICON_01_DISABLE", "UI/SkillTree/ST_Icon_01_Disable");
		AddSprite("UI_ST_ICON_02", "UI/SkillTree/ST_Icon_02");
		AddSprite("UI_ST_ICON_02_DISABLE", "UI/SkillTree/ST_Icon_02_Disable");
		AddSprite("UI_ST_ICON_03", "UI/SkillTree/ST_Icon_03");
		AddSprite("UI_ST_ICON_03_DISABLE", "UI/SkillTree/ST_Icon_03_Disable");
		AddSprite("UI_ST_ICON_04", "UI/SkillTree/ST_Icon_04");
		AddSprite("UI_ST_ICON_04_DISABLE", "UI/SkillTree/ST_Icon_04_Disable");
		AddSprite("UI_ST_ICON_05", "UI/SkillTree/ST_Icon_05");
		AddSprite("UI_ST_ICON_05_DISABLE", "UI/SkillTree/ST_Icon_05_Disable");
		AddSprite("UI_ST_ICON_06", "UI/SkillTree/ST_Icon_06");
		AddSprite("UI_ST_ICON_06_DISABLE", "UI/SkillTree/ST_Icon_06_Disable");
		AddSprite("UI_ST_ICON_07", "UI/SkillTree/ST_Icon_07");
		AddSprite("UI_ST_ICON_07_DISABLE", "UI/SkillTree/ST_Icon_07_Disable");
		AddSprite("UI_ST_ICON_08", "UI/SkillTree/ST_Icon_08");
		AddSprite("UI_ST_ICON_08_DISABLE", "UI/SkillTree/ST_Icon_08_Disable");

		AddSprite("UI_ST_ICON_BACKGROUND", "UI/SkillTree/ST_IconBackground");
		AddSprite("UI_ST_ICON_BACKGROUND_SELECT", "UI/SkillTree/ST_IconBackground_Select");
		AddSprite("UI_ST_ICON_NAME", "UI/SkillTree/ST_Name");
		AddSprite("UI_ST_ICON_TOOLTIP", "UI/SkillTree/ST_Tooltip");
		AddSprite("UI_ST_SELECT_BACKGROUND", "UI/SkillTree/ST_SelectBackground");
		AddSprite("UI_ST_SELECT_NAME", "UI/SkillTree/ST_Name");
		AddSprite("UI_ST_SELECT_TOOLTIP", "UI/SkillTree/ST_Tooltip");
		AddSprite("UI_SKILLICON_BG", "UI/icon_background");
		AddSprite("UI_SKILLICON01", "UI/icon_1");
		AddSprite("UI_SKILLICON02", "UI/icon_2");
		AddSprite("UI_SKILLICON_COOLTIME", "UI/icon_2");
		AddSprite("UI_SKILLICON02", "UI/icon_2");

		AddSprite("TITLE_BACKGROUND", "Title/Background");
		AddSprite("TITLE_BT_START", "Title/BtGameStart");
		AddSprite("TITLE_BT_HOWTO", "Title/BtHowto");
		AddSprite("TITLE_BT_INFO", "Title/BtInfo");
		AddSprite("TITLE_BT_EXIT", "Title/BtExit");
		AddSprite("TITLE_WINDOW_INFO", "Title/Window_Info");
		AddSprite("TITLE_WINDOW_HOWTO", "Title/Window_Howto");
		AddSprite("BLACK", "Black");
});

	SCENE.AddScene("S_TITLE", new CTitleScene());
	SCENE.AddScene("S_STAGE01", new CStage01());
	SCENE.ChangeScene("S_TITLE");

}

void CMainGame::Update()
{
	INPUT.Update();

	SCENE.Update();

	OBJ.Update();

	CAMERA.Update();

	INPUT.TimeScale = Lerp(INPUT.TimeScale, 1.f, udt * 10);
}

void CMainGame::Render()
{

	CAMERA.SetTransform();

	SCENE.Render();

	OBJ.Render();
}

void CMainGame::Release()
{
	CInputManager::ReleaseInstance();
	CGraphicsManager::ReleaseInstance();
	CSceneManager::ReleaseInstance();
	CObjectManager::ReleaseInstance();
	CCameraManager::ReleaseInstance();
}

void CMainGame::OnLostDevice()
{
	GRAPHICS.OnLostDevice();
}

void CMainGame::OnResetDevice()
{
	GRAPHICS.OnResetDevice();
}

void CMainGame::AddSprite(string _Key, string _Path, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".png";
		GRAPHICS.AddSprite(Key, Path);
	}
	else
	{
		for (int i = 0; i < _Count; i++)
		{
			string Key = _Key + " (" + to_string(i + 1) + ")";
			string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").png";
			GRAPHICS.AddSprite(Key, Path);

		}
	}
}

void CMainGame::AddMesh(string _Key, string _Path, string _MapPath, int _Count)
{
	if (_Count == 0)
	{
		string Key = _Key;
		string Path = "./resource/" + _Path + ".obj";
		string MapPath = "./resource/" + _MapPath + "/";
		GRAPHICS.AddMesh(Key, Path, MapPath);
	}
	else
	{
			for (int i = 0; i < _Count; i++)
		{


					string Key = _Key + " (" + to_string(i + 1) + ")";
					string Path = "./resource/" + _Path + " (" + to_string(i + 1) + ").obj";
					string MapPath = "./resource/" + _MapPath + "/";
					GRAPHICS.AddMesh(Key, Path, MapPath);
		}

	}
}
