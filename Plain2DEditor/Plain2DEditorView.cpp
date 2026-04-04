// Plain2DEditorView.cpp — реализация класса CPlain2DEditorView (представление документа)

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS может быть определён в проекте ATL для реализации:
// - обработчиков предварительного просмотра;
// - создания миниатюр (thumbnails);
// - фильтров поиска.
// Позволяет использовать общий код документа в нескольких проектах.
#ifndef SHARED_HANDLERS
#include "Plain2DEditor.h"
#endif

#include "Plain2DEditorDoc.h"
#include "Plain2DEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlain2DEditorView
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CPlain2DEditorView, CView) // регистрация класса для динамического создания (MFC)

// Карта сообщений для класса представления
BEGIN_MESSAGE_MAP(CPlain2DEditorView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlain2DEditorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorView::~CPlain2DEditorView()
{
}
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorView::CPlain2DEditorView() noexcept
{
	// TODO: добавьте код инициализации здесь
}
//------------------------------------------------------------------------------------------------------------
BOOL CPlain2DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{ // Предварительная настройка окна перед созданием
	// TODO: измените класс окна или стили здесь, модифицируя структуру CREATESTRUCT
	// Например: добавление стилей окна, изменение класса окна

	return CView::PreCreateWindow(cs);  // Вызываем реализацию базового класса
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnDraw(CDC* /*pDC*/)
{ // Основной метод отрисовки содержимого
	CPlain2DEditorDoc* pDoc = GetDocument();  // Получаем указатель на документ
	ASSERT_VALID(pDoc);  // Проверяем корректность указателя на документ
	if (!pDoc)
		return;  // Если документ не найден, выходим

	// TODO: добавьте код отрисовки данных документа здесь
	// Например: отрисовка геометрических фигур, текста, графических объектов
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnFilePrintPreview()
{ // Обработка команды «Предварительный просмотр печати»
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this); // запуск режима предварительного просмотра печати
#endif
}
//------------------------------------------------------------------------------------------------------------
BOOL CPlain2DEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{ // Подготовка к печати
	return DoPreparePrinting(pInfo); // стандартная подготовка
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{ // Начало печати (дополнительная инициализация перед печатью
	// TODO: добавьте дополнительную инициализацию перед печатью
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{ // Завершение печати (очистка после печати
	// TODO: добавьте код очистки после печати
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{ // Обработка отпускания правой кнопки мыши
	ClientToScreen(&point);  // преобразуем координаты из клиентской области в экранные
	OnContextMenu(this, point);  // вызываем контекстное меню в указанной точке
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{ // Отображение контекстного меню
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
//------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::AssertValid() const
{ // Проверка корректности состояния объекта (только в отладочной версии)
	CView::AssertValid();
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::Dump(CDumpContext& dc) const
{ // Вывод отладочной информации о состоянии объекта
	CView::Dump(dc);
}
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorDoc* CPlain2DEditorView::GetDocument() const // non-debug version is inline
{ // Получение указателя на связанный документ
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlain2DEditorDoc))); // Проверяем, что документ имеет правильный тип
	return (CPlain2DEditorDoc*)m_pDocument; // возвращаем указатель на документ
}
//------------------------------------------------------------------------------------------------------------
#endif //_DEBUG
