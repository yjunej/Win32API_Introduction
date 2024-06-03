#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_dDT(0.f)
	, m_dTT(0.f)
	, m_iCallCount(0)
	, m_iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	// Current Count
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;

	m_dTT += m_dDT;

	if (m_dTT >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dTT = 0;
		m_iCallCount = 0;
	}

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
	{
		m_dDT = 1. / 60.;
	}
#endif // DEBUG

}
