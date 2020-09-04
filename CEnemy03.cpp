#include "DXUT.h"
#include "CEnemy03.h"


CEnemy03::CEnemy03()
{
}


CEnemy03::~CEnemy03()
{
}

void CEnemy03::Awake()
{
}

void CEnemy03::Start()
{
}

void CEnemy03::Update()
{
}

void CEnemy03::LateUpdate()
{
}

void CEnemy03::OnDestroy()
{
}

void CEnemy03::OnCollision(CGameObject * _pObject)
{
}

void CEnemy03::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(1000, 30, 100, 900);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("IDLE", "ENEMY03_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}
