// JournalView.h : interface of the CJournalView class
//


#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"


class CJournalView : public CFormView
{
protected: // create from serialization only
	CJournalView();
	DECLARE_DYNCREATE(CJournalView)

public:
	enum{ IDD = IDD_JOURNAL_FORM };

// Attributes
public:
	CJournalDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CJournalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	
private:
	int m_nProjCode;
	int m_nNumMinutes;
	BOOL m_bIsBillable;
	CDateTimeCtrl m_dtcTime;
	CMonthCalCtrl m_calDate;
	void updateDataMembers(void);
	void getDataMembers(void);

public:
	afx_msg void OnBnClickedAddnew();
	afx_msg void OnEnChangeEditProjcode();
	afx_msg void OnEnChangeEditTotalmins();
	afx_msg void OnBnClickedCheckBillable();
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeStarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedRemove();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
private:
	bool m_bFirstEntry;
public:
	// Greys out or displays controls based on m_bFirstEntry variable
	void toggleControls(void);
	afx_msg void OnBnClickedSearch();
	COleDateTime m_SearchDate;
private:
	int m_nSearchCode;
public:
	afx_msg void OnBnClickedSearchProjradio();
	afx_msg void OnBnClickedSearchDateradio();
	afx_msg void OnDtnDatetimechangeSearchdate(NMHDR *pNMHDR, LRESULT *pResult);
private:
	bool m_bSearchChanged;
public:
	afx_msg void OnBnClickedSort();
	afx_msg void OnBnClickedListcode();
	afx_msg void OnEnChangeSearchcode();
};

#ifndef _DEBUG  // debug version in JournalView.cpp
inline CJournalDoc* CJournalView::GetDocument() const
   { return reinterpret_cast<CJournalDoc*>(m_pDocument); }
#endif

