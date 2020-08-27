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
	ac<CAnimator3D>()->AddState("IDLE", "PLAYER_IDLE", 30.f / 1000.f);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}

void CPlayerMovement::Start()
{
	CAMERA.Follow(go, 6.f);
}

void CPlayerMovement::Update()
{
	if (INPUT->KeyPress(VK_LEFT))
		tf->m_vPos += Vector3(-1, 0, 0) * 100 * dt;
	if (INPUT->KeyPress(VK_RIGHT))
		tf->m_vPos += Vector3(1, 0, 0) * 100 * dt;

	if (INPUT->KeyPress(VK_UP))
		tf->m_vPos += Vector3(0, 0, 1) * 100 * dt;
	if (INPUT->KeyPress(VK_DOWN))
		tf->m_vPos += Vector3(0, 0, -1) * 100 * dt;

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
