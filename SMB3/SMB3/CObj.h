#pragma once

#include "CEntity.h"
#include "CTaskMgr.h"
#include "CCamera.h"

#include "components.h"

class CObj
	: public CEntity
{
private:
	Vec2				m_Pos;
	Vec2				m_Scale;
	vector<CComponent*>	m_vecComponent;
	int					m_iLayerIdx;
	

public:
	Vec2 GetPos() { return m_Pos; }
	Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
	Vec2 GetScale() { return m_Scale; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	int GetLayerIdx() { return m_iLayerIdx; }


protected:
	template<typename T>
	T* AddComponent(const wstring& _strName = L"")
	{
		T* pNewCom = new T(this);
		m_vecComponent.push_back(pNewCom);
		pNewCom->SetName(_strName);
		return pNewCom;
	}

public:
	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T*>(m_vecComponent[i]))
			{
				return (T*)m_vecComponent[i];
			}
		}

		return nullptr;
	}

	template<typename T>
	void GetComponents(vector<T*>& _out)
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T>(m_vecComponent[i]))
			{
				_out.push_back((T*)m_vecComponent[i]);
			}
		}
	}


public:	
	// Level 이 시작할 때 Level 안에 들어있던 오브젝트 or 레벨이 시작되고나서 레벨에 합류하는 오브젝트
	virtual void begin() {}; 

	// 매 틱마다 호출
	virtual void tick(float _DT); 

	// 상속받은 자식 클래스에서 재정의(override) 할 수 없음
	virtual void finaltick(float _DT) final; 

	// 렌더링 함수
	virtual void render(HDC _dc);


	void Destroy();


	// 충돌 이벤트
	virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}

private:
	void SetDead();

public:
	virtual CObj* Clone() = 0;
	CObj();
	CObj(const CObj& _Origin);
	virtual ~CObj();

	friend class CLevel;
	friend class CTaskMgr;
};

