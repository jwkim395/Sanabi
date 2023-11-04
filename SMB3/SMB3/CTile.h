#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CTexture*   m_Atlas;
    int               m_Idx;
    


public:
    void SetAtlas(class CTexture* _Atlas) { m_Atlas = _Atlas; }
    void SetImgIdx(int _ImgIdx){ m_Idx = _ImgIdx; }
    int GetImgIdx() { return m_Idx; }
    void AddImgIdx();
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    void renderInUI(HDC _dc, int alpha);

public:
    CLONE(CTile);
    CTile();
    ~CTile();
};

