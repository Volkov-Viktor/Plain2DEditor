
// Plain2DEditorDoc.h : interface of the CPlain2DEditorDoc class

#pragma once

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
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

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
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
//------------------------------------------------------------------------------------------------------------
