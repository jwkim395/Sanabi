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
	float up = (_OwnCol->GetScale().y / 2.f + _OtherCol->GetScale().y / 2.f - abs(_OwnCol->GetPos().y - _OtherCol->GetPos().y)) / 2.f;
	_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
	
}