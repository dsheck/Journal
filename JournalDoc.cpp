// JournalDoc.cpp : implementation of the CJournalDoc class
//

#include "stdafx.h"
#include "Journal.h"

#include "JournalDoc.h"
#include ".\journaldoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJournalDoc

IMPLEMENT_DYNCREATE(CJournalDoc, CDocument)

BEGIN_MESSAGE_MAP(CJournalDoc, CDocument)
END_MESSAGE_MAP()


// CJournalDoc construction/destruction

CJournalDoc::CJournalDoc()
: m_nSize(0)
{
	// TODO: add one-time construction code here

}

CJournalDoc::~CJournalDoc()
{
}

BOOL CJournalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_EntryList.clear();
	m_itCurrentPosition = m_EntryList.end();
	(*m_itCurrentPosition).setBillable(false);
	(*m_itCurrentPosition).setMinutes(0);
	(*m_itCurrentPosition).setProjectCode(0);
	CTime time = CTime::GetCurrentTime();
	(*m_itCurrentPosition).setTime(time.GetHour(), time.GetMinute(), time.GetSecond());
	(*m_itCurrentPosition).setDate(time.GetDay(), time.GetMonth(), time.GetYear());

	m_nSize = static_cast<int>(m_EntryList.size());

	return TRUE;
}




// CJournalDoc serialization

void CJournalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// add storing code here
		list<CJournalEntry>::iterator out = m_EntryList.begin();
		CString test;
		// Write the num elements to file
		ar.Write(&m_nSize, sizeof(int));

		// Write each list item to file
		while( out != m_EntryList.end() )
		{
			CJournalEntry temp = *out;
			ar.Write(&temp, sizeof(CJournalEntry));
			out++;
		}
		CJournalEntry temp = *out;
		ar.Write(&temp, sizeof(CJournalEntry));
		UpdateAllViews(NULL);
	}
	else
	{
		// add loading code here
		ar.Read(&m_nSize, sizeof(int));
		m_EntryList.clear();
		CJournalEntry *temp;

		// For each entry, read it and drop it into the list
		for(int i = 0; i < m_nSize; i++)
		{
			temp = new CJournalEntry();
			ar.Read(temp, sizeof(CJournalEntry));
			m_EntryList.push_back(*temp);
		}

		m_itCurrentPosition = m_EntryList.end();
		m_itCurrentPosition--;
		m_nSize = (int)m_EntryList.size();
		UpdateAllViews(NULL);
	}
}


// CJournalDoc diagnostics

#ifdef _DEBUG
void CJournalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJournalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CJournalDoc commands

void CJournalDoc::setTime(int nHour, int nMin, int nSec)
{
	(*m_itCurrentPosition).setTime(nHour, nMin, nSec);
}

void CJournalDoc::addEntry(void)
{
	CTime time = CTime::GetCurrentTime();
	
	// Set the current position to the end of the list
	m_itCurrentPosition = m_EntryList.begin();
	
	// Create a default entry and insert it into the list
	CJournalEntry temp(time.GetHour(), time.GetMinute(), time.GetSecond(), time.GetMonth(),
		time.GetDay(), time.GetYear(), 0, 0, false);
	m_EntryList.insert(m_itCurrentPosition, temp);
	
	// Back up to the newly insert position
	m_itCurrentPosition--;

	m_nSize++;

	SetModifiedFlag(true);
	UpdateAllViews(NULL);
}

bool CJournalDoc::next(void)
{
	if(m_itCurrentPosition != m_EntryList.begin() )
	{
		m_itCurrentPosition--;
		return true;
	}
	else
		return false;
}

int CJournalDoc::getTime(void)
{
	return (*m_itCurrentPosition).getTime();
}

bool CJournalDoc::prev(void)
{
	// Don't let the user go to the "End", which is a pointer to a position beyond the last
	// element in the list. Go to the one before the "End"
	//list<CJournalEntry>::iterator begin;
	//begin = m_EntryList.end();
	//begin--;
	if( m_itCurrentPosition != m_EntryList.end() )
	{
		m_itCurrentPosition++;
		return true;
	}
	else
	{
		return false;
	}
}

void CJournalDoc::setDate(int nDay, int nMonth, int nYear)
{
	(*m_itCurrentPosition).setDate(nDay, nMonth, nYear);
	SetModifiedFlag(true);
}

int CJournalDoc::getDate(void)
{
	return (*m_itCurrentPosition).getDate();
}

void CJournalDoc::setProjCode(int nCode)
{
	(*m_itCurrentPosition).setProjectCode(nCode);
	SetModifiedFlag(true);
}

int CJournalDoc::getProjCode(void)
{
	return (*m_itCurrentPosition).getProjectCode();
}

void CJournalDoc::setNumMinutes(int nMinutes)
{
	(*m_itCurrentPosition).setMinutes(nMinutes);
	SetModifiedFlag(true);
}

int CJournalDoc::getNumMinutes(void)
{
	return (*m_itCurrentPosition).getMinutes();
}

void CJournalDoc::setBillable(BOOL bBillable)
{
	// Remove Compiler Warning by using bool values for setBillable instead of BOOL
	if(bBillable == 0)
		(*m_itCurrentPosition).setBillable(false);
	else
		(*m_itCurrentPosition).setBillable(true);
	SetModifiedFlag(true);
	UpdateAllViews(NULL);
}

bool CJournalDoc::isBillable(void)
{
	return (*m_itCurrentPosition).isBillable();
}

void CJournalDoc::removeEntry(void)
{
	m_EntryList.erase(m_itCurrentPosition);
	m_itCurrentPosition = m_EntryList.end();
	m_itCurrentPosition--;
		
	m_nSize = static_cast<int>(m_EntryList.size());

	SetModifiedFlag(true);
	UpdateAllViews(NULL);
}

int CJournalDoc::getSize(void)
{
	return m_nSize;
}

void CJournalDoc::setSize(int nSize)
{
	m_nSize = nSize;
}

bool CJournalDoc::atTail(void)
{
	if( m_itCurrentPosition == m_EntryList.begin() )
		return true;
	else
		return false;
}

bool CJournalDoc::atHead(void)
{
	list<CJournalEntry>::iterator lastElement = m_EntryList.end();
	lastElement--;
	if( m_itCurrentPosition == lastElement )
		return true;
	else
		return false;
}

bool CJournalDoc::searchDate(int nSearchVal, bool bNewSearch)
{
	if( nSearchVal < 0 )
		return false;

	list<CJournalEntry>::iterator itSearchLoc;
	if( bNewSearch )
	{
		itSearchLoc = m_EntryList.end();
		itSearchLoc--;
	}
	else
		itSearchLoc = --m_itCurrentPosition;

	// Date
	while( itSearchLoc != m_EntryList.end() )
	{
		if( (*itSearchLoc).getDate() == nSearchVal )
		{
			m_itCurrentPosition = itSearchLoc;
			UpdateAllViews(NULL);
			return true;
		}
		itSearchLoc--;
	}

	return false;
}

bool CJournalDoc::searchCode(int nSearchVal, bool bNewSearch)
{
	if( nSearchVal < 0 )
		return false;

	list<CJournalEntry>::iterator itSearchLoc;
	if( bNewSearch )
	{
		itSearchLoc = m_EntryList.end();
		itSearchLoc--;
	}
	else
		itSearchLoc = --m_itCurrentPosition;

	// Project Code
	while( itSearchLoc != m_EntryList.end() )
	{
		if( (*itSearchLoc).getProjectCode() == nSearchVal )
		{
			m_itCurrentPosition = itSearchLoc;
			UpdateAllViews(NULL);
			return true;
		}
		itSearchLoc--;
	}

	return false;
}

void CJournalDoc::sort(void)
{
	// Create a temporary list
	m_EntryList.sort();
	m_itCurrentPosition = m_EntryList.end();
	m_itCurrentPosition--;
	UpdateAllViews(NULL);
}

CString CJournalDoc::addToList(int nCode)
{
	list<CJournalEntry>::iterator itList = m_EntryList.end();
	itList--;
	CString listItem("");
	
	while( itList != m_EntryList.end() )
	{
		if( itList->getProjectCode() == nCode )
		{
			// Found it!
			CString itemString, temp;
			int param1, param2, val;
			
			// Format the time:
			val = itList->getTime();
			param1 = val / 10000;
			val -= param1 * 10000;
			param2 = val / 100;
			val -= param2 * 100;
			temp.Format("%d:%d:%d", param1, param2, val);
			
			// Format the date:
			val = itList->getDate();
			param1 = val / 10000;
			val -= param1 * 10000;
			param2 = val / 100;
			val -= param2 * 100;

			itemString.Format("%s, %d/%d/%d - Total Minutes: %d [%s]\n", temp, val, param2, param1, 
				itList->getMinutes(), (itList->isBillable() ? "Billable" : "Not Billable") );
			listItem.Append(itemString);
		}
		itList--;
	}

	return listItem;
}
