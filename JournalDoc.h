// JournalDoc.h : interface of the CJournalDoc class
//

// include Journal Entry and List
#include "JournalEntry.h"
#include <list>
#include <iterator>

#pragma once

class CJournalDoc : public CDocument
{
protected: // create from serialization only
	CJournalDoc();
	DECLARE_DYNCREATE(CJournalDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CJournalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	list<CJournalEntry> m_EntryList;
	list<CJournalEntry>::iterator m_itCurrentPosition;
public:
	void setTime(int nHour, int nMin, int nSec);
	void addEntry(void);
	bool next(void);
	int getTime(void);
	bool prev(void);
	void setDate(int nDay, int nMonth, int nYear);
	int getDate(void);
	void setProjCode(int nCode);
	int getProjCode(void);
	void setNumMinutes(int nMinutes);
	int getNumMinutes(void);
	void setBillable(BOOL bBillable);
	bool isBillable(void);
	void removeEntry(void);
private:
	int m_nSize;
public:
	int getSize(void);
	void setSize(int nSize);
	bool atTail(void);
	bool atHead(void);
	bool searchDate(int nSearchVal, bool bNewSearch);
	bool searchCode(int nSearchVal, bool bNewSearch);
	void sort(void);
	CString addToList(int nCode);
};


