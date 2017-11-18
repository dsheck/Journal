/****************************************************************
 *					CJournalEntry Implementation				*
 *						by: Don Sheck							*
 *																*
 *  Function: Keeps track of all data associated with a Journal *
 *	entry and allows modifications of this data in a data		*
 *	protecting way by varifying input.							*
 ****************************************************************/

#include "StdAfx.h"
#include ".\journalentry.h"

CJournalEntry::CJournalEntry(void)
: m_nStartHour(1)
, m_nStartMinute(0)
, m_nStartSecond(0)
, m_nStartDay(1)
, m_nStartMonth(1)
, m_nStartYear(1970)
, m_nProjectCode(0)
, m_nTotalMinutes(0)
, m_bBillable(false)
{
}

CJournalEntry::~CJournalEntry(void)
{
}

/********************************************************************
 *			Overloaded CJournaEntry Constructor						*
 *																	*
 *  Description: Allows a CJournalEntry Object to be constructed	*
 *	with specific or default data.									*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 *	10/16/2003	Don Sheck		Changed data assign method to use	*
 *								provided member functions.			*
 ********************************************************************/

CJournalEntry::CJournalEntry(int nStartHour = 1, int nStartMin = 0, int nStartSec = 0, int nStartMonth = 1, int nStartDate = 1, int nStartYear = 1970, int nNumMinutes = 0, int nProjCode = 0, bool bBillable = false)
{
	// Check Time Variables and then set it if it is correct, set to default if it is not
	setTime(nStartHour, nStartMin, nStartSec);

	// Check Month Variables, and set if it is correct, default if it is not
	setDate(nStartDate, nStartMonth, nStartYear);

	// Negative minutes are an illegal number of minutes
	setMinutes(nNumMinutes);

	// No Negative Project Codes
	setProjectCode(nProjCode);

	m_bBillable = bBillable;
}

/********************************************************************
 *			Overloaded OStream << Operator							*
 *																	*
 *  Description: Used to test the class in a console enviroment.	*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

ostream& operator<<( ostream& os, const CJournalEntry& theJournal)
{
	os << "Project Code: " << theJournal.m_nProjectCode << endl;
	os << "Start Date: " << theJournal.m_nStartDay << "/" << theJournal.m_nStartMonth << "/" << theJournal.m_nStartYear << endl;
	os << "Start Time: " << theJournal.m_nStartHour << ":" << theJournal.m_nStartMinute << ":" << theJournal.m_nStartSecond << endl;
	os << "Total Time Spent on Project: " << theJournal.m_nTotalMinutes << endl;
	os << "Billable to client: " << (theJournal.m_bBillable ? "Yes" : "No") << endl;
	
	return os;
}

/********************************************************************
 *			getMaxDaysInMonth Utility Function						*
 *																	*
 *  Description: Returns the number of allowable days in a given 	*
 *	month with help from the isLeapYear function.					*
 *																	*
 *	IN: nMonth is the month we are getting the number of days for	*
 *	OUT: Returns the number of days in nMonth						*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/15/2003	Don Sheck		Original specification				*
 ********************************************************************/

int CJournalEntry::getMaxDaysInMonth(int nMonth)
{
	switch(nMonth) {
		// February
		case 2: if( isLeapYear() )
					return 29;
				else
					return 28;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
		default: return 31;
	}
}

/********************************************************************
 *			isLeapYear Utility Function								*
 *																	*
 *  Description: Calculates whether the m_nStartYear variable is a 	*
 *	leap year or not.												*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns true if m_nStartYear is a leap year, false if it	*
 *		is not.														*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/15/2003	Don Sheck		Original specification				*
 ********************************************************************/

bool CJournalEntry::isLeapYear(void)
{
	if( (m_nStartYear % 4) == 0 && ( (m_nStartYear % 100) != 0 || (m_nStartYear % 400) == 0 ) )
	{
		// is a leap year
		return true;
	}
	else
	{
		// is not a leap year
		return false;
	}
}

/********************************************************************
 *			setTime Function										*
 *																	*
 *  Description: Sets the CJournalEntry object's time to the given 	*
 *	hour, minute and second.										*
 *																	*
 *	IN: nHour is the hour, nMin is the minute and nSec is the second*
 *		we are setting the object to.								*
 *	OUT: Returns true												*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 *	10/15/2003	Don Sheck		Added some further verification		*
 ********************************************************************/

bool CJournalEntry::setTime(int nHour, int nMin, int nSec)
{
	if( nHour >= 0 && nHour < 24 )
		m_nStartHour = nHour;
	else
		m_nStartHour = 1;

	if( nMin >= 0 && nMin < 60 )
		m_nStartMinute = nMin;
	else
		m_nStartMinute = 0;

	if( nSec >= 0 && nSec < 60 )
		m_nStartSecond = nSec;
	else
		m_nStartSecond = 0;

	return true;
}

/********************************************************************
 *			setDate Function										*
 *																	*
 *  Description: Sets the CJournalEntry object's date to the given 	*
 *	year, month and day.											*
 *																	*
 *	IN: nDay is the day, nMonth is the month and nYear is the year	*
 *		we are setting the object to.								*
 *	OUT: Returns true												*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 *	10/15/2003	Don Sheck		Fixed verification bug by adding	*
 *								getMaxDaysInMonth function.			*
 ********************************************************************/

bool CJournalEntry::setDate(int nDay, int nMonth, int nYear)
{
	if( nYear >= 0 )
		m_nStartYear = nYear;
	else
		m_nStartYear = 1970;

	if( nMonth >= 1 && nMonth <= 12 )
		m_nStartMonth = nMonth;
	else
		m_nStartMonth = 1;

	int nMaxDaysInMonth = getMaxDaysInMonth(m_nStartMonth);
	if( nDay >= 1 && nDay <= nMaxDaysInMonth )
		m_nStartDay = nDay;
	else
		m_nStartDay = 1;

	return true;
}

/********************************************************************
 *			setMinutes Function										*
 *																	*
 *  Description: Sets the CJournalEntry object's total minutes  	*
 *	worked on the project to the given number of minutes.			*
 *																	*
 *	IN: nNumMinutes is the number of minutes to set m_nTotalMinutes *
 *	OUT: Returns true												*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

bool CJournalEntry::setMinutes(int nNumMinutes)
{
	if( nNumMinutes >= 0 )
		m_nTotalMinutes = nNumMinutes;
	else
		m_nTotalMinutes = 0;
	return true;
}

/********************************************************************
 *			setProjectCode Function									*
 *																	*
 *  Description: Sets the CJournalEntry object's project code to  	*
 *	the given code.													*
 *																	*
 *	IN: nCode is the value to set m_nProjectCode to.				*
 *	OUT: Returns true												*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

bool CJournalEntry::setProjectCode(int nCode)
{
	if( nCode >= 0 )
		m_nProjectCode = nCode;
	else
		m_nProjectCode = 0;

	return true;
}

/********************************************************************
 *			setBillable Function									*
 *																	*
 *  Description: Sets the CJournalEntry object's billable boolean	*
 *	variable.														*
 *																	*
 *	IN: bBillable is the value to set m_bBillable to.				*
 *	OUT: Returns true												*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

bool CJournalEntry::setBillable(bool bBillable)
{
	m_bBillable = bBillable;
	return true;
}

/********************************************************************
 *			isBillable Function										*
 *																	*
 *  Description: Informs the caller of whether the object is 		*
 *	billable to the client or not.									*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns the value of m_bBillable							*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

bool CJournalEntry::isBillable(void)
{
	return m_bBillable;
}

/********************************************************************
 *			getTime Function										*
 *																	*
 *  Description: Returns the value of the currently saved time as	*
 *	a single integer.												*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns the time as a single integer in the form HHMMSS	*
 *	Where HH is the hour, MM is the minute and SS are the seconds	*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

int CJournalEntry::getTime(void)
{
	// HHMMSS
	return (m_nStartHour * 10000) + (m_nStartMinute * 100) + m_nStartSecond;
}

/********************************************************************
 *			getDate Function										*
 *																	*
 *  Description: Returns the value of the object's stored date as	*
 *	a single integer.												*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns the date as an integer in the form YYYYMMDD, where	*
 *	YYYY is the year, MM is the month and DD is the day.			*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

int CJournalEntry::getDate(void)
{
	// YYYYMMDD
	return (m_nStartYear * 10000) + (m_nStartMonth * 100) + m_nStartDay;
}

/********************************************************************
 *			getProjectCode Function									*
 *																	*
 *  Description: Returns the value of the project code				*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns m_nProjectCode										*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

int CJournalEntry::getProjectCode(void)
{
	return m_nProjectCode;
}

/********************************************************************
 *			getMinutes Function										*
 *																	*
 *  Description: Returns the value of m_nTotalMinutes				*
 *																	*
 *	IN: N/A															*
 *	OUT: Returns m_nTotalMinutes									*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/14/2003	Don Sheck		Original specification				*
 ********************************************************************/

int CJournalEntry::getMinutes(void)
{
	return m_nTotalMinutes;
}

/********************************************************************
 *			Overloaded Operator < Function							*
 *																	*
 *  Description: This function will return true if the right hand	*
 *	CJournalEntry object in a less than operation (ie: c1 < c2) is	*
 *	greater in date and time than the current object				*
 *																	*
 *	IN: A reference to the right hand operand of a < operator.		*
 *	OUT: Returns true if the current object is greater than the in	*
 *	reference.														*
 *																	*
 *	History:														*
 *	Date		Author			Notes								*
 *	--------------------------------------------------------------	*
 *	10/16/2003	Don Sheck		Original specification				*
 *	10/15/2003	Don Sheck		Logic fixes to return the correct	*
 *								result when the operator is called	*
 ********************************************************************/

bool CJournalEntry::operator<(CJournalEntry &in)
{
	bool bLessTime = false, bLessDate = false;
	// Compare time
	if( getTime() > in.getTime() )
		bLessTime = true;
	if( getDate() > in.getDate() )
		bLessDate = true;

	if( bLessDate || ( bLessDate && bLessTime ) || ( bLessTime && (getDate() == in.getDate()) ) )
		return true;
	else
	{
		return false;
	}
}