#include "pch.h"
#include "CEnd.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"


void CEnd::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CEnd::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->GetLayerIdx() == PLAYER) {
		_OtherObj->GetMovement()->SetVelocity(Vec2(192.f, 0.f));
		CLevelMgr::GetInst()->setmTime(4.f);
		CLevelMgr::GetInst()->setMarioStatus(4);
	}
}

CEnd::CEnd() {
	m_Collider = AddComponent<CCollider>(L"EndCollider");
	m_Collider->SetScale(Vec2(128.f, 128.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = { Vec2(195, 879), Vec2(32, 32), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
}

CEnd::~CEnd()
{
}
