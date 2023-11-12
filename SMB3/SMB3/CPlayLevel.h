#pragma once
#include "CLevel.h"
class CPlayLevel :
    public CLevel
{
public:
    bool mIsDead;
public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

    void setObj(CTile*);

    void loadMap();

};

