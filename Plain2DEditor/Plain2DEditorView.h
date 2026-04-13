#pragma once

#include "Plain2DEditorDoc.h"
#include "Line.h"
#include "Rect.h"
#include "Ellipse.h"
#include "Color_Pad.h"

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

	enum class EColor_Target
	{
		Target_None,
		Target_Brush,
		Target_Pen
	};

	ETool_Type m_Current_Tool = ETool_Type::Tool_None;
	EColor_Target m_Color_Target = EColor_Target::Target_None;
	CShape* m_pCurrent_Shape = nullptr; // временная фигура в процессе рисования
	CPoint m_Start_Point;
	CRect m_Prev_Rect_Drawn; // область в процессе рисования фигуры
	int m_Stoke_Size = 4; // запас для перекрытия не только фигуры, но и абриса вокруг нее
	bool m_Is_Drawing = false;

	// Пользовательские цвета (устанавливаются через палитру)
	COLORREF m_User_Fill_Color = RGB(255, 255, 255);
	COLORREF m_User_Border_Color = RGB(0, 0, 0);
	bool m_Has_User_Fill_Color = false;
	bool m_Has_User_Border_Color = false;

// Attributes
public:
	CPlain2DEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CShape* Create_Shape(ETool_Type type);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void On_Tool_Selected(ETool_Type tool_type);
	afx_msg void On_Tool_Brush();
	afx_msg void On_Tool_Pen();
	afx_msg void On_Tool_Line();
	afx_msg void On_Tool_Rectangle();
	afx_msg void On_Tool_Ellipse();
	afx_msg void On_Update_Tool(CCmdUI* pCmdUI, ETool_Type tool_type);
	afx_msg void On_Update_Tool_Line(CCmdUI* pCmdUI);
	afx_msg void On_Update_Tool_Rectangle(CCmdUI* pCmdUI);
	afx_msg void On_Update_Tool_Ellipse(CCmdUI* pCmdUI);
	afx_msg void On_Update_Tool_Brush(CCmdUI* pCmdUI);
	afx_msg void On_Update_Tool_Pen(CCmdUI* pCmdUI);

	afx_msg LRESULT On_Color_Selected(WPARAM wParam, LPARAM lParam);

	void Apply_Color_To_Shape(CShape* shape);

	DECLARE_MESSAGE_MAP()
};
//------------------------------------------------------------------------------------------------------------
#ifndef _DEBUG  // debug version in Plain2DEditorView.cpp
inline CPlain2DEditorDoc* CPlain2DEditorView::GetDocument() const
   { return reinterpret_cast<CPlain2DEditorDoc*>(m_pDocument); }
#endif
//------------------------------------------------------------------------------------------------------------
