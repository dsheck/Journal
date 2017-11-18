/****************************************************************
 *					CJournalEntry Definition					*
 *						by: Don Sheck							*
 *																*
 *  Function: Describes the data structure and the operations	*
 *	which can be performed on the data contained within.		*
 ****************************************************************/

#pragma once

#include <iostream>

using namespace std;

class CJournalEntry
{
// OStream Operator
	friend ostream& operator<<( ostream&, const CJournalEntry& );

private:
	int m_nStartHour;
	int m_nStartMinute;
	int m_nStartSecond;
	int m_nStartDay;
	int m_nStartMonth;
	int m_nStartYear;
	int m_nProjectCode;
	int m_nTotalMinutes;
	bool m_bBillable;

	// Functions
	int getMaxDaysInMonth(int nMonth);
	bool isLeapYear(void);

public:
	CJournalEntry(void);
	~CJournalEntry(void);
	CJournalEntry::CJournalEntry(int nStartHour, int nStartMin, int nStartSec, int nStartMonth, int nStartDate, int nStartYear, int nNumMinutes, int nProjCode, bool bBillable);

	bool setTime(int nHour, int nMin, int nSec);
	bool setDate(int nDay, int nMonth, int nYear);
	bool setMinutes(int nNumMinutes);
	bool setProjectCode(int nCode);
	bool setBillable(bool bBillable);
	bool isBillable(void);
	int getTime(void);
	int getDate(void);
	int getProjectCode(void);
	int getMinutes(void);
	// Operator< used for sorting listings
	bool operator<(CJournalEntry&);
};
