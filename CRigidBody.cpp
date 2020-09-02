#include "DXUT.h"
#include "CRigidBody.h"


CRigidBody::CRigidBody()
{
	m_vVelocity = Vector3(0, 0, 0);
}


CRigidBody::~CRigidBody()
{
}

void CRigidBody::Awake()
{
}

void CRigidBody::Start()
{
	m_pMap = OBJ.Find(Tag::Map)->gc<CStageMap>();
}

void CRigidBody::Update()
{
}

void CRigidBody::LateUpdate()
{

	float FloorY = -1200.f;
	Vector3 vMovePos = tf->m_vPos + m_vVelocity * dt;
	m_vVelocity.x *= 0.94f;
	m_vVelocity.y *= 0.98f;
	m_vVelocity.z *= 0.94f;

	FloorY = m_pMap->GetFloorY(vMovePos);
	//이동할 위치에 충돌했다면

	if (m_vVelocity.y < 0.f)
	{
		CollisionInfo info;
		if (m_pMap->GetCollisionInfoByRay(vMovePos, Vector3(0, -1, 0), 10, info) == true)
		{
			tf->m_vPos.y = FloorY;
			for (auto iter : OnLanding)
			{
				iter();
			}
			m_vVelocity.y = 0.f;
			m_vVelocity.x = 0.f;
		}
	}
	if (vMovePos.y > FloorY+1)
	{
		tf->m_vPos.y = vMovePos.y;

		m_vVelocity.y -= 3000.f * dt;
	}
	else
	{
		tf->m_vPos.y = FloorY;
	}

	tf->m_vPos.x = vMovePos.x;
	tf->m_vPos.z = vMovePos.z;




	m_vOldPos = tf->m_vPos;
}

void CRigidBody::OnDestroy()
{
}

void CRigidBody::OnCollision()
{
}

void CRigidBody::AddForce(Vector3 _vVelocitiy)
{
	m_vVelocity += _vVelocitiy;
}
