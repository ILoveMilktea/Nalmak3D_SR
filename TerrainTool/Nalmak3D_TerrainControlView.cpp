// Nalmak3D_TerrainControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Nalmak3D_TerrainTool.h"
#include "Nalmak3D_TerrainControlView.h"


// Nalmak3D_TerrainControlView

IMPLEMENT_DYNCREATE(Nalmak3D_TerrainControlView, CFormView)

Nalmak3D_TerrainControlView::Nalmak3D_TerrainControlView()
	: CFormView(IDD_NALMAK3D_TERRAINCONTROLVIEW)
{

}

Nalmak3D_TerrainControlView::~Nalmak3D_TerrainControlView()
{
}

void Nalmak3D_TerrainControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Nalmak3D_TerrainControlView, CFormView)
END_MESSAGE_MAP()


// Nalmak3D_TerrainControlView �����Դϴ�.

#ifdef _DEBUG
void Nalmak3D_TerrainControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Nalmak3D_TerrainControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Nalmak3D_TerrainControlView �޽��� ó�����Դϴ�.
