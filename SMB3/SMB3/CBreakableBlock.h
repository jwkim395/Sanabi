#pragma once
#include "CPlatform.h"
class CBreakableBlock :
    public CPlatform
{
public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

public:
    CBreakableBlock();
    ~CBreakableBlock();
};

