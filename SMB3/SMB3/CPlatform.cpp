#include "pch.h"
#include "CPlatform.h"
#include "CTexture.h"
#include "components.h"

CPlatform::CPlatform()
{
}

CPlatform::CPlatform(const CPlatform& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
	, m_Image(nullptr)
	, imagePos()
{
	m_Collider = GetComponent<CCollider>();
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick(float _DT)
{

}

void CPlatform::render(HDC _dc)
{
	Super::render(_dc);
	if (m_Image != nullptr) {
		Vec2 vRenderPos = GetRenderPos();
		
		TransparentBlt(_dc, int(vRenderPos.x - (imagePos.vCutSize.x * 2.f) + imagePos.vOffset.x)
			, int(vRenderPos.y - (imagePos.vCutSize.y * 2.f) + imagePos.vOffset.y)
			, int(imagePos.vCutSize.x) * 4, int(imagePos.vCutSize.y) * 4
			, m_Image->GetDC()
			, int(imagePos.vLeftTop.x), int(imagePos.vLeftTop.y)
			, int(imagePos.vCutSize.x), int(imagePos.vCutSize.y)
			, RGB(147, 187, 236));
	}
}


void CPlatform::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if ((UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx() || (UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
    {
        float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
        float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);

        float platRight = (_OwnCol->GetPos().x + _OwnCol->GetScale().x / 2.f);
        float otherRight = (_OtherCol->GetPrevPos().x + _OtherCol->GetScale().x / 2.f);
        float platLeft = (_OwnCol->GetPos().x - _OwnCol->GetScale().y / 2.f);
        float otherLeft = (_OtherCol->GetPrevPos().x - _OtherCol->GetScale().x / 2.f);
        //float otherbottom =( _OtherCol->GetPos().y +_OtherCol->GetScale().y / 2.f);

        //if (_OwnCol->GetName() == L"PlatformCollider2")
        //   LOG(LOG_LEVEL::LOG, std::to_wstring(otherbottom).c_str());
        //if ((UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx())
        //   int a = 0;

        float yfix = ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) ? 0.99f : 0.95f;


        if (plattop >= otherprevbottom * yfix)// && plattop <= otherbottom)
        {

            float up = (_OwnCol->GetScale().y / 2.f
                + _OtherCol->GetScale().y / 2.f
                - abs(_OwnCol->GetPos().y
                    - (_OtherCol->GetPos().y))
                ) / 2.f;

            _OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
        }
        else {
            if (platRight >= otherLeft)// && plattop <= otherbottom)
            {
                float right = (_OwnCol->GetScale().x / 2.f
                    + _OtherCol->GetScale().x / 2.f
                    - abs((_OtherCol->GetPos().x))
                    - _OwnCol->GetPos().x) / 2.f;

                _OtherObj->SetPos(Vec2(_OtherObj->GetPos().x + right, _OtherObj->GetPos().y));
            }
            else if (platLeft <= otherRight)// && plattop <= otherbottom)
            {

                float right = (_OwnCol->GetScale().x / 2.f
                    + _OtherCol->GetScale().x / 2.f
                    - abs((_OtherCol->GetPos().x))
                    - _OwnCol->GetPos().x) / 2.f;

                _OtherObj->SetPos(Vec2(_OtherObj->GetPos().x - right, _OtherObj->GetPos().y));
            }
        }
        

    }
}

void CPlatform::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx() ||
        (UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx())
    {
        float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
        float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);

        float platRight = (_OwnCol->GetPos().x + _OwnCol->GetScale().x / 2.f);
        float otherRight = (_OtherCol->GetPrevPos().x + _OtherCol->GetScale().x / 2.f);
        float platLeft = (_OwnCol->GetPos().x - _OwnCol->GetScale().y / 2.f);
        float otherLeft = (_OtherCol->GetPrevPos().x - _OtherCol->GetScale().x / 2.f);

        float yfix = ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) ? 0.99f : 0.97f;

        //위에서 올라왔으면, y스피드를 0으로 고정
        if (plattop > otherprevbottom)// *yfix)
        {

            CMovement* mov = _OtherObj->GetMovement();

            if (nullptr != mov)
            {
                Vec2 v = mov->GetVelocity();
                mov->SetVelocity(Vec2(v.x, 0.f));
            }
        }
        else if (platRight >= otherLeft || platLeft <= otherRight) {
            CMovement* mov = _OtherObj->GetMovement();

            if (nullptr != mov)
            {
                Vec2 v = mov->GetVelocity();
                mov->SetVelocity(Vec2(0.f, v.y));
            }
        }
    }

}