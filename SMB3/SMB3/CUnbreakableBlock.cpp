#include "pch.h"
#include "CUnbreakableBlock.h"
#include "CAssetMgr.h"

CUnbreakableBlock::CUnbreakableBlock(int idx) :CPlatform()
{
	m_Collider = AddComponent<CCollider>(L"BlockCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	if(idx == 4) // 4, 6~11
		imagePos = { Vec2(103, 1), Vec2(16, 16), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
	else if(idx == 6)
		imagePos = { Vec2(188, 120), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 7)
		imagePos = { Vec2(205, 120), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 8)
		imagePos = { Vec2(171, 120), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 9)
		imagePos = { Vec2(188, 137), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 10)
		imagePos = { Vec2(205, 137), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 11)
		imagePos = { Vec2(171, 137), Vec2(16, 16), Vec2(0, 0), 0 };
}

CUnbreakableBlock::~CUnbreakableBlock()
{
}
