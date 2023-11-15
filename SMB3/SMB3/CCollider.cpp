#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CEngine.h"
#include "CCamera.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"



CCollider::CCollider(CObj* _Owner)
	: CComponent(_Owner)
	, m_iCollisionCount(0)
{

}

CCollider::CCollider(const CCollider& _Origin)
	: CComponent(_Origin)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vScale(_Origin.m_vScale)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{

}

void CCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();
	prevPos = GetOwner()->GetPrevPos();

	m_vFinalPos = vOwnerPos + m_vOffsetPos;
	prevPos += m_vOffsetPos;

	// 현재 속해있는 레이어에 충돌체(본인) 를 등록
	int iLayerIdx = GetOwner()->GetLayerIdx();

	// Collider 를 보유하고 있는 오브젝트가 레벨 소속이 아닌데 Finaltick 이 호출된 경우
	assert(!(iLayerIdx < 0));
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);
	pCurLayer->RegisterCollider(this);
}

void CCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	if (0 < m_iCollisionCount)
	{
		SELECT_PEN(_dc, RED_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SELECT_PEN(_dc, GREEN_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
}


void CCollider::BeginOverlap(CCollider* _OtherCol)
{
	++m_iCollisionCount;
	GetOwner()->BeginOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::Overlap(CCollider* _OtherCol)
{
	GetOwner()->Overlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::EndOverlap(CCollider* _OtherCol)
{
	--m_iCollisionCount;
	GetOwner()->EndOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}