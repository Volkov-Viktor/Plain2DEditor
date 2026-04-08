#pragma once

#include "Shape.h"

class CEllipse : public CShape
{
public:
	virtual ~CEllipse();
	CEllipse() noexcept;

	virtual void Draw(CDC* pDC) override;
	virtual void Set_Paint_Area(const CRect& rc) override;
	virtual BOOL Hit_Test(const CPoint& pt) const override;
	virtual void Serialize(CArchive& ar) override;
};