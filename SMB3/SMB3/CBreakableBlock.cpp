#include "pch.h"
#include "CBreakableBlock.h"
#include "CAssetMgr.h"

CBreakableBlock::CBreakableBlock()
	:CPlatform()
{
	m_Collider = AddComponent<CCollider>(L"BlockCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -32.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = {Vec2(18, 1), Vec2(16, 16), Vec2(0, 0), 0}; //¿ÞÀ§, Å©±â, offset, duration
	
}

CBreakableBlock::~CBreakableBlock()
{
}
