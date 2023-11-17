#pragma once
#include "CMonster.h"
class CGoomba :
    public CMonster
{
public:
    float velo;
    float deadTime;
    int onBlock;

public:
    virtual void tick(float _DT) override;

    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

public:
    CLONE(CGoomba);
    CGoomba();
    CGoomba(const CGoomba& _Origin);
    ~CGoomba();
};

