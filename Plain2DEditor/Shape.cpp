#include "pch.h"
#include "Shape.h"

// CShape
//------------------------------------------------------------------------------------------------------------
CShape::~CShape()
{
}
//------------------------------------------------------------------------------------------------------------
CShape::CShape() noexcept
	: m_Paint_Area(0, 0, 0, 0), m_Fill_Color(RGB(255, 255, 255)), m_Border_Color(RGB(0, 0, 0)), m_Border_Width(2)
{
}
//------------------------------------------------------------------------------------------------------------
void CShape::Set_Paint_Area(const CRect& rect)
{
	m_Paint_Area = rect;
	m_Paint_Area.NormalizeRect();
}
//------------------------------------------------------------------------------------------------------------
BOOL CShape::Hit_Test(const CPoint &point) const
{
	return m_Paint_Area.PtInRect(point);
}
//------------------------------------------------------------------------------------------------------------
void CShape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_Paint_Area.left << m_Paint_Area.top << m_Paint_Area.right << m_Paint_Area.bottom;
		ar << (DWORD)m_Fill_Color << (DWORD)m_Border_Color;
		ar << m_Border_Width;
	}
	else
	{
		DWORD fill_color, border_color;
		ar >> m_Paint_Area.left >> m_Paint_Area.top >> m_Paint_Area.right >> m_Paint_Area.bottom;
		ar >> fill_color >> border_color;
		m_Fill_Color = (COLORREF)fill_color;
		m_Border_Color = (COLORREF)border_color;
		ar >> m_Border_Width;
	}
}
//------------------------------------------------------------------------------------------------------------
void CShape::Set_Fill_Color(COLORREF color)
{ 
	m_Fill_Color = color;
}
//------------------------------------------------------------------------------------------------------------
COLORREF CShape::Get_Fill_Color() const
{ 
	return m_Fill_Color; 
}
//------------------------------------------------------------------------------------------------------------
void CShape::Set_Border_Color(COLORREF color)
{ m_Border_Color = color;
}
//------------------------------------------------------------------------------------------------------------
COLORREF CShape::Get_Border_Color() const 
{ 
	return m_Border_Color; 
}
//------------------------------------------------------------------------------------------------------------
void CShape::Set_Border_Width(int width)
{ 
	m_Border_Width = max(1, width);
}
//------------------------------------------------------------------------------------------------------------
int  CShape::Get_Border_Width() const 
{ 
	return m_Border_Width; 
}
//------------------------------------------------------------------------------------------------------------
