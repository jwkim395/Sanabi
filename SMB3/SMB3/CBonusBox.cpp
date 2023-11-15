#include "pch.h"
#include "CBonusBox.h"
#include "CAssetMgr.h"

CBonusBox::CBonusBox()
{
	m_Collider = AddComponent<CCollider>(L"PipeCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = { Vec2(35, 1), Vec2(16, 16), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
}

CBonusBox::~CBonusBox()
{
}
