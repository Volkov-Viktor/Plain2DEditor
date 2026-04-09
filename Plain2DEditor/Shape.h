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

	// Утилиты доступа к цветам/толщине
	//void Set_Fill_Color(COLORREF c) { m_Fill_Color = c; }
	//COLORREF Get_Fill_Color() const { return m_Fill_Color; }

	//void Set_Border_Color(COLORREF c) { m_Border_Color = c; }
	//COLORREF Get_Border_Color() const { return m_Border_Color; }

	//void Set_Border_Width(int w) { m_Border_Width = max(1, w); }
	//int  Get_Border_Width() const { return m_Border_Width; }

protected:
	CRect m_Paint_Area;
	COLORREF m_Fill_Color;
	COLORREF m_Border_Color;
	int m_Border_Width;
};
//------------------------------------------------------------------------------------------------------------
