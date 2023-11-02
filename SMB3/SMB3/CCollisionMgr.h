#pragma once

class CCollider;

struct COLLIDER_ID
{
	INT_PTR left;
	INT_PTR right;

	bool operator == (const COLLIDER_ID& _other) const
	{
		if (left == _other.left && right == _other.right)
			return true;
		return false;
	}

	bool operator < (const COLLIDER_ID& _other) const
	{
		if (left < _other.left)
			return true;
		else if (left > _other.left)
			return false;
		else
		{
			if (right < _other.right)
				return true;
			else 
				return false;
		}
	}

	COLLIDER_ID()
		: left(0)
		, right(0)
	{}

	COLLIDER_ID(INT_PTR _Left, INT_PTR _Right)
		: left(_Left)
		, right(_Right)
	{}
};


class CCollisionMgr
{
	SINGLETON(CCollisionMgr);
private:
	// 레이어 간의 충돌을 지정하는 매트릭스
	UINT					m_LayerCheck[32]; 
	map<COLLIDER_ID, bool>	m_mapID;


public:	
	void tick();
	void CheckCollision(LAYER _Left, LAYER _Right);
	void UncheckCollision(LAYER _Left, LAYER _Right);

private:
	void CollisionBtwLayer(LAYER _Left, LAYER _Right);
	bool IsCollision(CCollider* _Left, CCollider* _Right);

};

