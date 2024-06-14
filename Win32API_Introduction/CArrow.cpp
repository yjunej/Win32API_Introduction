#include "CArrow.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CResourceMgr.h"


HBITMAP RotateBitmap(HDC hdc, HBITMAP hBitmap, double angle);

void CArrow::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vRenderPos = CCamera::GetInstance()->ScreenPosToRenderPos(vPos);

	// 방향 벡터를 사용하여 각도 계산
	double angle = atan2(GetDirection().y, GetDirection().x);

	// 원본 비트맵의 크기 가져오기
	BITMAP bm = m_pTex->GetBitmap();

	// 회전 중심을 기준으로 하는 3개의 정점 계산
	POINT vertices[4];
	double cosA = cos(angle);
	double sinA = sin(angle);

	int halfWidth = bm.bmWidth / 2;
	int halfHeight = bm.bmHeight / 2;

	vertices[0].x = (LONG)((-halfWidth * cosA + (-halfHeight) * sinA));
	vertices[0].y = (LONG)((-halfWidth * sinA - (-halfHeight) * cosA));

	vertices[1].x = (LONG)((halfWidth * cosA + (-halfHeight) * sinA));
	vertices[1].y = (LONG)((halfWidth * sinA - (-halfHeight) * cosA));

	vertices[2].x = (LONG)((-halfWidth * cosA + (halfHeight)*sinA));
	vertices[2].y = (LONG)((-halfWidth * sinA - (halfHeight)*cosA));

	vertices[3].x = (LONG)((halfWidth * cosA + (halfHeight)*sinA));
	vertices[3].y = (LONG)((halfWidth * sinA - (halfHeight) * cosA));

	long maxX = vertices[0].x;
	long maxY = vertices[0].y;
	long minX = vertices[0].x;
	long minY = vertices[0].y;

	for (int i = 0; i < 4 ; i++)
	{
		if (vertices[i].x > maxX)
			maxX = vertices[i].x;
		if (vertices[i].y > maxY)
			maxY = vertices[i].y;
		if (vertices[i].x < minX)
			minX = vertices[i].x;
		if (vertices[i].y < minY)
			minY = vertices[i].y;
	}


	// 원본 비트맵을 그리기 위한 DC 생성
	HDC memDC = CreateCompatibleDC(m_pTex->GetDC());
	HBITMAP hBmap = CreateCompatibleBitmap(m_pTex->GetDC(), maxX - minX, maxY - minY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBmap);

	RECT rect = { 0, 0, maxX-minX, maxY-minY };
	HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FillRect(memDC, &rect, brush);

	POINT verticesSubset[3] = { vertices[0], vertices[1], vertices[2] };

	for (int i = 0; i < 4; ++i) {
		if (minX < 0)
		{
			vertices[i].x -= minX;
			if (vertices[i].x > maxX)
			{
				maxX = vertices[i].x;
			}
		}
		if (minY < 0)
		{
			vertices[i].y -= minY;
			if (vertices[i].y > maxY)
			{
				maxY = vertices[i].y;
			}
 		}


		if (i != 3)
		{
			verticesSubset[i] = vertices[i];
		}
	}

	if (minX < 0)
		minX = 0;
	if (minY < 0)
		minY = 0;

	// PlgBlt를 사용하여 회전된 비트맵을 그리기
	PlgBlt(
		memDC,
		verticesSubset,
		m_pTex->GetDC(),
		0, 0,
		bm.bmWidth,
		bm.bmHeight,
		NULL, 0, 0 // 사용하지 않는 매개변수
	);

	TransparentBlt(
		_hdc,
		(int)(vRenderPos.x - vScale.x / 2.f),
		(int)(vRenderPos.y - vScale.y / 2.f),
		(int)vScale.x,
		(int)vScale.y,
		
		memDC,
		minX, minY,
		maxX - minX,
		maxY - minY,
		RGB(255, 255, 255) // 투명색으로 지정 (마젠타색)
	);





	// 리소스 해제
	//SelectObject(memDC, oldBitmap);
	DeleteObject(hBmap);
	DeleteObject(oldBitmap);
	DeleteDC(memDC);

	RenderComponent(_hdc);


		//if (m_bFinish) return;
		//CObject* pObj = m_pAnimator->GetOwner();
		//Vec2 vObjPos = pObj->GetPos();

		//vObjPos += m_vecFrm[m_iCurFrm].vOffset;

		//// Convert to Rendering position
		//vObjPos = CCamera::GetInstance()->ScreenPosToRenderPos(vObjPos);

		//TransparentBlt(
		//	_hdc,
		//	(int)(vObjPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		//	(int)(vObjPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		//	(int)m_vecFrm[m_iCurFrm].vSlice.x,
		//	(int)m_vecFrm[m_iCurFrm].vSlice.y,
		//	m_pTex->GetDC(),
		//	(int)m_vecFrm[m_iCurFrm].vLT.x,
		//	(int)m_vecFrm[m_iCurFrm].vLT.y,
		//	(int)m_vecFrm[m_iCurFrm].vSlice.x,
		//	(int)m_vecFrm[m_iCurFrm].vSlice.y,
		//	RGB(0, 0, 0)
		//);
}

CArrow::CArrow()
{

	m_pTex = CResourceMgr::GetInstance()->LoadTexture(L"ARROW", L"texture\\Arrow32.bmp");
}

CArrow::~CArrow()
{
}

HBITMAP RotateBitmap(HDC hdc, HBITMAP hBitmap, double angle)
{
	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	double radians = angle * (PI / 180.0);

	// 회전된 비트맵의 크기 계산
	int width = (int)(bm.bmWidth * fabs(cos(radians)) + bm.bmHeight * fabs(sin(radians)));
	int height = (int)(bm.bmWidth * fabs(sin(radians)) + bm.bmHeight * fabs(cos(radians)));

	HDC srcDC = CreateCompatibleDC(hdc);
	HDC destDC = CreateCompatibleDC(hdc);

	HBITMAP newBitmap = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP oldSrcBitmap = (HBITMAP)SelectObject(srcDC, hBitmap);
	HBITMAP oldDestBitmap = (HBITMAP)SelectObject(destDC, newBitmap);

	// 배경을 투명색으로 채우기
	RECT rect = { 0, 0, width, height };
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); // 투명색으로 지정 (검정색)
	FillRect(destDC, &rect, brush);
	DeleteObject(brush);

	// 회전 변환 설정
	XFORM xForm;
	xForm.eM11 = (FLOAT)cos(radians);
	xForm.eM12 = (FLOAT)sin(radians);
	xForm.eM21 = (FLOAT)-sin(radians);
	xForm.eM22 = (FLOAT)cos(radians);
	xForm.eDx = (FLOAT)(width / 2);
	xForm.eDy = (FLOAT)(height / 2);

	SetGraphicsMode(destDC, GM_ADVANCED);
	SetWorldTransform(destDC, &xForm);

	// 원본 비트맵을 회전된 비트맵으로 복사
	BitBlt(destDC, -bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, srcDC, 0, 0, SRCCOPY);

	// 리소스 해제
	SelectObject(srcDC, oldSrcBitmap);
	SelectObject(destDC, oldDestBitmap);
	DeleteDC(srcDC);
	DeleteDC(destDC);

	return newBitmap;
}