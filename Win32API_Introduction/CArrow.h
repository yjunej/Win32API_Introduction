#pragma once
#include "CBullet.h"

class CTexture;

class CArrow :
    public CBullet
{
private:
    CTexture* m_pTex;
    virtual void Render(HDC _hdc);
 


public:
    CArrow();
    ~CArrow();
};

