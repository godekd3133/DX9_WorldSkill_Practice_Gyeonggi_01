#include "DXUT.h"
#include "CEnemy04.h"


CEnemy04::CEnemy04()
{
}


CEnemy04::~CEnemy04()
{
}

void CEnemy04::Awake()
{
}

void CEnemy04::Start()
{
}

void CEnemy04::Update()
{
}

void CEnemy04::LateUpdate()
{
}

void CEnemy04::OnDestroy()
{
}

void CEnemy04::OnCollision(CGameObject * _pObject)
{
}

void CEnemy04::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(1000, 30, 100, 600);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("IDLE", "ENEMY04_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}
