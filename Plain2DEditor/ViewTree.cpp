#include "pch.h"
#include "framework.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CViewTree
//------------------------------------------------------------------------------------------------------------
CViewTree::~CViewTree()
{
}
//------------------------------------------------------------------------------------------------------------
CViewTree::CViewTree() noexcept
{
}
//------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{ // Обработчик уведомлений(WM_NOTIFY) для элемента управления деревом
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != nullptr);

// Подавляем предупреждение компилятора C26454 (анализ кода C++ Core Guidelines).
// Компилятор может ошибочно считать, что pNMHDR может быть nullptr после ASSERT.
#pragma warning(suppress : 26454)

	// Проверяем, является ли текущее уведомление запросом на показ подсказки (TTN_SHOW),
	// и есть ли у контрола активный tooltip (GetToolTips() не возвращает nullptr).
	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != nullptr)
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);

	return bRes;
}
//------------------------------------------------------------------------------------------------------------
