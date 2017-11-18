// JournalView.cpp : implementation of the CJournalView class
//

#include "stdafx.h"
#include "Journal.h"

#include "JournalDoc.h"
#include "JournalView.h"
#include ".\journalview.h"
#include "ListDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJournalView

IMPLEMENT_DYNCREATE(CJournalView, CFormView)

BEGIN_MESSAGE_MAP(CJournalView, CFormView)
	ON_BN_CLICKED(IDC_ADDNEW, OnBnClickedAddnew)
	ON_EN_CHANGE(IDC_EDIT_PROJCODE, OnEnChangeEditProjcode)
	ON_EN_CHANGE(IDC_EDIT_TOTALMINS, OnEnChangeEditTotalmins)
	ON_BN_CLICKED(IDC_CHECK_BILLABLE, OnBnClickedCheckBillable)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, OnMcnSelchangeMonthcalendar1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_STARTTIME, OnDtnDatetimechangeStarttime)
	ON_BN_CLICKED(IDC_NEXT, OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_REMOVE, OnBnClickedRemove)
	ON_BN_CLICKED(IDC_SEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_SEARCH_PROJRADIO, OnBnClickedSearchProjradio)
	ON_BN_CLICKED(IDC_SEARCH_DATERADIO, OnBnClickedSearchDateradio)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SEARCHDATE, OnDtnDatetimechangeSearchdate)
	ON_BN_CLICKED(IDC_SORT, OnBnClickedSort)
	ON_BN_CLICKED(IDC_LISTCODE, OnBnClickedListcode)
	ON_EN_CHANGE(IDC_SEARCHCODE, OnEnChangeSearchcode)
END_MESSAGE_MAP()

// CJournalView construction/destruction

CJournalView::CJournalView()
	: CFormView(CJournalView::IDD)
	, m_nProjCode(0)
	, m_nNumMinutes(0)
	, m_bIsBillable(FALSE)
	, m_bFirstEntry(true)
	, m_SearchDate(COleDateTime::GetCurrentTime())
	, m_nSearchCode(0)
	, m_bSearchChanged(false)
{
	// TODO: add construction code here
}

CJournalView::~CJournalView()
{
}

void CJournalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calDate);
	DDX_Text(pDX, IDC_EDIT_PROJCODE, m_nProjCode);
	DDX_Text(pDX, IDC_EDIT_TOTALMINS, m_nNumMinutes);
	DDX_Check(pDX, IDC_CHECK_BILLABLE, m_bIsBillable);
	DDX_Control(pDX, IDC_STARTTIME, m_dtcTime);
	DDX_DateTimeCtrl(pDX, IDC_SEARCHDATE, m_SearchDate);
	DDX_Text(pDX, IDC_SEARCHCODE, m_nSearchCode);
}

BOOL CJournalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CJournalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


// CJournalView diagnostics

#ifdef _DEBUG
void CJournalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CJournalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CJournalDoc* CJournalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJournalDoc)));
	return (CJournalDoc*)m_pDocument;
}
#endif //_DEBUG


// CJournalView message handlers

void CJournalView::OnBnClickedAddnew()
{
	UpdateData(true);
	CJournalDoc *pDoc = GetDocument();
	if( !m_bFirstEntry )
	{
		pDoc->addEntry();
	}
	else
	{
		pDoc->addEntry();
		m_bFirstEntry = false;
	}
	toggleControls();
	getDataMembers();
	updateDataMembers();
}

void CJournalView::OnEnChangeEditProjcode()
{
	updateDataMembers();
}

void CJournalView::updateDataMembers(void)
{
	// Pull Current Data from GUI
	UpdateData(true);

	// Set the Doc variables to the current values
	CJournalDoc *pDoc = GetDocument();
	toggleControls();

	// Update the Time
	CTime selectedTime;
	m_dtcTime.GetTime(selectedTime);
	pDoc->setTime(selectedTime.GetHour(), selectedTime.GetMinute(), selectedTime.GetSecond());

	// Update the Date
	m_calDate.GetCurSel(selectedTime);
	pDoc->setDate(selectedTime.GetDay(), selectedTime.GetMonth(), selectedTime.GetYear());

	// Update the Project Code
	pDoc->setProjCode(m_nProjCode);

	// Update the Number of Minutes
	pDoc->setNumMinutes(m_nNumMinutes);

	// Update whether its billable or not
	pDoc->setBillable(m_bIsBillable);
}

void CJournalView::OnEnChangeEditTotalmins()
{
	updateDataMembers();
}

void CJournalView::OnBnClickedCheckBillable()
{
	updateDataMembers();
}

void CJournalView::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	updateDataMembers();
}

void CJournalView::OnDtnDatetimechangeStarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	updateDataMembers();
}

void CJournalView::OnBnClickedNext()
{
	CJournalDoc *pDoc = GetDocument();
	pDoc->next();
	getDataMembers();
}

void CJournalView::getDataMembers(void)
{
	// Get the data members from the Doc and update the GUI
	CJournalDoc *pDoc = GetDocument();
	
	// Temporary time var
	int temp = pDoc->getTime();
	CString strTemp;
	
	// Adjust the Time
	int hour, min, sec;
	hour = temp / 10000;
	temp -= hour * 10000;
	min = temp / 100;
	temp -= min * 100;
	sec = temp;
	CTime *time = new CTime(2000, 1, 1, hour, min, sec);
	m_dtcTime.SetTime(time);
	
	// Adjust the Date
	delete time;
	temp = pDoc->getDate();
	int day, month, year;
	year = temp / 10000;
	temp -= year * 10000;
	month = temp / 100;
	temp -= month * 100;
	day = temp;
	time = new CTime(year, month, day, hour, min, sec);
	m_calDate.SetCurSel(*time);

	// Update Project Code
	m_nProjCode = pDoc->getProjCode();

	// Update Num Minutes
	m_nNumMinutes = pDoc->getNumMinutes();

	// Get Billable Info
	m_bIsBillable = pDoc->isBillable();

	// Redraw Info on Screen
	UpdateData(false);
}

void CJournalView::OnBnClickedPrevious()
{
	CJournalDoc *pDoc = GetDocument();
	if( !pDoc->atHead() )
	{
		pDoc->prev();
	}
	getDataMembers();
}

void CJournalView::OnBnClickedRemove()
{
	CJournalDoc *pDoc = GetDocument();
	pDoc->removeEntry();
	updateDataMembers();
}

void CJournalView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CJournalDoc *pDoc = GetDocument();
	// Set the first entry variable depending on list size
	if( pDoc->getSize() == 0 )
		m_bFirstEntry = true;
	else
		m_bFirstEntry = false;
	toggleControls();

	getDataMembers();
}

// Greys out or displays controls based on m_bFirstEntry variable
void CJournalView::toggleControls(void)
{
	CJournalDoc *pDoc = GetDocument();
	if( m_bFirstEntry )
	{
		// No Elements in the list
		GetDlgItem(IDC_EDIT_PROJCODE)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_TOTALMINS)->EnableWindow(false);
		GetDlgItem(IDC_CHECK_BILLABLE)->EnableWindow(false);
		GetDlgItem(IDC_STARTTIME)->EnableWindow(false);
		GetDlgItem(IDC_MONTHCALENDAR1)->EnableWindow(false);
		GetDlgItem(IDC_REMOVE)->EnableWindow(false);
		GetDlgItem(IDC_SEARCHDATE)->EnableWindow(false);
		GetDlgItem(IDC_SEARCHCODE)->EnableWindow(false);
		GetDlgItem(IDC_SORT)->EnableWindow(false);
		GetDlgItem(IDC_SEARCH)->EnableWindow(false);
		GetDlgItem(IDC_NEXT)->EnableWindow(false);
		GetDlgItem(IDC_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_LISTCODE)->EnableWindow(false);

		SendDlgItemMessage(IDC_SEARCH_DATERADIO, BM_SETCHECK, 1);
	}
	else
	{
		// There are Elements in the list
		GetDlgItem(IDC_EDIT_PROJCODE)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_TOTALMINS)->EnableWindow(true);
		GetDlgItem(IDC_CHECK_BILLABLE)->EnableWindow(true);
		GetDlgItem(IDC_STARTTIME)->EnableWindow(true);
		GetDlgItem(IDC_MONTHCALENDAR1)->EnableWindow(true);
		GetDlgItem(IDC_REMOVE)->EnableWindow(true);
		GetDlgItem(IDC_SEARCHDATE)->EnableWindow(true);
		GetDlgItem(IDC_SORT)->EnableWindow(true);
		GetDlgItem(IDC_SEARCH)->EnableWindow(true);
		GetDlgItem(IDC_NEXT)->EnableWindow(true);
		GetDlgItem(IDC_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_LISTCODE)->EnableWindow(true);

		// Manage the radio buttons
		int checked = GetCheckedRadioButton(IDC_SEARCH_DATERADIO, IDC_SEARCH_PROJRADIO);
		if( checked == IDC_SEARCH_DATERADIO )
		{
			GetDlgItem(IDC_SEARCHDATE)->EnableWindow(true);
			GetDlgItem(IDC_SEARCHCODE)->EnableWindow(false);
		}
		else
		{
			GetDlgItem(IDC_SEARCHDATE)->EnableWindow(false);
			GetDlgItem(IDC_SEARCHCODE)->EnableWindow(true);
		}
	}
}

void CJournalView::OnBnClickedSearch()
{
	UpdateData(true);
	int nSearchVal, checked = GetCheckedRadioButton(IDC_SEARCH_DATERADIO, IDC_SEARCH_PROJRADIO);
	CJournalDoc *pDoc = GetDocument();
	bool found;

	// Do the appropriate search call based on which radio button is selected
	if( checked == IDC_SEARCH_DATERADIO )
	{
		nSearchVal = m_SearchDate.GetDay();
		nSearchVal += m_SearchDate.GetMonth() * 100;
		nSearchVal += m_SearchDate.GetYear() * 10000;
		found = pDoc->searchDate(nSearchVal, m_bSearchChanged);
	}
	else
	{
		found = pDoc->searchCode(m_nSearchCode, m_bSearchChanged);
	}

	// Set the search to not be 'old'
	m_bSearchChanged = false;
	// if no result was found, alert user
	if( !found )
	{
		AfxMessageBox("Search did not find any entries with that criteria");
	}
}

void CJournalView::OnBnClickedSearchProjradio()
{
	// If the search project button is clicked, reset the m_bSearchChanged variable and 
	// toggle the controls.
	m_bSearchChanged = true;
	toggleControls();
}

void CJournalView::OnBnClickedSearchDateradio()
{
	// If the search date button is clicked, reset the m_bSearchChanged variable and 
	// toggle the controls.
	m_bSearchChanged = true;
	toggleControls();
}

void CJournalView::OnDtnDatetimechangeSearchdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// When the date is changed, reset the 'ischanged' variable
	m_bSearchChanged = true;
}

void CJournalView::OnBnClickedSort()
{
	// Sort the document's list
	CJournalDoc *pDoc = GetDocument();
	pDoc->sort(); 
}

void CJournalView::OnBnClickedListcode()
{
	// Set up and fire the Listing Dialog
	CListDialog myDialog;
	myDialog.setDocument( (CJournalDoc*) GetDocument() );
	myDialog.DoModal();
}

void CJournalView::OnEnChangeSearchcode()
{
	// When search code is changed, reset the m_bSearchChanged variable
	m_bSearchChanged = true;
}
