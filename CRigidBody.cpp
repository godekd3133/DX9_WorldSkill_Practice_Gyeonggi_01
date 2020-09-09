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
	Vector3 OldPos = tf->m_vPos;
	m_vVelocity.x -= m_vVelocity.x * m_vImpulse.x  * dt;
	m_vVelocity.y -= m_vVelocity.y * 0.035f * dt;
	m_vVelocity.z -= m_vVelocity.z * m_vImpulse.z * dt;
//	m_vVelocity.z-= m_vVelocity.z / m_vVelocity.z * 3000.f * dt;
//	m_vVelocity.x -= m_vVelocity.x / m_vVelocity.x * 3000.f * dt;

	FloorY = m_pMap->GetFloorY(vMovePos ) + Offset;
	//이동할 위치에 충돌했다면


	CollisionInfo info;
	if (vMovePos.y < FloorY+1)
	{
		if (m_vVelocity.y < 0.f)
		{
			m_vVelocity.x = 0.f;
			m_vVelocity.z = 0.f;			
			vMovePos.y = FloorY;
			for (auto iter : OnLanding)
				iter(); 
			m_vVelocity.y = 0.f;



		}
	}
	else
	{
		if (vMovePos.y > FloorY + 1)
		{
			m_vVelocity.y -= 5500.f * dt;
			tf->m_vPos.y = vMovePos.y;
		}
		else
		{

			m_vVelocity.y = 0.f;
			tf->m_vPos.y = FloorY;


		}
	}


	tf->m_vPos.x = vMovePos.x;
	tf->m_vPos.z = vMovePos.z;


	if (m_pMap->GetCollisionInfoByCollisionMap(tf->m_vPos) == MapCollision::Wall ||
		tf->m_vPos.y < m_pMap->GetFloorY(tf->m_vPos))
	{
		tf->m_vPos = OldPos;
		m_vVelocity.x = 0.f ;
		m_vVelocity.z = 0.f;
	}





	m_vOldPos = tf->m_vPos;
}

void CRigidBody::OnDestroy()
{
}

void CRigidBody::OnCollision(CGameObject * _pObject)
{
}

void CRigidBody::AddForce(Vector3 _vVelocitiy)
{
	m_vVelocity += _vVelocitiy;
}
