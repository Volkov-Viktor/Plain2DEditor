#pragma once

#include "Shape.h"

class CRectangle : public CShape
{
	DECLARE_SERIAL(CRectangle)

public:
	virtual ~CRectangle();
	CRectangle() noexcept;

	virtual void Draw(CDC* pDC) override;
	virtual void Set_Paint_Area(const CRect& rect) override;
	virtual BOOL Hit_Test(const CPoint& point) const override;
	virtual void Serialize(CArchive& ar) override;
};