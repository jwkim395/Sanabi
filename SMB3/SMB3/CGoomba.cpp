#include "pch.h"
#include "CGoomba.h"
#include "CAssetMgr.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CMario.h"
#include "CPlatform.h"

void CGoomba::tick(float _DT)
{
	if(deadTime == 1.f)
		m_Movement->AddForce(Vec2(velo, 0.f));
	else if(deadTime > 0.f){
		deadTime -= DT;
	}
	else {
		Destroy();
	}

	// ∏  πŸ¥⁄∫∏¥Ÿ ∂≥æÓ¡ˆ∏È destroy
	// π‚»˜∏È ¡◊¿Ω ∏º« > destroy
}

void CGoomba::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	// ¿ßø°º≠ π‚æ“¿∏∏È
	if (dynamic_cast<CMario*>(_OtherObj)) {
		m_Movement->SetVelocity(Vec2(0.f, 0.f));
		m_Animator->Play(L"GOOMBA_Dead", true);
		SetDead();
		deadTime -= DT;
	}
	else if (dynamic_cast<CPlatform*>(_OtherObj)) {
		if(GetPos().y > _OtherObj->GetPos().y - _OtherObj->GetScale().y / 2 &&
			GetPos().y < _OtherObj->GetPos().y + _OtherObj->GetScale().y / 2)
		velo *= -1.f;
	}
}

CGoomba::CGoomba():CMonster(), velo(-50000.f), deadTime(1.f)
{
	m_Collider = AddComponent<CCollider>(L"GoombaCollider");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -32.f));
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"MonsterAtlas", L"texture\\119432.png");
	m_Animator = AddComponent<CAnimator>(L"GoombaAnimator");
	m_Animator->LoadAnimation(L"animdata\\GOOMBA_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\GOOMBA_Dead.txt");
	m_Animator->Play(L"GOOMBA_IDLE", true);
	
	
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(64.f);
	m_Movement->SetMaxSpeed(64.f);
	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 3000.f));
	m_Movement->SetGround(true);

	
}

CGoomba::CGoomba(const CGoomba& _Origin)
{
}

CGoomba::~CGoomba()
{
}
