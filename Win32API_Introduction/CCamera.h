#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
	END,
};

struct tCamEffectInfo
{
	CAM_EFFECT eEffect; // Effect 
	float fDuration; // Effect play time 
	float fAccTime; // Time check
};

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

	CTexture* m_pVeilTex;

	list<tCamEffectInfo> m_listCamEffectInfo;

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

	void FadeIn(float _fDuration)
	{
		assert(0.f != _fDuration);
		tCamEffectInfo tcei = {
			CAM_EFFECT::FADE_IN,
			_fDuration,
			0.f,
		};
		m_listCamEffectInfo.push_back(tcei);
	}
	void FadeOut(float _fDuration)
	{
		assert(0.f != _fDuration);
		tCamEffectInfo tcei = {
			CAM_EFFECT::FADE_OUT,
			_fDuration,
			0.f,
		};
		m_listCamEffectInfo.push_back(tcei);
	}

	void Init();
	void Update();
	void Render(HDC _hdc);

private:
	void CalDiff();

};

