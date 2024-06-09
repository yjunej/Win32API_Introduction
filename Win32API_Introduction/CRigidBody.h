#pragma once
class CRigidBody
{
private:
	CObject* m_pOwner;

	// F = m * a
	// V += A * DT 

	Vec2 m_vForce; 
	Vec2 m_vVelocity;	
	Vec2 m_vMaxVelocity;
	Vec2 m_vAccel;
	Vec2 m_vAdditiveAccel;
	float m_fMass;

	float m_fFrictionCoef;

public:
	void PostUpdate();
	float GetSpeed() { return GetVelocity().GetLength(); }
	void AddForce(Vec2 _v)
	{
		m_vForce += _v;
	}
	void ClearPhysics();
	void Move();
	void SetMass(float _f) { m_fMass = _f; }
	void SetVelocity(Vec2 val) { m_vVelocity = val; }
	void AddVelocity(Vec2 val) { m_vVelocity = GetVelocity() + val; }
	void SetAdditiveAccel(Vec2 val) { m_vAdditiveAccel = val; }
	void SetMaxVelocity(Vec2 val) { m_vMaxVelocity = val; }

	Vec2 GetVelocity() const { return m_vVelocity; }

public:
	CRigidBody();
	~CRigidBody();
	friend class CObject;
};

