// Mailslot_Refactoring01.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "SlotWriter.h"
#include "SlotReader.h"

HANDLE hSlot;
LPTSTR SlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");

int _tmain(int argc, _TCHAR* argv[])
{
	CSlotReader reader(hSlot,SlotName);
	CSlotWriter test(hSlot,SlotName);
	test.Connect();
	test.Write(TEXT("Hola Mundo 1"));
	test.Write(TEXT("Hola Mundo 2"));

	Sleep(300);

	test.Write(TEXT("Hola Mundo 3"));
	reader.Connect();
	while (true)
	{
		reader.Read();
		Sleep(3000);
	}	
	CloseHandle(hSlot);
	system("pause");
	return 0;
}

