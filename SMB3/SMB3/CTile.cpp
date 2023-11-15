#include "pch.h"
#include "CTile.h"

#include "CAssetMgr.h"
#include "CTexture.h"


CTile::CTile()
	: m_Atlas(nullptr)
	, m_Idx(40)
{
	m_Atlas = CAssetMgr::GetInst()->LoadTexture(L"TileAltas", L"texture\\tile1.png");
}



CTile::~CTile()
{
}

void CTile::AddImgIdx()
{
	if (nullptr == m_Atlas)
		return;

	++m_Idx;

	UINT width = m_Atlas->GetWidth();
	UINT height = m_Atlas->GetHeight();

	UINT maxRow = height / TILE_SIZE;
	UINT maxCol = width / TILE_SIZE;

	UINT maxTileCount = maxRow * maxCol;

	if ((int)maxTileCount <= m_Idx)
	{
		m_Idx = 0;
	}
}

void CTile::Save(FILE* _pFile)
{
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	bool bAtlas = m_Atlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey = m_Atlas->GetKey();
		SaveWString(strKey, _pFile);

		wstring strRelativePath = m_Atlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	fwrite(&m_Idx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	fread(&m_Idx, sizeof(int), 1, _pFile);
}

void CTile::tick(float _DT)
{

}

void CTile::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();

	if (nullptr == m_Atlas)
	{
		Rectangle(_dc
			, (int)(vRenderPos.x)
			, (int)(vRenderPos.y)
			, (int)(vRenderPos.x + 64)
			, (int)(vRenderPos.y + 64));
	}
	else
	{
		UINT width = m_Atlas->GetWidth();
		UINT height = m_Atlas->GetHeight();

		UINT maxRow = height / TILE_SIZE;
		UINT maxCol = width / TILE_SIZE; 

		UINT maxTileCount = maxRow * maxCol;

		if ((int)maxTileCount <= m_Idx)
		{
			return;
		}

		UINT iRow = m_Idx / maxCol;
		UINT iCol = m_Idx % maxCol;

		Vec2 vLeftTop = Vec2(TILE_SIZE * iCol + 4, TILE_SIZE * iRow + 4);

		//BitBlt(_dc
		//	, (int)vRenderPos.x
		//	, (int)vRenderPos.y
		//	, TILE_SIZE, TILE_SIZE
		//	, m_Atlas->GetDC()
		//	, (int)vLeftTop.x
		//	, (int)vLeftTop.y, SRCCOPY);
		/*
		TransparentBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, TILE_SIZE, TILE_SIZE
			, m_Atlas->GetDC()
			, (int)vLeftTop.x, (int)vLeftTop.y
			, TILE_SIZE, TILE_SIZE
			, RGB(147, 187, 236));*/
		
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, int(vRenderPos.x)
			, int(vRenderPos.y)
			, TILE_SIZE - 8,TILE_SIZE - 8
			, m_Atlas->GetDC()
			, (int)vLeftTop.x
			, (int)vLeftTop.y
			, TILE_SIZE - 8, TILE_SIZE - 8
			, blend);
	}	
}

void CTile::renderInUI(HDC _dc, int alpha)
{
	Vec2 vRenderPos = GetPos();

	if (nullptr == m_Atlas)
	{
		Rectangle(_dc
			, (int)(vRenderPos.x)
			, (int)(vRenderPos.y)
			, (int)(vRenderPos.x + TILE_SIZE)
			, (int)(vRenderPos.y + TILE_SIZE));
	}
	else
	{
		UINT width = m_Atlas->GetWidth();
		UINT height = m_Atlas->GetHeight();

		UINT maxRow = height / TILE_SIZE;
		UINT maxCol = width / TILE_SIZE;

		UINT maxTileCount = maxRow * maxCol;

		if ((int)maxTileCount <= m_Idx)
		{
			return;
		}

		UINT iRow = m_Idx / maxCol;
		UINT iCol = m_Idx % maxCol;

		Vec2 vLeftTop = Vec2(TILE_SIZE * iCol, TILE_SIZE * iRow);

		//BitBlt(_dc
		//	, (int)vRenderPos.x
		//	, (int)vRenderPos.y
		//	, TILE_SIZE, TILE_SIZE
		//	, m_Atlas->GetDC()
		//	, (int)vLeftTop.x
		//	, (int)vLeftTop.y, SRCCOPY);
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = alpha; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, int(vRenderPos.x)
			, int(vRenderPos.y)
			, TILE_SIZE, TILE_SIZE
			, m_Atlas->GetDC()
			, (int)vLeftTop.x
			, (int)vLeftTop.y
			, TILE_SIZE, TILE_SIZE
			, blend);
	}
}

