#pragma once

#include "CEntity.h"

class CObj;
class CCollider;

class CLayer
	: public CEntity
{
private:
	vector<CObj*> 		m_vecObjects;
	vector<CCollider*>	m_vecCollider;

public:
	void begin();
	void tick(float _DT);
	void finaltick(float _DT);
	void render(HDC _dc);

	void clear() { m_vecCollider.clear(); }
	void AddObject(CObj* _Object) { m_vecObjects.push_back(_Object); }
	void RegisterCollider(CCollider* _Collider) { m_vecCollider.push_back(_Collider); }

	const vector<CObj*>& GetObjects() { return  m_vecObjects; }	

	const vector<CCollider*>& GetColliders() { return m_vecCollider; }

	void DeleteAllObjects();


public:
	CLONE_DISABLE(CLayer);
	CLayer();
	CLayer(const CLayer& _Origin) = delete;
	~CLayer();

	friend class CLevel;
	friend class CUIMgr;
};

