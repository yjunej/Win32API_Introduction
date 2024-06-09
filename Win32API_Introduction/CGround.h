#pragma once
#include "CObject.h"
class CGround :
    public CObject
{

private:

public:
    virtual void OnCollisionBegin(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
    virtual void OnCollisionEnd(CCollider* _pOther) override;

    virtual void Update() override;
    virtual void BeginPlay() override;


    CLONE(CGround)
public:
    CGround();
    virtual ~CGround();
};

