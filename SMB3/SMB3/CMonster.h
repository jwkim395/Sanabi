#pragma once
#include "CObj.h"


class CCollider;
class CTexture;

class CMonster :
    public CObj
{
    GENERATED_OBJECT(CObj);
protected:
    FMonInfo        m_Info;
    CCollider*      m_Collider;
    class CAnimator* m_Animator;
    class CMovement* m_Movement;

public:
    void SetMonsterInfo(const FMonInfo& _Info) { m_Info = _Info; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;


public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    
public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Origin);
    ~CMonster();
};

