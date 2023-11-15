#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "WriteCom.h"
#include "ReadCom.h"
using namespace std;

int main()
{
	int Acction = 0;
	int Warning = 0;
	LPCWSTR PcComPort = L"COM1";
	while (1)
	{
		Acction = 0;
		if (Acction == 0)
		{
			cout << "Enter the number to proceed to the next step（input 1、2 or 3）" << endl;
			cout << "1.Read  2.Write  3.Quit" << endl;
			cin >> Acction;
		}

		if (Acction == 1)
		{
			ReadCom(PcComPort);
			Warning = 0;
		}
		else if (Acction == 2)
		{
			WriteCom(PcComPort);
			Warning = 0;
		}
		else if (Acction == 3)
		{
			cout << "Program quit successfully" << endl;
			Warning = 0;
			return 0;
		}
		else
		{
			cout << "Illegal import!\n" << endl;
			Acction = 0;
			Warning = Warning + 1;
			if (Warning > 10)
			{
				printf("Warning!Too much wrong!");
				return 1;
			}
		}
	}
}
