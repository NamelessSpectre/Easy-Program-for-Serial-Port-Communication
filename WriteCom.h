#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int WriteCom(LPCWSTR PcComPort)
{
	if (PcComPort == NULL)
	{
		printf("Receiving serial port error!\n");
		return 1;
	}

	HANDLE handleCom;
	DCB dcb;
	BOOL IfSuccess;
	char SendBuffer[128] = "Test";
	DWORD dw_BytesWrite = 4;

	handleCom = CreateFile(PcComPort, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (handleCom == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open the serial port!\n");
		CloseHandle(handleCom);
		return 1;
	}

	IfSuccess = GetCommState(handleCom, &dcb);
	if (!IfSuccess)
	{
		printf("Failed to get status\n");
		CloseHandle(handleCom);
		return 1;
	}

	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	IfSuccess = SetCommState(handleCom, &dcb);

	if (!IfSuccess)
	{
		printf("Failed to set the state\n");
		CloseHandle(handleCom);
		return 1;
	}

	printf("Serial port connected\n");
	printf("BaudRate：%d，ByteSize：%d，Parity：%d，StopBits：%d\n", dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);

	printf("Input content:\n");
	cin >> SendBuffer;
	dw_BytesWrite = sizeof(SendBuffer);


	IfSuccess = WriteFile(handleCom, SendBuffer, dw_BytesWrite, &dw_BytesWrite, NULL);
	if (!IfSuccess)
	{
		printf("Failed to write\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("Write successfully!\n");
	}

	CloseHandle(handleCom);
	printf("Serial port closed\n");

	return 0;
}
