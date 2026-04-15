#include "pch.h"
#include "Plain2DEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlain2DEditorDoc
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CPlain2DEditorDoc, CDocument) // регистрация класса для динамического создания (MFC)
BEGIN_MESSAGE_MAP(CPlain2DEditorDoc, CDocument)
ON_COMMAND(ID_CLEAR_ALL, &CPlain2DEditorDoc::Clear_All_Shapes)
ON_COMMAND(ID_EDIT_UNDO, &CPlain2DEditorDoc::On_Edit_Undo)
ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CPlain2DEditorDoc::On_Update_Edit_Undo)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorDoc::~CPlain2DEditorDoc()
{
	for (int i = 0; i < m_Shapes.GetSize(); ++i)
		delete m_Shapes[i];
	m_Shapes.RemoveAll();
}
//------------------------------------------------------------------------------------------------------------
CPlain2DEditorDoc::CPlain2DEditorDoc() noexcept
{
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
	int i = (int)m_Shapes.GetSize();

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
	m_Shapes.Serialize(ar);
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::DeleteContents()
{ // Вызывается MFC перед File > New, File > Open, закрытием документа
	for (int i = 0; i < m_Shapes.GetSize(); ++i)
		delete m_Shapes[i];
	m_Shapes.RemoveAll();

	CDocument::DeleteContents();
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::On_Edit_Undo()
{
	Undo_Last();
}
//------------------------------------------------------------------------------------------------------------
void CPlain2DEditorDoc::On_Update_Edit_Undo(CCmdUI* pCmdUI)
{ // Активна только если есть фигуры для отмены
	pCmdUI->Enable(m_Shapes.GetSize() > 0);
}
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
