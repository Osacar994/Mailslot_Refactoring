#include "stdafx.h"
#include "Mailslot.h"

CMailslot::~CMailslot(void)
{
	Disconnect();
	CloseHandle(m_hEvent);
	delete m_pszSlotname;

}

CMailslot::CMailslot(HANDLE &hSlot,LPTSTR lpszSlotName)
{
	if(m_hMailSlot != INVALID_HANDLE_VALUE)
	{	
		hSlot = CreateMailslot(lpszSlotName,0,MAILSLOT_WAIT_FOREVER, (LPSECURITY_ATTRIBUTES) NULL);
	}
	if(hSlot == INVALID_HANDLE_VALUE)
	{
		printf("CreateMailSlot failed with %d\n", GetLastError());
	}
	else printf("Mailslot created successfully. \n");
	m_hMailSlot = hSlot;
	m_pszSlotname = lpszSlotName;
}
void CMailslot::Disconnect()
{
	if (m_hMailSlot != INVALID_HANDLE_VALUE)
		CloseHandle(m_hMailSlot);

	m_hMailSlot = INVALID_HANDLE_VALUE;
}
