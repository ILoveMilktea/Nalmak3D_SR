
// Nalmak3D_TerrainToolView.h : CNalmak3D_TerrainToolView Ŭ������ �������̽�
//

#pragma once

class CNalmak3D_TerrainToolDoc;

class CNalmak3D_TerrainToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CNalmak3D_TerrainToolView();
	DECLARE_DYNCREATE(CNalmak3D_TerrainToolView)

// Ư���Դϴ�.
public:
	CNalmak3D_TerrainToolDoc* GetDocument() const;
	static CNalmak3D_TerrainToolView* m_terrainToolView;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CNalmak3D_TerrainToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Nalmak3D_TerrainToolView.cpp�� ����� ����
inline CNalmak3D_TerrainToolDoc* CNalmak3D_TerrainToolView::GetDocument() const
   { return reinterpret_cast<CNalmak3D_TerrainToolDoc*>(m_pDocument); }
#endif

