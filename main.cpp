#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "д����.h"
#include "������.h"
using namespace std;

int main()
{
	int Acction = 0;
	int Warning = 0;
	LPCWSTR PcComPort = L"COM1";   // �������ƣ�CreateFile��Ҫ����LPCWSTR
	while (1)
	{
		Acction = 0;
		if (Acction == 0)
		{
			cout << "����ͨ�Ž��棬��ѡ�����������1��2��3��" << endl;
			cout << "1.��ȡ����  2.д������  3.�˳�" << endl;
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
			cout << "���������˳�" << endl;
			Warning = 0;
			return 0;
		}
		else
		{
			cout << "�Ƿ����룬�����ԣ�\n" << endl;
			Acction = 0;
			Warning = Warning + 1;
			if (Warning > 10)
			{
				printf("������࣬ϵͳ�Զ��˳���");
				return 1;
			}
		}
	}
}