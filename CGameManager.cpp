#include "DXUT.h"
#include "CGameManager.h"


CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}

void CGameManager::GainExp(float _Exp)
{
	CurExp += _Exp;
	if (CurExp > MaxExp)
	{
		if (m_pPlayer)
		{
			EFFECT(m_pPlayer->tf->m_vPos, Vector3(0.25f, 0.25f, 0.25f), "EFFECT_LEVELUP");
		}
		CurExp = 0;
		CurHp = GetMaxHp();
		Level++;
		MaxExp *= 1.1f;
		SkillPoint += 3;
	}
}

void CGameManager::GainHp(float _Hp)
{
	CurHp += _Hp;
	if (CurHp > GetMaxHp())
		CurHp = GetMaxHp();

}

void CGameManager::Hit(float _Damage)
{
	if(God == false)
	CurHp -= _Damage;
	if (CurHp <= 0)
		IsDead = true;
}

void CGameManager::SaveData()
{

}

void CGameManager::LoadData()
{
}

void CGameManager::Reset()
{
	God = true;
	m_pPlayer = nullptr;
	m_pMap = nullptr;

	this->MaxCombo = 0;
	this->Level = 1;
	this->Score = 0;
	this->KillCount = 0;

	this->Quest = 0;
	this->Combo = 0;
	this->Count = 0;
	this->IsDead = false;

	this->MoveSpeed = 300;
	
	this->DamageMul = 1.f;
	this->Damage = 100;
	
	this->CurHp = 500;
	this->MaxHp = 500;

	this->CurExp = 0;
	this->MaxExp = 3000;

	this->SkillPoint = 10;
	this->Skill01Timer = 0.f;
	this->Skill02Timer = 0.f;
	this->Skill01CoolTime = 4.f;
	this->Skill02CoolTime = 7.f;

	for (int i = 0; i < 8; i++)
	{
		this->SkillLevel[i] = 0;
	}
}

void CGameManager::AddData(UserInfo _Info)
{
	m_Info.push_back(_Info);
	std::sort(m_Info.begin(), m_Info.end(), [](UserInfo _Prev, UserInfo _Next) {return _Prev.Score > _Next.Score; });
}
