#pragma once



// Nalmak3D_TerrainControlView �� ���Դϴ�.

class Nalmak3D_TerrainControlView : public CFormView
{
	DECLARE_DYNCREATE(Nalmak3D_TerrainControlView)

protected:
	Nalmak3D_TerrainControlView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~Nalmak3D_TerrainControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NALMAK3D_TERRAINCONTROLVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


