#include "pch.h"
#include "CBtnUI.h"

#include "CEngine.h"
#include "resource.h"
#include "CTexture.h"

#include "CKeyMgr.h"

CBtnUI::CBtnUI()
	: m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_CallBackFunc(nullptr)
	, m_Inst(nullptr)
	, m_Delegate(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (nullptr != m_CurImg)
	{
	}
	else
	{
		/*
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, int(vPos.x)
			, int(vPos.y)
			, m_CurImg->GetWidth(), m_CurImg->GetHeight()
			, m_CurImg->GetDC()
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y)
			, m_CurImg->GetWidth(), m_CurImg->GetHeight()
			, blend);*/
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}	

	// 부모클래스(CUI) 렌더함수 호출(자식 UI 들한테 render 를 호출한다)
	Super::render(_dc);
}

void CBtnUI::OnHovered(Vec2 _vMousePos)
{
}

void CBtnUI::MouseOn(Vec2 _vMousePos)
{
}

void CBtnUI::OnUnHovered(Vec2 _vMousePos)
{
}


void CBtnUI::LBtnDown(Vec2 _vMousePos)
{
}

void CBtnUI::LBtnUp(Vec2 _vMousePos)
{
}

INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CBtnUI::LBtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_CallBackFunc)
	{
		m_CallBackFunc();
	}

	if (nullptr != m_Inst && nullptr != m_Delegate)
	{
		(m_Inst->*m_Delegate)();
	}
}
