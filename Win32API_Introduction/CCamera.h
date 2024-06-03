#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 m_vLookPos;
	CObject* m_pFocusObj;
	Vec2 m_vDiff; // from Center of Screen to vLookPos

public:
	void SetLookPos(Vec2 _v) { m_vLookPos = _v; }
	void SetFocus(CObject* _p) { m_pFocusObj = _p; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }


	void Update();

private:
	void CalDiff();

};

