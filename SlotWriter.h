#pragma once
#include "Mailslot.h"
/*
Herencia de Implementaci�n:
Ac� hay una herencia de TDC a TDC, lo cual es un error a uno de los principios de dise�o.
Nunca debe usarse este tipo de Herencias, Ante esta problematica debe utilizarse
el metodo de segregaci�n de Interfacez.
*/

class CSlotWriter : public CMailslot
{
public:
	CSlotWriter(HANDLE &hSlot,LPTSTR lpszSlotName);
	virtual ~CSlotWriter(void);
	virtual void Write(LPTSTR lpszMessage);
	bool Connect();
private:
	CSlotWriter(void);
	CSlotWriter(const CSlotWriter &sw);
	CSlotWriter& operator = (const CSlotWriter &sw);
};

