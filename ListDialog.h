#pragma once
#include "afxwin.h"

#include "JournalDoc.h"


// CListDialog dialog

class CListDialog : public CDialog
{
	DECLARE_DYNCREATE(CListDialog)

public:
	CListDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListDialog();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_LISTDIALOG, IDH = IDR_HTML_LISTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	int m_nCode;
public:
	afx_msg void OnBnClickedSubmit();
	CJournalDoc* m_pDocument;
	void setDocument(CJournalDoc* pDoc);
	//CString m_ListString;
	CListBox m_ListBox;
};
