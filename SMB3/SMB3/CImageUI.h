#pragma once
#include "CUI.h"

class CTexture;
class CTile;

class CImageUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* m_NormalImg;
    CTexture* m_PressedImg;
    CTexture* m_CurImg;
    CTile* m_Tile;

public:
    void SetNormalImg(CTexture* _NormalImg) { m_NormalImg = _NormalImg; }
    void SetPressedImg(CTexture* _PressedImg) { m_PressedImg = _PressedImg; }
    void SetTile(CTile* t) { m_Tile = t; }
    CTile* GetTile() { return m_Tile; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void setCurImgToNormal() { m_CurImg = m_NormalImg; }
    virtual void LBtnClicked(Vec2 _vMousePos) override;


public:
    CLONE(CImageUI);
    CImageUI();
    CImageUI(CTexture*);
    ~CImageUI();
};

