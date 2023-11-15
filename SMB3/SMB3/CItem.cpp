#include "pch.h"
#include "CItem.h"
#include "CAssetMgr.h"

CItem::CItem(int idx)
{
	m_Collider = AddComponent<CCollider>(L"ItemCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	if (idx == 2) { // 2, 3
		imagePos = { Vec2(1, 249), Vec2(16, 16), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
		m_Image = CAssetMgr::GetInst()->LoadTexture(L"MarioAtlas", L"texture\\69712.png");
	}
	else if (idx == 3) {
		imagePos = { Vec2(119, 1), Vec2(16, 16), Vec2(0, 0), 0 };
		m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	}
}

CItem::~CItem()
{
}
