#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 m_vLookPos; // Target Position
	Vec2 m_vCurLookPos; // Current Position
	Vec2 m_vPrevLookPos; // Last Position
	
	CObject* m_pFocusObj;
	Vec2 m_vDiff; // from Center of Screen to vLookPos

	float m_fTime;
	float m_fSpeed;
	float m_fAccTime;

public:
	Vec2 GetCurLookPos() const { return m_vCurLookPos; }

	void SetLookPos(Vec2 _v) 
	{
		m_vLookPos = _v; 
		float fMoveDist = (m_vLookPos - m_vPrevLookPos).GetLength();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetFocus(CObject* _p) { m_pFocusObj = _p; }
	Vec2 ScreenPosToRenderPos(Vec2 _v) const { return _v - m_vDiff; }
	Vec2 RenderPosToScreenPos(Vec2 _v) const { return _v + m_vDiff; }

	void Update();

private:
	void CalDiff();

};

