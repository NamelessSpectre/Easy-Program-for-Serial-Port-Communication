#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "写串口.h"
#include "读串口.h"
using namespace std;

int main()
{
	int Acction = 0;
	int Warning = 0;
	LPCWSTR PcComPort = L"COM1";   // 串口名称，CreateFile需要传入LPCWSTR
	while (1)
	{
		Acction = 0;
		if (Acction == 0)
		{
			cout << "串口通信界面，请选择操作（输入1、2、3）" << endl;
			cout << "1.读取内容  2.写入内容  3.退出" << endl;
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
			cout << "程序正常退出" << endl;
			Warning = 0;
			return 0;
		}
		else
		{
			cout << "非法输入，请重试！\n" << endl;
			Acction = 0;
			Warning = Warning + 1;
			if (Warning > 10)
			{
				printf("报错过多，系统自动退出！");
				return 1;
			}
		}
	}
}