#include "pch.h"
#include "CBonusBox.h"
#include "CAssetMgr.h"


void CBonusBox::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    CPlatform::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
    if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
    {

        float platBottom = _OwnCol->GetPos().y + _OwnCol->GetScale().y / 2.f;
        float otherTop = _OtherCol->GetPrevPos().y - _OtherCol->GetScale().y / 2.f;

        //위에서 올라왔으면, y스피드를 0으로 고정
        if (platBottom <= otherTop)
            imagePos.vLeftTop = Vec2(86, 1);
        
    }
}

CBonusBox::CBonusBox() :CPlatform()
{
	m_Collider = AddComponent<CCollider>(L"BoxCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = { Vec2(35, 1), Vec2(16, 16), Vec2(0, 0), 0 }; //왼위, 크기, offset, duration
}

CBonusBox::~CBonusBox()
{
}
