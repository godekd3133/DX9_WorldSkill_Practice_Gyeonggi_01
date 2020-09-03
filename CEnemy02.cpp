#include "DXUT.h"
#include "CEnemy02.h"


CEnemy02::CEnemy02()
{
}


CEnemy02::~CEnemy02()
{
}

void CEnemy02::Awake()
{
}

void CEnemy02::Start()
{
}

void CEnemy02::Update()
{
}

void CEnemy02::LateUpdate()
{
}

void CEnemy02::OnDestroy()
{
}

void CEnemy02::OnCollision(CGameObject * _pObject)
{
}

void CEnemy02::Init(Vector3 _vPos)
{
	tf->m_vScale = Vector3(1.5f, 1.5f, 1.5f);
	tf->m_vPos = _vPos;
	ac<CEnemy>()->Init(1000, 30, 100);
	ac<CMeshRenderer>()->Init(nullptr);
	ac<CRigidBody>();
	ac<CAnimator3D>()->AddState("IDLE", "ENEMY02_IDLE", 30.F / 1000.F);
	gc<CAnimator3D>()->SetCurrentState("IDLE");
}
