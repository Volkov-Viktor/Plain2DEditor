//
#include "pch.h"
//#include "framework.h"
//#include "mainfrm.h"
////#include "FileView.h"
//#include "Resource.h"
//#include "Plain2DEditor.h"
//
//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif
//
//// CFileView
////------------------------------------------------------------------------------------------------------------
//CFileView::~CFileView()
//{
//}
////------------------------------------------------------------------------------------------------------------
//CFileView::CFileView() noexcept
//{
//}
////------------------------------------------------------------------------------------------------------------
//// макросы MFC, связывающие сообщения Windows (события) с методами класса
//BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
//	ON_WM_CREATE()
//	ON_WM_SIZE()
//	ON_WM_CONTEXTMENU()
//	ON_COMMAND(ID_PROPERTIES, OnProperties)
//	ON_COMMAND(ID_OPEN, OnFileOpen)
//	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
//	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
//	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
//	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
//	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
//	ON_WM_PAINT()
//	ON_WM_SETFOCUS()
//END_MESSAGE_MAP()
////------------------------------------------------------------------------------------------------------------
//int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	// Шаг 1: наследуем базовую логику создания панели
//	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// Шаг 2: инициализируем пустой прямоугольник для дерева файлов
//	CRect rectDummy;
//	rectDummy.SetRectEmpty();
//
//	// Шаг 3: создаём дерево файлов с заданными стилями
//	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
//
//	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
//	{
//		TRACE0("Failed to create file view\n");
//		return -1;
//	}
//
//	// Шаг 4: загружаем иконки для узлов дерева
//	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
//	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
//
//	// Шаг 5: создаём и настраиваем панель инструментов
//	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
//	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);
//
//	// Шаг 6: применяем визуальный стиль
//	OnChangeVisualStyle();
//
//	// Шаг 7: настраиваем стили панели инструментов
//	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
//	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
//
//	// Шаг 8: указываем владельца панели инструментов
//	m_wndToolBar.SetOwner(this);
//
//	// Шаг 9: настраиваем маршрутизацию команд (обрабатываем их напрямую)
//	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
//
//	// Шаг 10: заполняем дерево файлов и корректируем макет
//	FillFileView();
//	AdjustLayout();
//
//	return 0;
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnSize(UINT nType, int cx, int cy)
//{
//	// 1. Обрабатываем изменение размера на уровне базовой панели (CDockablePane)
//	CDockablePane::OnSize(nType, cx, cy);
//	// 2. Адаптируем внутренний макет вида под новые размеры (перераспределяем пространство
//	// между деревом файлов и панелью инструментов)
//	AdjustLayout();
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::FillFileView()
//{ // Заполнение дерева файлов (m_wndFileView) данными
//
//	// Создаём корневой узел дерева
//	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("FakeApp files"), 0, 0);
//	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
//
//	// Добавляем узел с исходными файлами (.cpp, .rc)
//	HTREEITEM hSrc = m_wndFileView.InsertItem(_T("FakeApp Source Files"), 0, 0, hRoot);
//	m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
//	m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
//	m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
//	m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
//	m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
//	m_wndFileView.InsertItem(_T("pch.cpp"), 1, 1, hSrc);
//
//	// Добавляем узел с заголовочными файлами (.h)
//	HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp Header Files"), 0, 0, hRoot);
//	m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
//	m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
//	m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
//	m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
//	m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
//	m_wndFileView.InsertItem(_T("pch.h"), 2, 2, hInc);
//
//	// Добавляем узел с ресурсными файлами (.ico, .bmp, .rc2)
//	HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp Resource Files"), 0, 0, hRoot);
//	m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
//	m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
//	m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
//	m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);
//
//	// Раскрываем основные узлы по умолчанию
//	m_wndFileView.Expand(hRoot, TVE_EXPAND);
//	m_wndFileView.Expand(hSrc, TVE_EXPAND);
//	m_wndFileView.Expand(hInc, TVE_EXPAND);
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
//{ // Обработка появления контекстного меню при правом клике мыши в окне CFileView
//	
//	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView; // получение указателя на дерево файлов
//	ASSERT_VALID(pWndTree);
//
//	if (pWnd != pWndTree)
//	{ // Если клик не на дереве — передаём обработку базовому классу
//
//		CDockablePane::OnContextMenu(pWnd, point);
//		return;
//	}
//
//	if (point != CPoint(-1, -1))
//	{ // Если координаты клика корректны, определяем элемент под курсором
//
//		CPoint ptTree = point;
//		pWndTree->ScreenToClient(&ptTree);
//
//		UINT flags = 0;
//		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
//		if (hTreeItem != nullptr)
//			pWndTree->SelectItem(hTreeItem);
//	}
//
//	pWndTree->SetFocus(); // устанавливаем фокус на дерево для корректной работы команд меню
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE); // отображаем контекстное меню в позиции клика
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::AdjustLayout()
//{
//	if (GetSafeHwnd() == nullptr)
//		return;
//
//	// Получаем размеры клиентской области окна
//	CRect rectClient;
//	GetClientRect(rectClient);
//
//	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy; // рассчитываем фиксированную высоту панели инструментов
//
//	// Размещаем панель инструментов в верхней части окна
//	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
//	
//	// Размещаем дерево файлов под панелью инструментов с отступами в 1 пиксель
//	m_wndFileView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnProperties()
//{ // обработчик команды «Свойства»
//	AfxMessageBox(_T("Properties...."));
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnFileOpen()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnFileOpenWith()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnDummyCompile()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnEditCut()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnEditCopy()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnEditClear()
//{
//	// TODO: Add your command handler code here
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnPaint()
//{
//	CPaintDC dc(this); // контекст устройства для отрисовки (автоматически управляет BeginPaint/EndPaint)
//
//	// Получаем экранные координаты дерева файлов
//	CRect rectTree;
//	m_wndFileView.GetWindowRect(rectTree);
//
//	ScreenToClient(rectTree); // преобразуем в клиентские координаты текущего окна (CFileView)
//
//	rectTree.InflateRect(1, 1); // увеличиваем прямоугольник на 1 пиксель со всех сторон
//	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW)); // рисуем тёмную 3D‑рамку вокруг дерева файлов
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnSetFocus(CWnd* pOldWnd)
//{
//	CDockablePane::OnSetFocus(pOldWnd);
//
//	m_wndFileView.SetFocus();
//}
////------------------------------------------------------------------------------------------------------------
//void CFileView::OnChangeVisualStyle()
//{ // Динамическое переключение визуального стиля интерфейса
//	m_wndToolBar.CleanUpLockedImages(); // очистка старых иконок панели инструментов
//	
//	// Загружаем новый набор иконок для панели инструментов
//	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);
//
//	m_FileViewImages.DeleteImageList(); // удаляем старый список изображений для дерева файлов
//
//	// Выбираем ресурс иконок для дерева в зависимости от режима цвета
//	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;
//
//	CBitmap bmp;
//	if (!bmp.LoadBitmap(uiBmpId))
//	{
//		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
//		ASSERT(FALSE);
//		return;
//	}
//
//	BITMAP bmpObj;
//	bmp.GetBitmap(&bmpObj); // получаем информацию о загруженном изображении
//
//	// Настраиваем флаги для создания списка изображений
//	UINT nFlags = ILC_MASK;
//	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;
//	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0); 
//
//	m_FileViewImages.Add(&bmp, RGB(255, 0, 255)); // добавление иконок в список
//
//	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL); // привязка нового списка иконок к дереву файлов
//}
////------------------------------------------------------------------------------------------------------------