#include "DXUT.h"
#include "CPlayerMovement.h"


CPlayerMovement::CPlayerMovement()
{
}


CPlayerMovement::~CPlayerMovement()
{
}

void CPlayerMovement::Awake()
{
	ac<CMeshRenderer>()->Init(MESH("PLAYER_ATTACK_01 (1)"));
}

void CPlayerMovement::Start()
{
}

void CPlayerMovement::Update()
{
}

void CPlayerMovement::LateUpdate()
{
}

void CPlayerMovement::OnDestroy()
{
}

void CPlayerMovement::OnCollision()
{
}
