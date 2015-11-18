#include "stdafx.h"
#include "SlotReader.h"

CSlotReader::~CSlotReader(void)
{
}

CSlotReader::CSlotReader(HANDLE &hSlot,LPTSTR lpszSlotName) : CMailslot(hSlot,lpszSlotName)
{
}

bool CSlotReader::Connect()
{
	//	Close any existing mail slot
	//Disconnect();
	//	Now open the mail slot for overlapped I/O
	m_hEvent = ::CreateEvent( NULL, FALSE, FALSE, TEXT("ExampleSlot"));
	if(NULL ==m_hEvent) return FALSE;
	m_overlapped.Offset = 0;
	m_overlapped.OffsetHigh = 0;
	m_overlapped.hEvent = m_hEvent;
}

bool CSlotReader::Read(void)
{
	DWORD cbMessage, cMessage, cbRead;
	BOOL fResult;
	LPTSTR lpszBuffer;
	TCHAR achID[80];
	DWORD cAllMessages;
	cbMessage = cMessage = cbRead = 0;
	
	fResult = GetMailslotInfo( m_hMailSlot, (LPDWORD) NULL, &cbMessage, &cMessage,(LPDWORD) NULL);

	if(!fResult)
	{
		printf("GetMailslotInfo failed with %d. \n", GetLastError());
		return FALSE;
	}

	if(cbMessage == MAILSLOT_NO_MESSAGE)
	{
		printf("Waiting for a message...\n");
		return TRUE;
	}

	cAllMessages = cMessage;

	while (cMessage != 0)
	{
		::StringCchPrintf((LPTSTR) achID,80,TEXT("\nMessage #%d of %d \n"), cAllMessages - cMessage +1, cAllMessages);

		lpszBuffer = (LPTSTR) GlobalAlloc(GPTR,lstrlen((LPTSTR) achID)*sizeof(TCHAR) + cbMessage);

		if(NULL == lpszBuffer) return FALSE;
		lpszBuffer[0] = '\0';

		fResult = ::ReadFile(m_hMailSlot,lpszBuffer,cbMessage,&cbRead,&m_overlapped);

		if(!fResult)
		{
			printf("ReadFile failed with %d. \n", GetLastError());
			::GlobalFree((HGLOBAL) lpszBuffer);
			return FALSE;
		}

		::StringCbCat(lpszBuffer, lstrlen((LPTSTR) achID)*sizeof(TCHAR) + cbMessage,(LPTSTR) achID);

		// Mostrar el Mensaje

		_tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);

		::GlobalFree((HGLOBAL) lpszBuffer);

		fResult = GetMailslotInfo(m_hMailSlot,(LPDWORD) NULL, &cbMessage, &cMessage,(LPDWORD) NULL);

		if(!fResult)
		{
			printf("GetMailslotInfo failed (%d)\n", GetLastError());
			return FALSE;
		}
	}
	CloseHandle(m_hEvent);
	return TRUE;
}