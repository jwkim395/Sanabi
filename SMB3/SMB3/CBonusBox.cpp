#include "pch.h"
#include "CBonusBox.h"
#include "CAssetMgr.h"
#include "CItem.h"

void CBonusBox::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    Super::BeginOverlap();
    if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
    {
        float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
        float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);

        float platBottom = _OwnCol->GetPos().y + _OwnCol->GetScale().y / 2.f;
        float otherTop = _OtherCol->GetPrevPos().y - _OtherCol->GetScale().y / 2.f;

        float platRight = (_OwnCol->GetPos().x + _OwnCol->GetScale().x / 2.f);
        float otherRight = (_OtherCol->GetPos().x + _OtherCol->GetScale().x / 2.f);
        float platLeft = (_OwnCol->GetPos().x - _OwnCol->GetScale().y / 2.f);
        float otherLeft = (_OtherCol->GetPos().x - _OtherCol->GetScale().x / 2.f);

        float yfix = ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) ? 0.99f : 0.97f;

        //위에서 올라왔으면, y스피드를 0으로 고정
        if (plattop >= otherprevbottom || platBottom <= otherTop)// *yfix)
        {
            CMovement* mov = _OtherObj->GetMovement();

            if (nullptr != mov)
            {
                Vec2 v = mov->GetVelocity();
                mov->SetVelocity(Vec2(v.x, 0.f));
            }
        }
        else if (platRight > otherLeft || platLeft < otherRight) {
            CMovement* mov = _OtherObj->GetMovement();

            if (nullptr != mov)
            {
                Vec2 v = mov->GetVelocity();
                mov->SetVelocity(Vec2((-v.x) / 3.f, v.y));
            }
        }
    }
    Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
}

CBonusBox::CBonusBox(int idx) :CPlatform(), mItem(nullptr)
{
	mItem = new CItem(idx);
	m_Collider = AddComponent<CCollider>(L"BoxCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = { Vec2(35, 1), Vec2(16, 16), Vec2(0, 0), 0 }; //왼위, 크기, offset, duration
}

CBonusBox::~CBonusBox()
{
}
