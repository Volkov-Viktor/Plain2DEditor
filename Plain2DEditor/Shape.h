#pragma once

#include <afxwin.h>

//------------------------------------------------------------------------------------------------------------
class CShape : public CObject
{
public:
	virtual ~CShape();
	CShape() noexcept;

	virtual void Draw(CDC* pDC) = 0;
	virtual void Set_Paint_Area(const CRect& rect);
	virtual BOOL Hit_Test(const CPoint &point) const;
	virtual void Serialize(CArchive& ar) override;

	void Set_Fill_Color(COLORREF c);
	COLORREF Get_Fill_Color() const;
	void Set_Border_Color(COLORREF c);
	COLORREF Get_Border_Color() const;
	void Set_Border_Width(int w);
	int  Get_Border_Width() const;

protected:
	CRect m_Paint_Area;
	COLORREF m_Fill_Color;
	COLORREF m_Border_Color;
	int m_Border_Width;
};
//------------------------------------------------------------------------------------------------------------
