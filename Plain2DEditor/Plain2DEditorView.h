
// Plain2DEditorView.h : interface of the CPlain2DEditorView class
//

#pragma once


class CPlain2DEditorView : public CView
{
protected: // create from serialization only
	CPlain2DEditorView() noexcept;
	DECLARE_DYNCREATE(CPlain2DEditorView)

// Attributes
public:
	CPlain2DEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlain2DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Plain2DEditorView.cpp
inline CPlain2DEditorDoc* CPlain2DEditorView::GetDocument() const
   { return reinterpret_cast<CPlain2DEditorDoc*>(m_pDocument); }
#endif

