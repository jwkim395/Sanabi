#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_LayerCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < 32; ++iRow)
	{
		for (UINT iCol = iRow; iCol < 32; ++iCol)
		{
			if (!(m_LayerCheck[iRow] & (1 << iCol)))
				continue;

			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}
	
	m_LayerCheck[row] |= (1 << col);
}

void CCollisionMgr::UncheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}

	m_LayerCheck[row] &= ~(1 << col);
}

void CCollisionMgr::CollisionBtwLayer(LAYER _Left, LAYER _Right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (nullptr == pCurLevel)
		return;

	const vector<CCollider*>& vecLeft = pCurLevel->GetLayer(_Left)->GetColliders();
	const vector<CCollider*>& vecRight = pCurLevel->GetLayer(_Right)->GetColliders();


	// 서로 다른 레이어끼리 충돌 검사
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				COLLIDER_ID ID(vecLeft[i]->GetID(), vecRight[j]->GetID());

				map<COLLIDER_ID, bool>::iterator iter = m_mapID.find(ID);

				if (iter == m_mapID.end())
				{
					m_mapID.insert(make_pair(ID, false));
					iter = m_mapID.find(ID);
				}


				// 현재 충돌 중이다.
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					if (false == iter->second)
					{
						// 둘다 Dead 상태가 아니라면
						if ( !vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							// 이전에 충돌한 적이 없다.
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}
					}

					else
					{
						// 이전에도 충돌 중이었다.
						// 둘 중 하나 이상 Dead 상태
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{
							vecLeft[i]->EndOverlap(vecRight[j]);
							vecRight[j]->EndOverlap(vecLeft[i]);
						}
						else
						{
							vecLeft[i]->Overlap(vecRight[j]);
							vecRight[j]->Overlap(vecLeft[i]);
						}
					}
					iter->second = true;
				}

				// 현재 충돌하지 않고 있다.
				else
				{
					if (iter->second)
					{
						// 이전에는 충돌하고 있었다.
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}
					iter->second = false;
				}
			}
		}
	}

	// 같은 레이어 내에서 충돌 검사
	else
	{

	}
}

bool CCollisionMgr::IsCollision(CCollider* _Left, CCollider* _Right)
{	
	if (fabs(_Left->GetScale().x / 2.f + _Right->GetScale().x / 2.f) >= fabs(_Left->GetPos().x - _Right->GetPos().x)
		&& fabs(_Left->GetScale().y / 2.f + _Right->GetScale().y / 2.f) >= fabs(_Left->GetPos().y - _Right->GetPos().y))
	{
		return true;
	}

	return false;
}
