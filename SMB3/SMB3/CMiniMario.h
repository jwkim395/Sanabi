#pragma once
#include "CPlayer.h"
class CMiniMario :
    public CPlayer
{
public:
    virtual void tick(float _DT) override;

public:
    CLONE(CMiniMario);
    CMiniMario();
    ~CMiniMario();
};

