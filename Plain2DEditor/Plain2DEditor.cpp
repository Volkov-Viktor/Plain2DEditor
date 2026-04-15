#include "pch.h"  // Предварительно скомпилированный заголовок — ускоряет компиляцию
#include "Plain2DEditor.h"
#include "MainFrm.h"
#include "Plain2DEditorDoc.h"
#include "Plain2DEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlain2DEditorApp
//------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CPlain2DEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPlain2DEditorApp::OnAppAbout) // обработчик команды «О программе» (вызывает диалоговое окно с информацией)
	
	// Стандартные команды для работы с документами на основе файлов
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew) // создать новый документ
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen) // открыть существующий документ
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorApp::CPlain2DEditorApp() noexcept
{
	m_bHiColorIcons = TRUE; // используем полноцветные иконки (32 бита)
	m_nAppLook = 0; // стиль интерфейса: 0 — стандартный вид Windows
	
	// // Поддержка Restart Manager (восстановление после сбоя)
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение собрано с поддержкой Common Language Runtime (/clr):
	//   1) Эта настройка нужна для корректной работы Restart Manager.
	//   2) В проекте должна быть ссылка на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените строку ID приложения на уникальную.
	// Рекомендуемый формат: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Plain2DEditor.AppID.NoVersion"));

	// TODO: добавьте код инициализации здесь.
	// Всю значимую инициализацию размещайте в InitInstance()
}
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorApp theApp; // единственный экземпляр приложения CPlain2DEditorApp
//------------------------------------------------------------------------------------------------------------
BOOL CPlain2DEditorApp::InitInstance() // инициализация приложения CPlain2DEditorApp
{
	// InitCommonControlsEx() обязателен для Windows XP, если манифест приложения
	// указывает на использование ComCtl32.dll версии 6+ (для поддержки визуальных стилей).
	// Без этого создание окон будет неудачным.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	// Укажите классы общих элементов управления, которые вы хотите использовать
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls); // инициализация базового класса MFC

	CWinAppEx::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer(); // разрешить использование контейнеров элементов управления
	EnableTaskbarInteraction(FALSE); // отключить взаимодействие с панелью задач Windows

	// Стандартная инициализация
	// Если вы не используете эти функции, удалите соответствующие блоки для уменьшения размера исполняемого файла
	// Изменяем ключ реестра, где хранятся настройки приложения
	// TODO: изменить эту строку на что‑то подходящее (название компании и т. д.)
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4); // Загружаем стандартные настройки из INI‑файла (включая список последних файлов — MRU)
	
	InitContextMenuManager(); // Инициализация менеджера контекстных меню
	InitKeyboardManager(); // Инициализация менеджера клавиатурных сокращений
	InitTooltipManager(); // Инициализация менеджера всплывающих подсказок

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Регистрируем шаблоны документов приложения. Шаблоны связывают:
	// документы, окна фреймов и представления
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPlain2DEditorDoc),
		RUNTIME_CLASS(CMainFrame), // главное окно SDI
		RUNTIME_CLASS(CPlain2DEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Парсим командную строку на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Разрешаем открытие через DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Обрабатываем команды, указанные в командной строке. Вернёт FALSE, если
	// приложение запущено с параметрами /RegServer, /Register, /Unregserver или /Unregister
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Главное окно инициализировано — показываем и обновляем его
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// Вызываем DragAcceptFiles только если есть суффикс
	// В SDI‑приложении это должно происходить после ProcessShellCommand
	// Разрешаем перетаскивание файлов для открытия
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}
//------------------------------------------------------------------------------------------------------------
int CPlain2DEditorApp::ExitInstance()
{ // Метод завершения работы приложения
	//TODO: обработайте дополнительные ресурсы, которые вы могли добавить в приложении
	AfxOleTerm(FALSE); // завершение работы с библиотеками OLE (корректное отключение)

	return CWinAppEx::ExitInstance(); // вызов реализации базового класса для завершения работы MFC‑приложения
}
//------------------------------------------------------------------------------------------------------------
class CAboutDlg : public CDialogEx
{ // Диалоговое окно «О программе»(используется для отображения информации о приложении)
public:
	CAboutDlg() noexcept;

// Данные диалога
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX }; // Идентификатор ресурса диалога (используется в дизайнере ресурсов)
#endif

protected:
	// Метод обмена данными (Data Exchange) — поддерживает механизм DDX/DDV:
	// DDX (Dialog Data Exchange) — обмен данными между элементами управления и переменными
	// DDV (Dialog Data Validation) — валидация данных
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Реализация
protected:
	DECLARE_MESSAGE_MAP() // макрос объявления карты сообщений для диалогового окна
};
//------------------------------------------------------------------------------------------------------------
CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{ // Конструктор диалогового окна «О программе»
	// Пустой конструктор: вся инициализация выполняется базовым классом CDialogEx
	// IDD_ABOUTBOX — идентификатор ресурса диалога в файле ресурсов (.rc)
}
//------------------------------------------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{ // Метод обмена данными (DDX/DDV) для диалогового окна
	CDialogEx::DoDataExchange(pDX);
}
//------------------------------------------------------------------------------------------------------------
// Карта сообщений для диалогового окна CAboutDlg
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorApp::OnAppAbout()
{ // Команда приложения для отображения диалогового окна «О программе»
	CAboutDlg aboutDlg; // Создаём экземпляр диалогового окна «О программе»
	aboutDlg.DoModal(); // Отображаем окно в модальном режиме (блокирует основное окно до закрытия)
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorApp::PreLoadState()
{ // Предварительная загрузка состояния приложения (инициализация контекстных меню)
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorApp::LoadCustomState()
{ // Загрузка пользовательского состояния приложения
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorApp::SaveCustomState()
{ // Сохранение пользовательского состояния приложения
}
//------------------------------------------------------------------------------------------------------------
