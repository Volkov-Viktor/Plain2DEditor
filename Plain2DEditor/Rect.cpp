#include "pch.h"
#include "Rect.h"

IMPLEMENT_SERIAL(CRectangle, CShape, 1)

// CRectangle
//------------------------------------------------------------------------------------------------------------
CRectangle::~CRectangle()
{
}
//------------------------------------------------------------------------------------------------------------
CRectangle::CRectangle() noexcept
{
}
//------------------------------------------------------------------------------------------------------------
void CRectangle::Set_Paint_Area(const CRect& rect)
{
	CShape::Set_Paint_Area(rect);
}
//------------------------------------------------------------------------------------------------------------
void CRectangle::Draw(CDC* pDC)
{
	if (pDC == nullptr)
		return;

	CPen pen(PS_SOLID, m_Border_Width, m_Border_Color);
	CBrush brush(m_Fill_Color);

	CPen* orig_pen = pDC->SelectObject(&pen);
	CBrush* orig_brush = pDC->SelectObject(&brush);

	pDC->Rectangle(m_Paint_Area);

	pDC->SelectObject(orig_pen);
	pDC->SelectObject(orig_brush);
}
//------------------------------------------------------------------------------------------------------------
BOOL CRectangle::Hit_Test(const CPoint& point) const
{
	CRect paint_area = m_Paint_Area;
	paint_area.NormalizeRect();

	BOOL hit_x = (point.x >= paint_area.left && point.x <= paint_area.right);
	BOOL hit_y = (point.y >= paint_area.top && point.y <= paint_area.bottom);

	return hit_x && hit_y;
}
//------------------------------------------------------------------------------------------------------------
void CRectangle::Serialize(CArchive& ar)
{
	CShape::Serialize(ar);
}
//------------------------------------------------------------------------------------------------------------
