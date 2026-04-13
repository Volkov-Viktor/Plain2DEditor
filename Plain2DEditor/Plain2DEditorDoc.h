#pragma once

#include "Resource.h"
#include "Shape.h"

//------------------------------------------------------------------------------------------------------------
class CPlain2DEditorDoc : public CDocument
{
protected: // create from serialization only
	CPlain2DEditorDoc() noexcept;
	DECLARE_DYNCREATE(CPlain2DEditorDoc)

// Attributes
public:
	CObArray m_Shapes;
// Operations
public:
	void Add_Shape(CShape* shape);
	void Clear_All_Shapes();
	bool Undo_Last();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();

// Implementation
public:
	virtual ~CPlain2DEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void On_Edit_Undo();
	afx_msg void On_Update_Edit_Undo(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
//------------------------------------------------------------------------------------------------------------
