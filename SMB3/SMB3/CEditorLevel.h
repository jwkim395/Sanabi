#pragma once
#include "CLevel.h"

class CEditorLevel :
    public CLevel
{
private:
    class CImageUI* selected;
    Vec2 mLeft;
    Vec2 mRightBottom;
    bool isEndSetted;
    bool isMarioSetted;
public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;
    virtual void tick() override;

public:
    void OpenTileCreateWindow();
    void LoadTile();
    void SaveTile();
    void setSelected(CImageUI* _ui) { selected = _ui; }
    void initSelected();
    void LoadGame();

public:
    CEditorLevel();
};

