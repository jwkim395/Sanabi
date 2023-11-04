#include "pch.h"
#include "CImageUI.h"
#include "CTexture.h"
#include "CTile.h"
#include "CLevelMgr.h"

void CImageUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CImageUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (nullptr != m_CurImg)
	{

	}
	else
	{
		m_Tile->SetPos(vPos);
		m_Tile->SetScale(vScale);
		if(selected)
			m_Tile->renderInUI(_dc, 120);
		else
			m_Tile->renderInUI(_dc, 255);
	}
	Super::render(_dc);
}

void CImageUI::LBtnClicked(Vec2 _vMousePos)
{
	CImageUI* curSel = CLevelMgr::GetInst()->GetTile();
	if (nullptr != curSel) {
		curSel->setCurImgToNormal();
		CLevelMgr::GetInst()->GetTile()->selected = false;
	}
	m_CurImg = m_PressedImg;
	selected = true;
	CLevelMgr::GetInst()->SetTile(this);
}

CImageUI::CImageUI()
	: m_NormalImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_Tile(nullptr)
{
	m_Tile = new CTile;
}

CImageUI::CImageUI(CTexture* t)
	: m_NormalImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_Tile(nullptr)
{
	m_Tile = new CTile;
	m_Tile->SetAtlas(t);
}

CImageUI::~CImageUI()
{
	delete m_Tile;
}
