#pragma once
#include "CObject.h"
class CBox :
    public CObject
{
private:
    int m_iBulletCountUp;
    float m_fHPUp;
    float m_fDamageUp;
    float m_fAttackSpeedUp;

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    virtual void OnCollisionBegin(CCollider* _pOther) override;

public:
    void SetBulletCountUp(int _i) { m_iBulletCountUp = _i; }
	void SetHPUP(float _f) { m_fHPUp = _f; }
	void SetDamageUp(float _f) { m_fDamageUp = _f; }
	void SetAttackSpeedUp(float _f) { m_fAttackSpeedUp = _f; }


    CLONE(CBox)

public:

    CBox();
    ~CBox();

};

