#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUI::CUI()
	: m_ParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bMouseOn_Prev(false)
	, m_bMouseLBtnDown(false)
{

}

CUI::CUI(const CUI& _Origin)
	: CObj(_Origin)
	, m_ParentUI(nullptr)	 
	, m_bMouseOn(false)
	, m_bMouseOn_Prev(false)
	, m_bMouseLBtnDown(false)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::tick(float _DT)
{
	Super::tick(_DT);

	// 최종 좌표 연산하기
	m_vFinalPos = GetPos();

	if (nullptr != m_ParentUI)
	{
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}

	// 마우스 상태 체크
	m_bMouseOn_Prev = m_bMouseOn;

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + GetScale().x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + GetScale().y)
	{		
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}


	// 자식 UI 들 Tick 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick(_DT);
	}
}

void CUI::render(HDC _dc)
{
	Super::render(_dc);

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}
