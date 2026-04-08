// Plain2DEditorView.h : interface of the CPlain2DEditorView class
#pragma once

#include "Shape.h"

//------------------------------------------------------------------------------------------------------------
class CPlain2DEditorView : public CView
{
protected:
	CPlain2DEditorView() noexcept;
	DECLARE_DYNCREATE(CPlain2DEditorView)

	enum class ETool_Type
	{
		Tool_None,

		Tool_Line,
		Tool_Rect,
		Tool_Ellipse
	};

	ETool_Type m_Current_Tool = ETool_Type::Tool_None;
	CShape* m_pCurrent_Shape = nullptr; // временная фигура в процессе рисования
	CPoint m_Start_Point;
	bool m_Is_Drawing = false;

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

	afx_msg CShape* Create_Shape(ETool_Type type);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void On_Tool_Ellipse();
	afx_msg void On_Update_Tool_Ellipse(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
//------------------------------------------------------------------------------------------------------------
#ifndef _DEBUG  // debug version in Plain2DEditorView.cpp
inline CPlain2DEditorDoc* CPlain2DEditorView::GetDocument() const
   { return reinterpret_cast<CPlain2DEditorDoc*>(m_pDocument); }
#endif
//------------------------------------------------------------------------------------------------------------
