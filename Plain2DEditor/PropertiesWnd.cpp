#include "pch.h"
#include "framework.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Plain2DEditor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__; // сохранение имени текущего файла для отладки
#define new DEBUG_NEW
#endif

// CPropertiesWnd
//------------------------------------------------------------------------------------------------------------
CPropertiesWnd::~CPropertiesWnd()
{
}
//------------------------------------------------------------------------------------------------------------
CPropertiesWnd::CPropertiesWnd() noexcept
{
	m_nComboHeight = 0; // инициализация высоты выпадающего списка (комбобокса) нулём
}
//------------------------------------------------------------------------------------------------------------
// Карта сообщений для класса CPropertiesWnd (наследует CDockablePane)
BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::AdjustLayout()
{ // корректировка расположения элементов внутри панели
	if (GetSafeHwnd () == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
		return; // проверка создания главного окна и того, что оно не свернуто

	CRect rectClient;
	GetClientRect(rectClient); // получение размеров клиентской области

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy; // расчет высоты панели инструментов

	// Устанавливаем позицию и размер выпадающего списка (комбобокса), панели инструментов и списка свойств
	m_wndObjectCombo.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}
//------------------------------------------------------------------------------------------------------------
int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1) // вызов реализации базового класса
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Создание выпадающего списка(комбобокса) объектов
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;
	}

	// Добавляем элементы в выпадающий список
	m_wndObjectCombo.AddString(_T("Application"));
	m_wndObjectCombo.AddString(_T("Properties Window"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect(&rectCombo); // получаем размеры клиентской области комбобокса
	m_nComboHeight = rectCombo.Height(); // сохраняем высоту комбобокса для дальнейшего использования при компоновке

	// Создание списка свойств (грида)
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList(); // инициализация списка свойств (заполнение начальными данными)

	// Создание панели инструментов
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	// Настройка стилей панели инструментов
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// Все команды будут маршрутизироваться через этот контроль, а не через родительский фрейм
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout(); // корректировка расположения элементов внутри панели
	return 0;
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{ // Обработка изменения размера окна
	CDockablePane::OnSize(nType, cx, cy); // вызов реализации базового класса для стандартной обработки изменения размера
	AdjustLayout(); // корректируем расположение элементов внутри панели с учётом новых размеров
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnExpandAllProperties()
{ // Обработчик команды «Развернуть все свойства»
	m_wndPropList.ExpandAll();
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
	// Обновление состояния команды «Развернуть все свойства»(для интерфейса)
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnSortProperties()
{ // Обработчик команды «Сортировка свойств»
	// Переключаем режим сортировки: если сейчас алфавитный — переходим в обычный, и наоборот
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{ // Обновление состояния команды «Сортировка свойств» (для интерфейса)
	// Устанавливаем отметку (чекбокс) в меню/панели инструментов:
	// если режим алфавитной сортировки активен — ставим галочку
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnProperties1()
{ // Обработчик команды Properties1 (пользовательская команда 1)
	// TODO: добавьте код обработчика команды здесь
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{ // Обновление состояния команды Properties1 (для интерфейса)
	// TODO: добавьте код обновления состояния UI здесь
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnProperties2()
{ // Обработчик команды Properties2 (пользовательская команда 2)
	// TODO: добавьте код обработчика команды здесь
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: добавьте код обработчика команды здесь
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::InitPropList()
{
	SetPropListFont(); // Устанавливаем шрифт для списка свойств

	m_wndPropList.EnableHeaderCtrl(FALSE); // отключаем заголовок таблицы (колонки)
	m_wndPropList.EnableDescriptionArea(); // включаем область описания свойств (под списком)
	m_wndPropList.SetVSDotNetLook(); // устанавливаем стиль оформления в духе Visual Studio .NET
	m_wndPropList.MarkModifiedProperties(); // помечаем изменённые свойства (визуальное выделение)

	// Группа 1: «Внешний вид» (Appearance)
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Appearance"));

	// Свойство «3D Look» — булево значение(включено / выключено)
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t) false, _T("Specifies the window's font will be non-bold and controls will have a 3D border")));

	// Свойство «Border» — выпадающий список с вариантами рамки
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	// Свойство «Caption» — текстовое поле для заголовка окна
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t) _T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	m_wndPropList.AddProperty(pGroup1); // добавляем группу «Appearance» в список свойств

	// Группа 2: «Размер окна» (Window Size) — высота и ширина с счётчиками
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);
	
	// Cвойство «Height» со счётчиком (spin control)
	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t) 250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	// Cвойство «Width» со счётчиком
	pProp = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize); // добавляем группу «Window Size» в список

	// Группа 3: «Шрифт» (Font)
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);
	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	// Свойство выбора шрифта
	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	// Свойство «Использовать системный шрифт» — булево значение
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	m_wndPropList.AddProperty(pGroup2); // добавляем группу «Font» в список

	// Группа 4: «Разное» (Misc) — прочие настройки окна
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	
	// Свойство «(Name)»
	pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	// Свойство выбора цвета окн
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), nullptr, _T("Specifies the default window color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	// Фильтр для диалогового окна выбора файла
	static const TCHAR szFilter[] = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
	
	// Свойство выбора файла иконки
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon")));

	// Свойство выбора файла папки
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Folder"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3); // добавляем группу «Misc» в грид

	// Группа 5: «Иерархия» (Hierarchy) — пример вложенной структуры свойств
	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	// Уровень 1: первая вложенная группа
	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	pGroup4->AddSubItem(pGroup41);

	// Уровень 2: вторая вложенная группа
	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	pGroup41->AddSubItem(pGroup411);

	// Добавляем три простых свойства во вторую вложенную группу
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t) _T("Value 1"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t) _T("Value 2"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t) _T("Value 3"), _T("This is a description")));

	pGroup4->Expand(FALSE); // по умолчанию группа «Hierarchy» свернута
	m_wndPropList.AddProperty(pGroup4);  // добавление всей вложенной структуры(группы «Hierarchy» со всеми подгруппами) в грид свойств
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{ //  Обработка события получения фокуса окном
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{ // обработка системных событий изменения настроек
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}
//------------------------------------------------------------------------------------------------------------
void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach()); // удаляем предыдущий шрифт (если он был создан), чтобы избежать утечек памяти

	// Получаем базовые параметры шрифта из глобальных данных MFC
	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	// Инициализируем структуру для получения метрик неклиентской области
	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	// Заполняем структуру текущими системными метриками (шрифты меню, отступы и т. д.)
	afxGlobalData.GetNonClientMetrics(info);

	// Настраиваем параметры шрифта на основе системных метрик меню
	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf); // новый шрифт с обновлёнными параметрами

	// Применяем новый шрифт к элементам управления
	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}
//------------------------------------------------------------------------------------------------------------
