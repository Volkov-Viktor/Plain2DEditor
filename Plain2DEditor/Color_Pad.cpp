#include "pch.h"
#include "framework.h"
#include "Color_Pad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CColor_Pad, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------

// CColor_Pad
//------------------------------------------------------------------------------------------------------------
CColor_Pad::~CColor_Pad()
{
}
//------------------------------------------------------------------------------------------------------------
CColor_Pad::CColor_Pad() noexcept
	: m_Cell_Size(20), m_Gap(3)
{
}
//------------------------------------------------------------------------------------------------------------
void CColor_Pad::Init_Colors()
{
	m_Colors = {
		// Ряд 1 — тёмные / насыщенные цвета
		RGB(0,   0,   0),       // Чёрный
		RGB(127, 127, 127),     // Серый
		RGB(136, 0,   21),      // Тёмно-красный
		RGB(237, 28,  36),      // Красный
		RGB(255, 127, 39),      // Оранжевый
		RGB(255, 242, 0),       // Жёлтый
		RGB(34,  177, 76),      // Зелёный
		RGB(0,   162, 232),     // Голубой
		RGB(63,  72,  204),     // Синий
		RGB(163, 73,  164),     // Фиолетовый

		// Ряд 2 — светлые / пастельные цвета
		RGB(255, 255, 255),     // Белый
		RGB(195, 195, 195),     // Светло-серый
		RGB(185, 122, 87),      // Коричневый
		RGB(255, 174, 201),     // Розовый
		RGB(255, 201, 14),      // Золотой
		RGB(239, 228, 176),     // Светло-жёлтый
		RGB(181, 230, 29),      // Лайм
		RGB(153, 217, 234),     // Светло-голубой
		RGB(112, 146, 190),     // Стальной синий
		RGB(200, 191, 231),     // Лавандовый
	};
}
//------------------------------------------------------------------------------------------------------------
int CColor_Pad::Hit_Test_Color(CPoint point) const
{
	CRect client_rect;
	GetClientRect(&client_rect);

	int cols = max(1, (client_rect.Width() - m_Gap) / (m_Cell_Size + m_Gap));
	int left_margin = (client_rect.Width() - cols * (m_Cell_Size + m_Gap) + m_Gap) / 2;
	int top_margin = 8;

	for (int i = 0; i < (int)m_Colors.size(); ++i)
	{
		CRect cell_rect = Get_Cell_Rect(i, cols, left_margin, top_margin);
		if (cell_rect.PtInRect(point))
			return i;
	}

	return -1;
}
//------------------------------------------------------------------------------------------------------------
CRect CColor_Pad::Get_Cell_Rect(int index, int columns, int left_margin, int top_margin) const
{
	int col = index % columns;
	int row = index / columns;

	int x = left_margin + col * (m_Cell_Size + m_Gap);
	int y = top_margin + row * (m_Cell_Size + m_Gap);

	return CRect(x, y, x + m_Cell_Size, y + m_Cell_Size);
}
//------------------------------------------------------------------------------------------------------------
int CColor_Pad::Get_Columns() const
{
	CRect client_rect;
	GetClientRect(&client_rect);

	int cols = max(1, (client_rect.Width() - m_Gap) / (m_Cell_Size + m_Gap));
	return cols;
}
//------------------------------------------------------------------------------------------------------------
int CColor_Pad::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init_Colors();
	return 0;
}
//------------------------------------------------------------------------------------------------------------
void CColor_Pad::OnPaint()
{
	CPaintDC dc(this);

	CRect client_rect;
	GetClientRect(&client_rect);

	dc.FillSolidRect(client_rect, ::GetSysColor(COLOR_3DFACE)); // Заливка фона

	if (m_Colors.empty())
		return;

	int cols = max(1, (client_rect.Width() - m_Gap) / (m_Cell_Size + m_Gap));
	int left_margin = (client_rect.Width() - cols * (m_Cell_Size + m_Gap) + m_Gap) / 2;
	int top_margin = 8;

	for (int i = 0; i < (int)m_Colors.size(); ++i)
	{
		CRect cell_rect = Get_Cell_Rect(i, cols, left_margin, top_margin);
		dc.FillSolidRect(cell_rect, m_Colors[i]); // заливка ячейки цветом
		dc.Draw3dRect(cell_rect, RGB(96, 96, 96), RGB(96, 96, 96)); // рамка вокруг ячейки
	}
}
//------------------------------------------------------------------------------------------------------------
void CColor_Pad::OnLButtonDown(UINT n_flags, CPoint point)
{
	int index = Hit_Test_Color(point);
	if (index >= 0 && index < (int)m_Colors.size())
	{
		COLORREF selected_color = m_Colors[index];

		CFrameWnd* pFrame = dynamic_cast<CFrameWnd*>(AfxGetMainWnd());
		if (pFrame != nullptr)
		{
			CView* pView = pFrame->GetActiveView();

			
			if (pView == nullptr)
			{ // если GetActiveView() вернул nullptr — ищем вручную среди дочерних окон
				CWnd* pChild = pFrame->GetWindow(GW_CHILD);
				while (pChild != nullptr)
				{
					pView = dynamic_cast<CView*>(pChild);
					if (pView != nullptr)
						break;
					pChild = pChild->GetNextWindow();
				}
			}

			if (pView != nullptr)
				pView->SendMessage(WM_COLOR_SELECTED, (WPARAM)selected_color, 0);
		}
	}

	CDockablePane::OnLButtonDown(n_flags, point);
}
//------------------------------------------------------------------------------------------------------------
void CColor_Pad::OnSize(UINT n_type, int cx, int cy)
{
	CDockablePane::OnSize(n_type, cx, cy);
	Invalidate();
}
//------------------------------------------------------------------------------------------------------------
