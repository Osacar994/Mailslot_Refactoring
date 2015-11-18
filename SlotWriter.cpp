#include "stdafx.h"
#include "SlotWriter.h"


CSlotWriter::CSlotWriter(HANDLE &hSlot,LPTSTR lpszSlotName) : CMailslot(hSlot,lpszSlotName)
{
}


CSlotWriter::~CSlotWriter(void)
{
}

void CSlotWriter::Write(LPTSTR lpszMessage)
{
	BOOL fResult;
	DWORD cdWritten;
	
	fResult = WriteFile(m_hMailSlot,lpszMessage,(DWORD)(lstrlen(lpszMessage)+1)*sizeof(TCHAR),&cdWritten,(LPOVERLAPPED) NULL);

	if(!fResult)
	{
		printf("WriteFile failed with %d. \n", GetLastError());
	}
	else
	{
		printf("Slot written to successfully. \n");
	}
}

bool CSlotWriter::Connect()
{
	//	Close any existing mail slot
	//Disconnect();
	//	Now open the mail slot for overlapped I/O
	m_hMailSlot = CreateFile(m_pszSlotname,GENERIC_WRITE,FILE_SHARE_READ,(LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL);
	if (m_hMailSlot != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}
