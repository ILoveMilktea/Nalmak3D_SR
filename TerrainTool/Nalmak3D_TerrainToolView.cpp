
// Nalmak3D_TerrainToolView.cpp : CNalmak3D_TerrainToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Nalmak3D_TerrainTool.h"
#endif

#include "Nalmak3D_TerrainToolDoc.h"
#include "Nalmak3D_TerrainToolView.h"
#include "TerrainToolScene.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
CNalmak3D_TerrainToolView* CNalmak3D_TerrainToolView::m_terrainToolView = nullptr;
// CNalmak3D_TerrainToolView

IMPLEMENT_DYNCREATE(CNalmak3D_TerrainToolView, CView)

BEGIN_MESSAGE_MAP(CNalmak3D_TerrainToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_TerrainToolView 생성/소멸

CNalmak3D_TerrainToolView::CNalmak3D_TerrainToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNalmak3D_TerrainToolView::~CNalmak3D_TerrainToolView()
{
	Core::DestroyInstance();
}

BOOL CNalmak3D_TerrainToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_TerrainToolView 그리기

void CNalmak3D_TerrainToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_TerrainToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Core::GetInstance()->Run();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CNalmak3D_TerrainToolView 인쇄

BOOL CNalmak3D_TerrainToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_TerrainToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CNalmak3D_TerrainToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CNalmak3D_TerrainToolView 진단

#ifdef _DEBUG
void CNalmak3D_TerrainToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_TerrainToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_TerrainToolDoc* CNalmak3D_TerrainToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_TerrainToolDoc)));
	return (CNalmak3D_TerrainToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_TerrainToolView 메시지 처리기


void CNalmak3D_TerrainToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//CMainFrame* mainFrame = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	//RECT frameRect = {};
	//RECT thisRect = {};
	//mainFrame->GetWindowRect(&frameRect);
	//GetClientRect(&thisRect);

	//mainFrame->SetWindowPos(nullptr,
	//	0, 0,
	//	WINCX + frameRect.right - frameRect.left - thisRect.right,
	//	WINCY + frameRect.bottom - frameRect.top - thisRect.bottom,
	//	SWP_NOSIZE | SWP_NOMOVE);


	g_hWnd = m_hWnd;
	if(!m_terrainToolView)
		m_terrainToolView = this;

	Core::Desc core;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.resourceDirectoryPath = L"../Resource";
	Core::GetInstance()->Initialize(m_hWnd, &core);
	Core::GetInstance()->AddScene(L"scene", Scene::Instantiate<TerrainToolScene>());
	Core::GetInstance()->SetStartScene(L"scene");

	SetTimer(1, 16, NULL);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CNalmak3D_TerrainToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(false);


	CView::OnTimer(nIDEvent);
}
