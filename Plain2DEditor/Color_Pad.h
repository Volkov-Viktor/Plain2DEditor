#pragma once

#include <vector>
#include <afxwin.h> 

//------------------------------------------------------------------------------------------------------------
#define WM_COLOR_SELECTED (WM_APP + 1)

//------------------------------------------------------------------------------------------------------------
class CColor_Pad : public CDockablePane
{
public:
	virtual ~CColor_Pad();
	CColor_Pad() noexcept;

protected:
	void Init_Colors();
	int Hit_Test_Color(CPoint point) const;
	CRect Get_Cell_Rect(int index, int columns, int left_margin, int top_margin) const;
	int Get_Columns() const;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

	int m_Cell_Size;
	int m_Gap;
	std::vector<COLORREF> m_Colors;
};
//------------------------------------------------------------------------------------------------------------
