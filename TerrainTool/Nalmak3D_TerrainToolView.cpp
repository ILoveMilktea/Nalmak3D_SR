
// Nalmak3D_TerrainToolView.cpp : CNalmak3D_TerrainToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_TerrainToolView ����/�Ҹ�

CNalmak3D_TerrainToolView::CNalmak3D_TerrainToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CNalmak3D_TerrainToolView::~CNalmak3D_TerrainToolView()
{
	Core::DestroyInstance();
}

BOOL CNalmak3D_TerrainToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_TerrainToolView �׸���

void CNalmak3D_TerrainToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_TerrainToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Core::GetInstance()->Run();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CNalmak3D_TerrainToolView �μ�

BOOL CNalmak3D_TerrainToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_TerrainToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CNalmak3D_TerrainToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CNalmak3D_TerrainToolView ����

#ifdef _DEBUG
void CNalmak3D_TerrainToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_TerrainToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_TerrainToolDoc* CNalmak3D_TerrainToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_TerrainToolDoc)));
	return (CNalmak3D_TerrainToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_TerrainToolView �޽��� ó����


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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CNalmak3D_TerrainToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(false);


	CView::OnTimer(nIDEvent);
}
