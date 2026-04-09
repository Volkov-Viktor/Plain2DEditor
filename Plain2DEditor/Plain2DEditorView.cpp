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
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_LINE, &CPlain2DEditorView::On_Tool_Line)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPlain2DEditorView::On_Update_Tool_Line)
	ON_COMMAND(ID_RECT, &CPlain2DEditorView::On_Tool_Rectangle)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CPlain2DEditorView::On_Update_Tool_Rectangle)
	ON_COMMAND(ID_ELLIPSE, &CPlain2DEditorView::On_Tool_Ellipse)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPlain2DEditorView::On_Update_Tool_Ellipse)
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
void CPlain2DEditorView::OnDraw(CDC* pDC)
{ // Основной метод отрисовки содержимого

	CRect client_rect;
	GetClientRect(&client_rect);

	// Создаём совместимый memory DC и bitmap
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, client_rect.Width(), client_rect.Height());
	CBitmap* pOldBmp = memDC.SelectObject(&bmp);

	// Очистка бек‑буфера цветом окна
	memDC.FillSolidRect(&client_rect,::GetSysColor(COLOR_WINDOW));

	// Рисуем все фигуры в memDC
	CPlain2DEditorDoc* pDoc = GetDocument();  // Получаем указатель на документ
	ASSERT_VALID(pDoc);  // Проверяем корректность указателя на документ
	if (pDoc)
	{
		for (int i = 0; i < pDoc->m_Shapes.GetSize(); i++)
		{ // отсрисовка сохраненных фигур из документа
			CShape* shape = (CShape*)pDoc->m_Shapes[i];
			if (shape)
				shape->Draw(&memDC);
		}
	}

	// Отрисовка временной фигуры (при рисовании)
	if (m_pCurrent_Shape) 
		m_pCurrent_Shape->Draw(&memDC);

	// Копируем на экран
	pDC->BitBlt(0, 0, client_rect.Width(), client_rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBmp); // восстановление
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
//------------------------------------------------------------------------------------------------------------
BOOL CPlain2DEditorView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE; // фон не стираем, будем рисовать сами в OnDraw (для реализации двойной буферизации)
}
//------------------------------------------------------------------------------------------------------------
CShape* CPlain2DEditorView::Create_Shape(ETool_Type type)
{
	switch (type)
	{
	case ETool_Type::Tool_Line:
		return new CLine();
	case ETool_Type::Tool_Rect:
		return new CRectangle();
	case ETool_Type::Tool_Ellipse:
		return new CEllipse();
	default:
		return nullptr;
	}
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_Current_Tool == ETool_Type::Tool_None)
	{
		CView::OnLButtonDown(0, point);
		return;
	}

	m_Start_Point = point;
	m_Is_Drawing = true;

	m_pCurrent_Shape = Create_Shape(m_Current_Tool);

	if (m_pCurrent_Shape == nullptr)
	{
		m_Is_Drawing = false;
		return;
	}

	m_pCurrent_Shape->Set_Paint_Area(CRect(point, point));
	SetCapture(); // захват движения мыши
	m_Prev_Rect_Drawn = CRect(point, point);
	m_Prev_Rect_Drawn.NormalizeRect();
	m_Prev_Rect_Drawn.InflateRect(m_Stoke_Size, m_Stoke_Size);
	Invalidate();
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_Is_Drawing || !m_pCurrent_Shape)
		return;

	CLine* line = dynamic_cast<CLine*>(m_pCurrent_Shape);
	if (line != nullptr)
		line->Update_End_Point(point);
	else
		m_pCurrent_Shape->Set_Paint_Area(CRect(m_Start_Point, point));

	// Вычисляем область для частичной перерисовки
	CRect new_rect(m_Start_Point, point);
	new_rect.NormalizeRect();
	new_rect.InflateRect(m_Stoke_Size, m_Stoke_Size);

	// Область, которую нужно перерисовать — объединение старой и новой временной фигуры
	CRect old_rect = new_rect;
	if (!m_Prev_Rect_Drawn.IsRectEmpty())
		old_rect.UnionRect(old_rect, m_Prev_Rect_Drawn);

	m_Prev_Rect_Drawn = new_rect; // Обновляем предыдущую временную фигуру

	InvalidateRect(&old_rect, FALSE); // инвалидируем только нужную область (не стираем фон — FALSE)
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_Is_Drawing || !m_pCurrent_Shape)
		return;

	ReleaseCapture(); // освобождение захвата мыши
	
	CLine* line = dynamic_cast<CLine*>(m_pCurrent_Shape);
	if (line != nullptr)
		line->Update_End_Point(point);
	else
		m_pCurrent_Shape->Set_Paint_Area(CRect(m_Start_Point, point));

	// Вычисление финальной области для перерисовки (включая запас под абрис)
	CRect final_rect(m_Start_Point, point);
	final_rect.NormalizeRect();
	final_rect.InflateRect(m_Stoke_Size, m_Stoke_Size);

	// Объединяем всё
	CRect old_rect = final_rect;
	if (!m_Prev_Rect_Drawn.IsRectEmpty())
		old_rect.UnionRect(old_rect, m_Prev_Rect_Drawn);

	// добавляем в документ
	CPlain2DEditorDoc* pDoc = GetDocument();
	if (pDoc)
		pDoc->Add_Shape(m_pCurrent_Shape);

	m_pCurrent_Shape = nullptr;
	m_Is_Drawing = false;

	m_Prev_Rect_Drawn.SetRectEmpty(); // очистка
	InvalidateRect(&old_rect, FALSE);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Tool_Selected(ETool_Type tool_type)
{
	if (m_Current_Tool == tool_type)
		m_Current_Tool = ETool_Type::Tool_None;
	else
		m_Current_Tool = tool_type;
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Tool_Line()
{
	On_Tool_Selected(ETool_Type::Tool_Line);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Tool_Rectangle()
{
	On_Tool_Selected(ETool_Type::Tool_Rect);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Tool_Ellipse()
{
	On_Tool_Selected(ETool_Type::Tool_Ellipse);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Update_Tool(CCmdUI* pCmdUI, ETool_Type tool_type)
{
	pCmdUI->SetCheck(m_Current_Tool == tool_type);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Update_Tool_Line(CCmdUI* pCmdUI)
{
	On_Update_Tool(pCmdUI, ETool_Type::Tool_Line);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Update_Tool_Rectangle(CCmdUI* pCmdUI)
{
	On_Update_Tool(pCmdUI, ETool_Type::Tool_Rect);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorView::On_Update_Tool_Ellipse(CCmdUI* pCmdUI)
{
	On_Update_Tool(pCmdUI, ETool_Type::Tool_Ellipse);
}
//------------------------------------------------------------------------------------------------------------
