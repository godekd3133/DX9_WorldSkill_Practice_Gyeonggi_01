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
		return Damage + (Damage  * (1.f / max(1,GetValue(7)))* (DamageMul + GetValue(2) / 100.f));
	}

	int SkillPoint = 10;
	int SkillLevel[8] = { 0, };
	int Quest=0;
	int Count = 0;
	string QuestString[4] =
	{
		"���� 200 ���� óġ�ϼ���. [ %d / 200 ]",
		"������ óġ�ϼ���. [ %d / 1 ]",
		"���� 300 ���� óġ�ϼ���. [ %d / 300 ]",
		"������ óġ�ϼ���. [ %d / 1 ]"
	};
	string SkillName[8] = {
		"���� ����",
		"��ũ�ι�ƽ ũ����",
		"��ü �ܷ�",
		"�뽬",
		"ü�� ���",	
		"����",
		"�⺻ ����",
		"��� ��ȭ"
	};

	string SkillTooltip[8] = {
		"�⺻ ������ ��ȭ�ǿ� 2Ÿ ������ �Ҽ� �ְԵ˴ϴ�.\n2Ÿ ������ �������� %d%%�Դϴ�. ",
		"������� ��ų�� ��ũ�ι�ƽ ũ������ ��ȭ�˴ϴ�.\n��ũ�ι�ƽ ũ������ �������� %d%% �Դϴ�.",
		"�߰� ���ݷ°� ü���� %d%% ��ŭ �����մϴ�.",
		"������ �뽬�Ͽ� ���� �����ϴ� �뽬 ��ų�� Ȱ��ȭ �˴ϴ�.\n���� �������� %d%% �Դϴ�.\n��ũ�ι�ƽ ũ���� 3���� �̻� �ʿ�",
		"���������� %d%% ��ŭ �����մϴ�.",
		"���� ������ %d%% ��ŭ �����մϴ�.",
		"�⺻ ���ݷ��� %d ��ŭ �����մϴ�.",
		"������ %d%% ��ŭ �����մϴ�."
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
		7,
		15,
		1,
		3,
		7,
		3
	};
	int  GetMaxHp() { return MaxHp + MaxHp * max(1.f, GetValue(2)); }
	
	float GetValue (int _index)
	{
		if (SkillLevel[_index] == 0) return 0;

		return SkillValue[_index] + SKillValueAdd[_index] * (SkillLevel[_index] - 1);
	}

};

#define GAME (*CGameManager::GetInstance())