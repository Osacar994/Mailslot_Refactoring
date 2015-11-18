#pragma once
#include "Mailslot.h"
/*
Herencia de Implementación:
Acá hay una herencia de TDC a TDC, lo cual es un error a uno de los principios de diseño.
Nunca debe usarse este tipo de Herencias, Ante esta problematica debe utilizarse
el metodo de segregación de Interfacez.
*/

class CSlotReader : public CMailslot 
{
public:
	CSlotReader(HANDLE &hSlot,LPTSTR lpszSlotName);
	virtual ~CSlotReader(void);
	virtual bool Read();
	bool Connect();
private:
	CSlotReader(void);
	CSlotReader(const CSlotReader &sw);
	CSlotReader& operator = (const CSlotReader &sw);
};

