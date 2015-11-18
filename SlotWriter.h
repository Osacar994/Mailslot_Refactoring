#pragma once
#include "Mailslot.h"
/*
Herencia de Implementación:
Acá hay una herencia de TDC a TDC, lo cual es un error a uno de los principios de diseño.
Nunca debe usarse este tipo de Herencias, Ante esta problematica debe utilizarse
el metodo de segregación de Interfacez.
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

