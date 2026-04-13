#pragma once

#include "Shape.h"

class CEllipse : public CShape
{
	DECLARE_SERIAL(CEllipse)

public:
	virtual ~CEllipse();
	CEllipse() noexcept;

	virtual void Draw(CDC* pDC) override;
	virtual void Set_Paint_Area(const CRect& rect) override;
	virtual BOOL Hit_Test(const CPoint& point) const override;
	virtual void Serialize(CArchive& ar) override;
};