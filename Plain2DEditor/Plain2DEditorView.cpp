
// Plain2DEditorView.cpp : implementation of the CPlain2DEditorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Plain2DEditor.h"
#endif

#include "Plain2DEditorDoc.h"
#include "Plain2DEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlain2DEditorView

IMPLEMENT_DYNCREATE(CPlain2DEditorView, CView)

BEGIN_MESSAGE_MAP(CPlain2DEditorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlain2DEditorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPlain2DEditorView construction/destruction

CPlain2DEditorView::CPlain2DEditorView() noexcept
{
	// TODO: add construction code here

}

CPlain2DEditorView::~CPlain2DEditorView()
{
}

BOOL CPlain2DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlain2DEditorView drawing

void CPlain2DEditorView::OnDraw(CDC* /*pDC*/)
{
	CPlain2DEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPlain2DEditorView printing


void CPlain2DEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlain2DEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlain2DEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlain2DEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlain2DEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlain2DEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlain2DEditorView diagnostics

#ifdef _DEBUG
void CPlain2DEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CPlain2DEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlain2DEditorDoc* CPlain2DEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlain2DEditorDoc)));
	return (CPlain2DEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlain2DEditorView message handlers
