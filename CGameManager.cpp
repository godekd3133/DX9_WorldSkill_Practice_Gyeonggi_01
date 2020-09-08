#include "DXUT.h"
#include "CGameManager.h"


CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}

void CGameManager::Reset()
{
	this->Level = 1;

	this->MoveSpeed = 300;
	
	this->DamageMul = 1.f;
	this->Damage = 100;
	
	this->CurHp = 500;
	this->MaxHp = 500;

	this->CurExp = 0;
	this->MaxExp = 15000;

	this->SkillPoint = 10;
	this->Skill01Timer = 0.f;
	this->Skill02Timer = 0.f;
	this->Skill01CoolTime = 5.f;
	this->Skill02CoolTime = 7.f;

	for (int i = 0; i < 8; i++)
	{
		this->SkillLevel[i] = 0;
		this->SkillValue[i] = 0;
	}
}
