#pragma once
#include "CObj.h"

class CPlatform :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_Collider;


public:
    virtual void tick(float _DT) override;
    void SetScale(Vec2 v1) { m_Collider->SetScale(v1); };
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CPlatform);
    CPlatform();
    CPlatform(const CPlatform& _Origin);
    ~CPlatform();
};

