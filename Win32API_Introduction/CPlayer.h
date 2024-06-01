#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
public:
	virtual void Update() override;


private:
	void Fire();

};

