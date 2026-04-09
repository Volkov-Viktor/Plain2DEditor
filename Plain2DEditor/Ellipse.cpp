#include "pch.h"
#include "Ellipse.h"

// CEllipse
//------------------------------------------------------------------------------------------------------------
CEllipse::~CEllipse()
{
}
//------------------------------------------------------------------------------------------------------------
CEllipse::CEllipse() noexcept
{
}
//------------------------------------------------------------------------------------------------------------
void CEllipse::Set_Paint_Area(const CRect& rect)
{
	CShape::Set_Paint_Area(rect);
}
//------------------------------------------------------------------------------------------------------------
void CEllipse::Draw(CDC* pDC)
{
	if (pDC == nullptr)
		return;

	CPen pen(PS_SOLID, m_Border_Width, m_Border_Color);
	CBrush brush(m_Fill_Color);

	CPen* orig_pen = pDC->SelectObject(&pen);
	CBrush* orig_brush = pDC->SelectObject(&brush);

	pDC->Ellipse(m_Paint_Area);

	pDC->SelectObject(orig_pen);
	pDC->SelectObject(orig_brush);
}
//------------------------------------------------------------------------------------------------------------
BOOL CEllipse::Hit_Test(const CPoint& point) const
{
	CRect paint_area = m_Paint_Area;
	paint_area.NormalizeRect();

	double semiaxis_gorizontal = paint_area.Width() / 2.0;
	double semiaxis_vertical = paint_area.Height() / 2.0;

	if (semiaxis_gorizontal <= 0 || semiaxis_vertical <= 0)
		return FALSE;

	double center_x = paint_area.left + semiaxis_gorizontal;
	double center_y = paint_area.top + semiaxis_vertical;

	double offset_x = point.x - center_x;
	double offset_y = point.y - center_y;

	double res = (offset_x * offset_x) / (semiaxis_gorizontal * semiaxis_gorizontal) +
		(offset_y * offset_y) / (semiaxis_vertical * semiaxis_vertical);

	const double epsilon = 1e-9;
	return res <= 1.0 + epsilon;
}
//------------------------------------------------------------------------------------------------------------
void CEllipse::Serialize(CArchive& ar)
{	
	CShape::Serialize(ar);
}
//------------------------------------------------------------------------------------------------------------
