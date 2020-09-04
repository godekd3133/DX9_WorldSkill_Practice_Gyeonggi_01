#include "DXUT.h"
#include "CEnemy01.h"


CEnemy01::CEnemy01()
{
}


CEnemy01::~CEnemy01()
{
}

void CEnemy01::Awake()
{
}

void CEnemy01::Start()
{
}

void CEnemy01::Update()
{
}

void CEnemy01::LateUpdate()
{
}

void CEnemy01::OnDestroy()
{
}

void CEnemy01::OnCollision(CGameObject * _pObject)
{
}

void CEnemy01::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f); 
	tf->m_vPos = _vPos; 
	ac<CEnemy>()->Init(1000, 30, 100,1000);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("IDLE", "ENEMY01_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}
