#include "pch.h"
#include "CMonster.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CCollider.h"


CMonster::CMonster()
	: m_Info{}
	, m_Collider(nullptr)
	, m_Movement(nullptr)
{
	m_Collider = AddComponent<CCollider>(L"MonsterCollider");
	
}

CMonster::CMonster(const CMonster& _Origin)
	: CObj(_Origin)
	, m_Info(_Origin.m_Info)	
	, m_Collider(nullptr)
	, m_Movement(nullptr)
{
	m_Collider = GetComponent<CCollider>();
	m_Movement = GetComponent<CMovement>();
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	Vec2 vPos = GetPos();
	prevPos = GetPos();
}

void CMonster::tick(float _DT)
{
	Super::tick(_DT);
}

void CMonster::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}