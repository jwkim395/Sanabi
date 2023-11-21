#include "pch.h"
#include "CBreakableBlock.h"
#include "CAssetMgr.h"
#include "CMario.h"
#include "CTurtle.h"

void CBreakableBlock::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CPlatform::BeginOverlap(_OwnCol,_OtherObj, _OtherCol);
	if (dynamic_cast<CMario*>(_OtherObj) && dynamic_cast<CMario*>(_OtherObj)->getStatus() >= 1) {
        float platBottom = _OwnCol->GetPos().y + _OwnCol->GetScale().y / 2.f;
		float otherTop = _OtherCol->GetPrevPos().y - _OtherCol->GetScale().y / 2.f;
        if (platBottom <= otherTop)
        {
            Destroy();
        }
	}
	else if (dynamic_cast<CTurtle*>(_OtherObj) && dynamic_cast<CTurtle*>(_OtherObj)->status == 2) {
        float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
        float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);
		float platBottom = _OwnCol->GetPos().y + _OwnCol->GetScale().y / 2.f;
		float otherTop = _OtherCol->GetPrevPos().y - _OtherCol->GetScale().y / 2.f;
		if (plattop >= otherprevbottom) {

		}
		else {
			Destroy();
		}
	}
}

CBreakableBlock::CBreakableBlock()
	:CPlatform()
{
	m_Collider = AddComponent<CCollider>(L"BlockCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = {Vec2(18, 1), Vec2(16, 16), Vec2(0, 0), 0}; //¿ÞÀ§, Å©±â, offset, duration
	
}

CBreakableBlock::~CBreakableBlock()
{
}
