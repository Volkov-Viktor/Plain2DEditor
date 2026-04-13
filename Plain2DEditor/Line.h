#pragma once

#include "Shape.h"

class CLine : public CShape
{
	DECLARE_SERIAL(CLine)

public:
	virtual ~CLine();
	CLine() noexcept;

	virtual void Draw(CDC* pDC) override;
	virtual void Set_Paint_Area(const CRect& rect) override;
	virtual BOOL Hit_Test(const CPoint& point) const override;
	virtual void Serialize(CArchive& ar) override;

	void Update_End_Point(const CPoint& end_point);

private:
	CPoint m_Start_Point;
	CPoint m_End_Point;
};