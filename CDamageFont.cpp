#include "DXUT.h"
#include "CDamageFont.h"


CDamageFont::CDamageFont()
{
}


CDamageFont::~CDamageFont()
{
}

void CDamageFont::Awake()
{
}

void CDamageFont::Start()
{
}

void CDamageFont::Update()
{
	for (int i = 0; i < m_vecFontObject.size(); i++)
	{
		m_vecFontObject[i]->tf->m_vScale = tf->m_vScale;
		m_vecFontObject[i]->tf->m_vScale.y = -m_vecFontObject[i]->tf->m_vScale.y;
	}
	SetTransform();
}

void CDamageFont::LateUpdate()
{
}

void CDamageFont::OnDestroy()
{
}

void CDamageFont::OnCollision(CGameObject * _pObject)
{
}

void CDamageFont::Init(Vector3 _vPos, int _Damage)
{
	string strDamage = to_string(_Damage);
	tf->m_vPos = _vPos;

	for (int i = 0; i < strDamage.size(); i++)
	{
		CGameObject * pFontObject = OBJ.Create();
		pFontObject->ac<CSpriteRenderer>()->Init(
			SPRITE("UI_DAMAGEFONT (" + to_string(strDamage[i] - '0' + 1) + ")"),
			SortingLayer::SR_UI,
			RenderMode::RM_Billboard
		);
		m_vecFontObject.push_back(pFontObject);
	}


	m_vSize = Vector2(SPRITE("UI_DAMAGEFONT (1)")->m_Info.Width, SPRITE("UI_DAMAGEFONT (1)")->m_Info.Height);
	for (int i = 0; i < m_vecFontObject.size(); i++)
	{
		m_vecFontObject[i]->tf->m_vPos = tf->m_vPos;
		m_vecFontObject[i]->tf->m_vScale = tf->m_vScale;
		m_vecFontObject[i]->tf->m_vScale.y = -m_vecFontObject[i]->tf->m_vScale.y;
	}

	Vector3 Scale = tf->m_vScale;
	sa->Add(
		[=]()->bool {
		tf->m_vScale = Lerp(tf->m_vScale, Scale*2, dt *24);
		return true;
	}, 0.25f
	);
	sa->Add(
		[=]()->bool {
		tf->m_vScale = Lerp(tf->m_vScale, Scale, dt * 24);
		return true;
	}, 0.25f
	);
	sa->Delay(0.33f);
	sa->Add(
		[=]()->bool {
		for (auto iter : m_vecFontObject)
		{
			iter->gc<CSpriteRenderer>()->m_Color = Lerp(iter->gc<CSpriteRenderer>()->m_Color, Color(1, 1, 1, 0), dt * 24);
		}
		return true;
	}, 0.1f
	);
	sa->Add(
		[=]()->bool {
		for (auto iter : m_vecFontObject)
		{
			iter->Destroy();
		}
		go->Destroy();
		return false;
	}
	);
}

void CDamageFont::SetTransform()
{
	int half = m_vecFontObject.size()/2;
	for (int i = 0; i <= m_vecFontObject.size()/2; i++)
	{
		m_vecFontObject[half +i]->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f - (float)i, 0.5f);
		m_vecFontObject[half -i]->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f + (float)i, 0.5f);
	}
}
