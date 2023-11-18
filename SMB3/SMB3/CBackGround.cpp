#include "pch.h"
#include "CBackGround.h"
#include "CTexture.h"



void CBackGround::tick(float _DT)
{
}

void CBackGround::render(HDC _dc)
{
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

CBackGround::CBackGround()
{
}

CBackGround::CBackGround(const CBackGround& _Origin)
	: CObj(_Origin)
	, m_Image(nullptr)
	, imagePos()
{
}

CBackGround::~CBackGround()
{
}
