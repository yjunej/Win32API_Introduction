#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(3)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::Update()
{

}

void CTile::Render(HDC _hdc)
{

	if (nullptr == m_pTileTex || m_iImgIdx < 0)
		return;

	UINT iWidth = m_pTileTex->GetWidth();
	UINT iHeight = m_pTileTex->GetHeight();
	
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;
	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;

	if (iMaxCol < iCurCol || iMaxRow < iCurRow)
	{
		assert(nullptr);
	}


	Vec2 vRenderPos = GetPos();
	Vec2 vScale = GetScale();

	vRenderPos = CCamera::GetInstance()->ScreenPosToRenderPos(vRenderPos);

	BitBlt(
		_hdc,
		(int)vRenderPos.x,
		(int)vRenderPos.y,
		(int)vScale.x,
		(int)vScale.y,
		m_pTileTex->GetDC(),
		iCurCol * TILE_SIZE,
		iCurRow * TILE_SIZE,
		SRCCOPY
	);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
