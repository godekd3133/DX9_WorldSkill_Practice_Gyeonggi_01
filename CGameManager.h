#pragma once
#include "CSingleton.h"
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
	void Reset();
public:
	int Level;
	int CurExp;
	int MaxExp;
	int CurHp;
	int MaxHp;

	float MoveSpeed;
	float Damage = 100.f;
	float DamageMul = 1.f;

	float Skill01CoolTime = 7.f;
	float Skill01Timer = 0.f;

	float Skill02CoolTime = 12.f;
	float Skill02Timer = 0.f;

	int SkillPoint = 10;
	int SkillLevel[8] = { 0, };

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
		"�߰� ���ݷ°� ü���� %d%% ��ŭ �����մϴ�.\n��ũ�ι�ƽ ũ���� 3���� �̻� �ʿ�",
		"������ �뽬�Ͽ� ���� �����ϴ� �뽬 ��ų�� Ȱ��ȭ �˴ϴ�.\n���� �������� %d%% �Դϴ�.",
		"���������� %d%% ��ŭ �����մϴ�.",
		"���� ������ %d%% ��ŭ �����մϴ�.",
		"�⺻ ���ݷ��� %d%% ��ŭ �����մϴ�.",
		"������ %d%% ��ŭ �����մϴ�."
	};

	float SkillValue[8]
	{
		110,
		250,
		5,
		175,
		5,
		20,
		5,
		5
	};
	float SKillValueAdd[8]
	{
		10,
		25,
		5,
		15,
		1,
		2,
		1,
		3
	};
	float GetValue(int _index)
	{
		if (SkillLevel[_index] == 0) return 0;

		return SkillValue[_index] + SKillValueAdd[_index] * (SkillLevel[_index] - 1);
	}

};

#define GAME (*CGameManager::GetInstance())