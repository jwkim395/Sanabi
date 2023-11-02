#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::tick(float _DT)
{
	if (IsLBtnDown())
	{
		Vec2 vDiff = m_vLbtnDownPos - CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = GetPos();
		vPos -= vDiff;
		SetPos(vPos);

		m_vLbtnDownPos = CKeyMgr::GetInst()->GetMousePos();
	}

	Super::tick(_DT);
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));


	Super::render(_dc);
}

void CPanelUI::LBtnDown(Vec2 _MousePos)
{
	// 마우스 왼쪽 버튼이 눌렸을 때 마우스의 위치를 기록
	m_vLbtnDownPos = _MousePos;
}
