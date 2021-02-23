
// Nalmak3D_TerrainToolView.h : CNalmak3D_TerrainToolView 클래스의 인터페이스
//

#pragma once

class CNalmak3D_TerrainToolDoc;

class CNalmak3D_TerrainToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CNalmak3D_TerrainToolView();
	DECLARE_DYNCREATE(CNalmak3D_TerrainToolView)

// 특성입니다.
public:
	CNalmak3D_TerrainToolDoc* GetDocument() const;
	static CNalmak3D_TerrainToolView* m_terrainToolView;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CNalmak3D_TerrainToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Nalmak3D_TerrainToolView.cpp의 디버그 버전
inline CNalmak3D_TerrainToolDoc* CNalmak3D_TerrainToolView::GetDocument() const
   { return reinterpret_cast<CNalmak3D_TerrainToolDoc*>(m_pDocument); }
#endif

