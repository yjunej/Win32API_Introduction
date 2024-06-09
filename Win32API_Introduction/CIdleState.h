#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CIdleState();
    ~CIdleState();
};

