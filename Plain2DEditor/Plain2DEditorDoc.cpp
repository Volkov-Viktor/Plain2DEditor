
// Plain2DEditorDoc.cpp — реализация класса CPlain2DEditorDoc (модель данных документа)
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
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlain2DEditorDoc
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CPlain2DEditorDoc, CDocument) // регистрация класса для динамического создания (MFC)
BEGIN_MESSAGE_MAP(CPlain2DEditorDoc, CDocument)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorDoc::~CPlain2DEditorDoc()
{
}
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorDoc::CPlain2DEditorDoc() noexcept
{
	// TODO: добавьте код однократной инициализации здесь
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::Add_Shape(CShape* shape)
{
	if (!shape)
		return;

	m_Shapes.Add(shape);
	SetModifiedFlag(TRUE);
	UpdateAllViews(nullptr);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::Clear_All_Shapes() 
{
	for (int i = 0; i < m_Shapes.GetSize(); ++i)
		delete m_Shapes[i];

	m_Shapes.RemoveAll();
	SetModifiedFlag(TRUE);
	UpdateAllViews(nullptr);
}
//------------------------------------------------------------------------------------------------------------
bool CPlain2DEditorDoc::Undo_Last()
{
	int i = m_Shapes.GetSize();

	if (i == 0)
		return false;

	delete m_Shapes[i - 1];
	m_Shapes.RemoveAt(i - 1);

	SetModifiedFlag(TRUE);
	UpdateAllViews(nullptr);

	return true;
}
//------------------------------------------------------------------------------------------------------------
BOOL CPlain2DEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) // вызов реализации базового класса
		return FALSE;

	// TODO: добавьте код повторной инициализации здесь
	// (в SDI‑приложениях документ может переиспользоваться)

	return TRUE;
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())  // Режим сохранения документа
	{
		// TODO: добавьте код сохранения данных документа здесь
		// Например: запись геометрических объектов, настроек и т. д.
	}
	else  // Режим загрузки документа
	{
		// TODO: добавьте код загрузки данных документа здесь
		// Например: чтение и восстановление объектов из файла
	}
}
//------------------------------------------------------------------------------------------------------------
#ifdef SHARED_HANDLERS
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{ // Поддержка создания миниатюр для проводника Windows
	// Заливаем область миниатюры цветом
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: реализовать отрисовку миниатюры здесь");
	LOGFONT lf;

	// Получаем параметры системного шрифта по умолчанию
	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36; // Устанавливаем размер шрифта

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf); // Создаём шрифт для отрисовки

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::InitializeSearchContent()
{ // Инициализация содержимого для поиска (поддержка Windows Search)
	CString strSearchContent;
	// Формируем содержимое для поиска на основе данных документа
	// Части содержимого разделяются символом ";"
	// Пример: strSearchContent = _T("точка;прямоугольник;окружность;OLE‑объект;");
	SetSearchContent(strSearchContent);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::SetSearchContent(const CString& value)
{ // Установка содержимого для поиска
	if (value.IsEmpty())
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid); // удаление данных поиска, если строка пуста
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT); // устанавливаем текстовое значение для поиска
			SetChunkValue(pChunk); // сохраняем данные поиска
		}
	}
}
//------------------------------------------------------------------------------------------------------------
#endif // SHARED_HANDLERS
//------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CPlain2DEditorDoc::AssertValid() const
{
	CDocument::AssertValid(); // Проверяем корректность состояния базового класса
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc); // Выводим отладочную информацию о состоянии документа
}
//------------------------------------------------------------------------------------------------------------
#endif //_DEBUG
