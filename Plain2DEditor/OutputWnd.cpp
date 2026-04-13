//
//#include "pch.h"
//#include "framework.h"
//
//#include "OutputWnd.h"
//#include "Resource.h"
//#include "MainFrm.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//// COutputBar
////------------------------------------------------------------------------------------------------------------
//COutputWnd::~COutputWnd()
//{
//}
////------------------------------------------------------------------------------------------------------------
//COutputWnd::COutputWnd() noexcept
//{
//}
////------------------------------------------------------------------------------------------------------------
//BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
//	ON_WM_CREATE()
//	ON_WM_SIZE()
//END_MESSAGE_MAP()
////------------------------------------------------------------------------------------------------------------
//int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{ // инициализация окна вывода с вкладками(Build, Debug, Find) при создании окна
//
//	if (CDockablePane::OnCreate(lpCreateStruct) == -1) // Базовая инициализация через родительский класс
//		return -1;
//
//	CRect rectDummy;
//	rectDummy.SetRectEmpty();
//
//	// создаём контейнер (m_wndTabs) вкладок
//	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
//	{
//		TRACE0("Failed to create output tab window\n");
//		return -1;
//	}
//
//	// Определяем стиль окон вывода: без интегральной высоты, дочернее окно, видимое, с горизонтальной и вертикальной прокруткой
//	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
//
//	// Создаём три панели вывода (Build, Debug, Find)
//	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
//		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
//		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
//	{
//		TRACE0("Failed to create output windows\n");
//		return -1;
//	}
//
//	UpdateFonts();
//
//	CString strTabName;
//	BOOL bNameValid;
//
//	// Привязываем панели к вкладкам и задаём локализованные названия
//	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
//	ASSERT(bNameValid);
//	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
//	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
//	ASSERT(bNameValid);
//	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
//	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
//	ASSERT(bNameValid);
//	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);
//
//	// Заполняем панели тестовым текстом
//	FillBuildWindow();
//	FillDebugWindow();
//	FillFindWindow();
//
//	return 0;
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::OnSize(UINT nType, int cx, int cy)
//{ // При изменении размера окна, корректируем размер вкладок, чтобы они занимали всё клиентское пространство
//	CDockablePane::OnSize(nType, cx, cy);
//	m_wndTabs.SetWindowPos (nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
//{ // Вычисляем максимальную ширину текста в списке и устанавливаем горизонтальную прокрутку, чтобы обеспечить видимость всего текста
//	CClientDC dc(this);
//	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);
//
//	int cxExtentMax = 0;
//
//	for (int i = 0; i < wndListBox.GetCount(); ++i)
//	{
//		CString strItem;
//		wndListBox.GetText(i, strItem);
//
//		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
//	}
//
//	wndListBox.SetHorizontalExtent(cxExtentMax);
//	dc.SelectObject(pOldFont);
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::FillBuildWindow()
//{ // Заполняем панель Build тестовыми строками, демонстрируя, что вывод отображается в виде строк списка, но при этом можно изменить способ отображения по своему усмотрению
//	m_wndOutputBuild.AddString(_T("Build output is being displayed here."));
//	m_wndOutputBuild.AddString(_T("The output is being displayed in rows of a list view"));
//	m_wndOutputBuild.AddString(_T("but you can change the way it is displayed as you wish..."));
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::FillDebugWindow()
//{ // Заполняем панель Debug тестовыми строками, демонстрируя, что вывод отображается в виде строк списка, но при этом можно изменить способ отображения по своему усмотрению
//	m_wndOutputDebug.AddString(_T("Debug output is being displayed here."));
//	m_wndOutputDebug.AddString(_T("The output is being displayed in rows of a list view"));
//	m_wndOutputDebug.AddString(_T("but you can change the way it is displayed as you wish..."));
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::FillFindWindow()
//{ // Заполняем панель Find тестовыми строками, демонстрируя, что вывод отображается в виде строк списка, но при этом можно изменить способ отображения по своему усмотрению
//	m_wndOutputFind.AddString(_T("Find output is being displayed here."));
//	m_wndOutputFind.AddString(_T("The output is being displayed in rows of a list view"));
//	m_wndOutputFind.AddString(_T("but you can change the way it is displayed as you wish..."));
//}
////------------------------------------------------------------------------------------------------------------
//void COutputWnd::UpdateFonts()
//{ // Устанавливаем шрифт для всех панелей вывода, используя глобальный шрифт, определённый в MFC
//	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
//	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
//	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
//}
////------------------------------------------------------------------------------------------------------------
//
//
//
//
//// COutputList1
////------------------------------------------------------------------------------------------------------------
//COutputList::~COutputList()
//{
//}
////------------------------------------------------------------------------------------------------------------
//COutputList::COutputList() noexcept
//{
//}
////------------------------------------------------------------------------------------------------------------
//BEGIN_MESSAGE_MAP(COutputList, CListBox)
//	ON_WM_CONTEXTMENU()
//	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
//	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
//	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
//	ON_WM_WINDOWPOSCHANGING()
//END_MESSAGE_MAP()
////------------------------------------------------------------------------------------------------------------
//void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
//{ // При вызове контекстного меню, загружаем меню из ресурсов и отображаем его в позиции курсора
//	CMenu menu;
//	menu.LoadMenu(IDR_OUTPUT_POPUP);
//
//	CMenu* pSumMenu = menu.GetSubMenu(0);
//
//	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
//	{
//		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
//
//		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
//			return;
//
//		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
//		UpdateDialogControls(this, FALSE);
//	}
//
//	SetFocus();
//}
////------------------------------------------------------------------------------------------------------------
//void COutputList::OnEditCopy()
//{ // При выборе команды "Copy" в контекстном меню, отображаем сообщение (в реальной реализации здесь будет код для копирования текста в буфер обмена)
//	MessageBox(_T("Copy output"));
//}
////------------------------------------------------------------------------------------------------------------
//void COutputList::OnEditClear()
//{ // При выборе команды "Clear" в контекстном меню, отображаем сообщение (в реальной реализации здесь будет код для очистки содержимого панели вывода)
//	MessageBox(_T("Clear output"));
//}
////------------------------------------------------------------------------------------------------------------
//void COutputList::OnViewOutput()
//{ // При выборе команды "View Output" в контекстном меню, скрываем панель вывода, если она видима, или показываем её, если она скрыта
//	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
//	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());
//
//	if (pMainFrame != nullptr && pParentBar != nullptr)
//	{
//		pMainFrame->SetFocus();
//		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
//		pMainFrame->RecalcLayout();
//
//	}
//}
////------------------------------------------------------------------------------------------------------------
