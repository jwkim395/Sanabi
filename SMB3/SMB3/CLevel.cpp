#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CLayer.h"
#include "CObj.h"
#include "CTile.h"
#include "CLevelMgr.h"

CLevel::CLevel()
	: m_TileRow(0)
	, m_TileCol(0)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		if (nullptr != m_Layer[i])
			delete m_Layer[i];
	}
}

void CLevel::begin()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->begin();
	}
}

void CLevel::tick()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->clear();
	}

	if (CLevelMgr::GetInst()->getmTime() <= 0.f) {
		for (UINT i = 0; i < LAYER::END; ++i)
		{
			m_Layer[i]->tick(DT);
		}

		for (UINT i = 0; i < LAYER::END; ++i)
		{
			m_Layer[i]->finaltick(DT);
		}
	}
	else {
		m_Layer[PLAYER]->tick(DT);
		m_Layer[PLAYER]->finaltick(DT);
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->render(_dc);
	}
}

void CLevel::AddObject(LAYER _LayerType, CObj* _Object)
{
	// 레이어에 오브젝트를 집어넣는다.
	m_Layer[_LayerType]->AddObject(_Object);

	// 레이어 인덱스값을 오브젝트에 세팅해준다(오브젝트가 자신이 소속된 레이어 인덱스를 알게 한다)
	_Object->m_iLayerIdx = _LayerType;
}

void CLevel::DeleteAllObjects()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->DeleteAllObjects();
	}
}

void CLevel::DeleteObjectsByLayer(LAYER _Layer)
{
	m_Layer[_Layer]->DeleteAllObjects();
}

void CLevel::CreateTile(UINT _Row, UINT _Col)
{
	DeleteObjectsByLayer(LAYER::TILE);

	m_TileRow = _Row;
	m_TileCol = _Col;

	for (UINT i = 0; i < _Row; ++i)
	{
		for (UINT j = 0; j < _Col; ++j)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(Vec2(TILE_SIZE * j, TILE_SIZE * i));

			AddObject(LAYER::TILE, pTile);
		}
	}
}

CObj* CLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		const vector<CObj*>& vecObjects = m_Layer[i]->GetObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (vecObjects[j]->GetName() == _Name)
			{
				return vecObjects[j];
			}
		}
	}

	return nullptr;
}

void CLevel::FindTileScreen()
{
	m_vecTile.clear();


	Vec2 vLeftTop = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vLeftTop -= (vResolution / 2.f);

	int iLTCol = (int)vLeftTop.x / TILE_SIZE;
	int iLTRow = (int)vLeftTop.y / TILE_SIZE;

	if (vLeftTop.x < 0.f)
		iLTCol = 0;
	if (vLeftTop.y < 0.f)
		iLTRow = 0;

	int iMaxCol = ((int)vResolution.x / TILE_SIZE) + iLTCol + 1;
	int iMaxRow = ((int)vResolution.y / TILE_SIZE) + iLTRow + 1;

	if (m_TileCol < iMaxCol)
		iMaxCol = m_TileCol;
	if (m_TileRow < iMaxRow)
		iMaxRow = m_TileRow;
	
	for (int iRow = iLTRow; iRow < iMaxRow; ++iRow)
	{
		for (int iCol = iLTCol; iCol < iMaxCol; ++iCol)
		{
			int iTileIdx = iRow * m_TileCol + iCol;

			m_vecTile.push_back(m_Layer[(UINT)LAYER::TILE]->m_vecObjects[iTileIdx]);
		}
	}
}
