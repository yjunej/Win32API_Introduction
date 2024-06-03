#pragma once

#include "CObject.h"

class CBullet :
    public CObject
{
private:
    float m_fSpeed;
    float m_fTheta;
    Vec2 m_vDirection;

public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

    void SetDirection(float _f) {m_fTheta = _f;}
    void SetDirection(Vec2 _vec) { m_vDirection = _vec.Normalize(); }

    virtual void OnCollisionBegin(CCollider* _pOther);

public:
    CBullet();
    ~CBullet();
};

