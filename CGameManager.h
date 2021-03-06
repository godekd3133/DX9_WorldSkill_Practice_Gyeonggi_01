#pragma once
#include "CSingleton.h"
struct UserInfo {
	string Name;
		int Score;
};
class CGameManager :
	public CSingleton< CGameManager>
{
public:
	CGameManager();
	~CGameManager();
public:
	CGameObject * m_pPlayer = nullptr;
	CStageMap * m_pMap = nullptr;

public:
	void  GainExp(float _Exp);
	void GainHp(float _Hp);
	void Hit(float _Damage);
	void SaveData();
	void LoadData();
	bool IsDead = false;
	void Reset();
public:
	int Level;
	int CurExp;
	int MaxExp;
	int CurHp;
	int MaxHp;

	float MoveSpeed;
	float Damage = 100.f;
	int Score = 0;
	float DamageMul = 1.f;
	vector< UserInfo> m_Info;
	void AddData(UserInfo _Info);
	float Skill01CoolTime = 7.f;
	float Skill01Timer = 0.f;

	int Combo = 0;
	int MaxCombo = 0;
	int KillCount = 0;
	bool God = false;
	float Skill02CoolTime = 12.f;
	float Skill02Timer = 0.f;
	int GetFinalDamage()
	{
		float Base = Damage + Damage *  max(0, GetValue(7)) / 100.f;
		return Base * max(1.f, DamageMul + GetValue(2) / 100.f);
	}

	int SkillPoint = 10;
	int SkillLevel[8] = { 0, };
	int Quest=0;
	int Count = 0;
	string QuestString[4] =
	{
		"적을 70 마리 처치하세요. [ %d / 70 ]",
		"보스를 처치하세요. [ %d / 1 ]",
		"적을 100 마리 처치하세요. [ %d / 100 ]",
		"보스를 처치하세요. [ %d / 1 ]"
	};
	string SkillName[8] = {
		"무술 숙련",
		"아크로바틱 크래쉬",
		"신체 단련",
		"대쉬",
		"체력 흡수",	
		"간파",
		"기본 숙련",
		"방어 강화"
	};

	string SkillTooltip[8] = {
		"기본 공격이 강화되여 2타 공격을 할수 있게됩니다.\n2타 공격의 데미지는 %d%%입니다. ",
		"내려찍기 스킬이 아크로바틱 크래쉬로 강화됩니다.\n아크로바틱 크래쉬의 데미지는 %d%% 입니다.",
		"추가 공격력과 체력이 %d%% 만큼 증가합니다.",
		"빠르게 대쉬하여 적을 공격하는 대쉬 스킬이 활성화 됩니다.\n착지 데미지는 %d%% 입니다.\n아크로바틱 크래쉬 3레벨 이상 필요",
		"생명력흡수가 %d%% 만큼 증가합니다.",
		"적의 방어력을 %d%% 만큼 무시합니다.",
		"기본 공격력이 %d 만큼 증가합니다.",
		"방어력이 %d%% 만큼 증가합니다."
	};

	float SkillValue[8]
	{
		110,
		250,
		10,
		175,
		5,
		20,
		10,
		5
	};
	float SKillValueAdd[8]
	{
		10,
		25,
		12,
		15,
		1,
		3,
		10,
		3
	};
	int  GetMaxHp() { return MaxHp + MaxHp * max(0.f, GetValue(2)); }
	
	float GetValue (int _index)
	{
		if (SkillLevel[_index] == 0) return 0;

		return SkillValue[_index] + SKillValueAdd[_index] * (SkillLevel[_index] - 1);
	}

};

#define GAME (*CGameManager::GetInstance())