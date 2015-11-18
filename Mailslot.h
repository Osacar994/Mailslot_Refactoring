#pragma once
#include "stdafx.h";
class CMailslot
{
protected:
	CMailslot(HANDLE &hSlot,LPTSTR lpszSlotName);	
	virtual ~CMailslot(void);	
	HANDLE			m_hMailSlot,
					m_hEvent;
	bool			m_bStop;
	LPTSTR			m_pszSlotname;
	OVERLAPPED	m_overlapped;
public:
	bool IsOpen(void) const {return m_hMailSlot != INVALID_HANDLE_VALUE;}
	virtual void Disconnect(void);
private:
	CMailslot(void);
	CMailslot(const CMailslot &mailslot);
	CMailslot& operator = (const CMailslot &mailslot);
};

