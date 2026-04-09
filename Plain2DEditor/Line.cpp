#include "pch.h"
#include "Line.h"

// CEllipse
//------------------------------------------------------------------------------------------------------------
CLine::~CLine()
{
}
//------------------------------------------------------------------------------------------------------------
CLine::CLine() noexcept
	: m_Start_Point(0, 0), m_End_Point(0, 0)
{
}
//------------------------------------------------------------------------------------------------------------
void CLine::Set_Paint_Area(const CRect& rect)
{
	m_Start_Point = CPoint(rect.left, rect.top); // rect передаётся как CRect(startPoint, endPoint) из View
	m_End_Point = CPoint(rect.right, rect.bottom); // left,top = начало; right,bottom = конец — ДО нормализации

	CShape::Set_Paint_Area(rect); // вызывается для нормализации ограничевающего прямоугольника
}
//------------------------------------------------------------------------------------------------------------
void CLine::Draw(CDC* pDC)
{
	if (pDC == nullptr)
		return;

	CPen pen(PS_SOLID, m_Border_Width, m_Border_Color);
	CPen* orig_pen = pDC->SelectObject(&pen);

	// Отрисовка с использонием не нормализованных, а реальных точек
	pDC->MoveTo(m_Start_Point);
	pDC->LineTo(m_End_Point);

	pDC->SelectObject(orig_pen);
}
//------------------------------------------------------------------------------------------------------------
BOOL CLine::Hit_Test(const CPoint& point) const
{
	return CShape::Hit_Test(point);
}
//------------------------------------------------------------------------------------------------------------
void CLine::Serialize(CArchive& ar)
{
	//CShape::Serialize(ar); // базовые поля

	//if (ar.IsStoring())
	//{
	//	ar << m_Start_Point.x << m_Start_Point.y;
	//	ar << m_End_Point.x << m_End_Point.y;
	//}
	//else
	//{
	//	ar >> m_Start_Point.x >> m_Start_Point.y;
	//	ar >> m_End_Point.x >> m_End_Point.y;
	//}
}
//------------------------------------------------------------------------------------------------------------
void CLine::Update_End_Point(const CPoint& end_point)
{
	m_End_Point = end_point;
	m_Paint_Area = CRect(m_Start_Point, m_End_Point);
	m_Paint_Area.NormalizeRect();
}
//------------------------------------------------------------------------------------------------------------
