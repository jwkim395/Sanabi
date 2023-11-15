#include "pch.h"
#include "CPipe.h"
#include "CAssetMgr.h"

CPipe::CPipe(int idx):CPlatform() {
	m_Collider = AddComponent<CCollider>(L"PipeCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -32.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	if (idx == 12) // 4, 6~11
		imagePos = { Vec2(238, 1), Vec2(16, 16), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
	else if (idx == 13)
		imagePos = { Vec2(255, 1), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 14)
		imagePos = { Vec2(238, 18), Vec2(16, 16), Vec2(0, 0), 0 };
	else if (idx == 15)
		imagePos = { Vec2(255, 18), Vec2(16, 16), Vec2(0, 0), 0 };
}

CPipe::~CPipe()
{
}
