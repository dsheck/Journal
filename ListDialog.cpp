// ListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Journal.h"
#include "ListDialog.h"
#include ".\listdialog.h"
#include "JournalEntry.h"
#include <list>
#include <iterator>



// CListDialog dialog

IMPLEMENT_DYNCREATE(CListDialog, CDHtmlDialog)

CListDialog::CListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CListDialog::IDD)
	, m_nCode(0)
	, m_pDocument(NULL)
{
}

CListDialog::~CListDialog()
{
}

void CListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nCode);
	DDX_Control(pDX, IDC_ENTRYLIST, m_ListBox);
}

BOOL CListDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CListDialog, CDialog)
	ON_BN_CLICKED(IDC_SUBMIT, OnBnClickedSubmit)
END_MESSAGE_MAP()


// CListDialog message handlers

HRESULT CListDialog::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // return TRUE  unless you set the focus to a control
}

HRESULT CListDialog::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // return TRUE  unless you set the focus to a control
}

void CListDialog::OnBnClickedSubmit()
{
	UpdateData(true);

	m_ListBox.ResetContent();

	// Get the list of items
	CString test;
	test = m_pDocument->addToList(m_nCode);
	
	if( test != "" )
	{
		int iCurrPos= 0;

		while( -1 != ( iCurrPos = test.FindOneOf("\n") ) )
		{
			// Go through the list and add the strings before each \n to the listbox
			m_ListBox.AddString(test.Left( iCurrPos ));
			test = test.Right( test.GetLength() - iCurrPos - 1 );
		}
		if ( test.GetLength() > 0 )
		{
			// the last one
			m_ListBox.AddString(test);
		}
	}
	else
	{
		AfxMessageBox("No Entries were found with that Project Code");
	}
	
	// Refresh the dialog
	UpdateData(false);
}

void CListDialog::setDocument(CJournalDoc* pDoc)
{
	m_pDocument = pDoc;
}
