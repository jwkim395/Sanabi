#pragma once
#include "CPlatform.h"
class CEnd :
    public CPlatform
{
public:
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
public:
    CEnd();
    ~CEnd();
};

