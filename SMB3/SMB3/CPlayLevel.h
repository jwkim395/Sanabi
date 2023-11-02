#pragma once
#include "CLevel.h"
class CPlayLevel :
    public CLevel
{
public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

};

