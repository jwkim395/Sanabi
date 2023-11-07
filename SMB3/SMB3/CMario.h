#pragma once
#include "CObj.h"

class CMario :
    public CObj
{
    GENERATED_OBJECT(CObj);
protected:    
    class CCollider*  m_Collider;
    class CAnimator*  m_Animator;
    class CMovement*  m_Movement;
    int status; // 0 > mini, 1 > super, 2 > fire, 3 > racoon
    float jumpedTime;

public:
    virtual void tick(float _DT) override;    
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

public:
    CLONE_DISABLE(CMario);
    CMario();
    ~CMario();
};

