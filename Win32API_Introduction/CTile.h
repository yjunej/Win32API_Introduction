#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;
    int m_iImgIdx;

public:
    void SetTexture(CTexture* _cTex) { m_pTileTex = _cTex; }
    void IncImgIdx() { ++m_iImgIdx; }

  
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

private:

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;




    CLONE(CTile)

public:
    CTile();
    ~CTile();
};

