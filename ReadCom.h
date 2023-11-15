#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int ReadCom(LPCWSTR PcComPort)
{
	if (PcComPort == NULL)
	{
		printf("Receiving serial port error\n");
		return 1;
	}

	HANDLE handleCom;
	DCB dcb;
	BOOL IfSuccess;
	char ReceiveBuffer[128] = { 0 };
	DWORD dw_BytesRead = 0;


	handleCom = CreateFile(PcComPort, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (handleCom == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open the serial port\n");
		CloseHandle(handleCom);
		return 1;
	}

	IfSuccess = GetCommState(handleCom, &dcb);
	if (!IfSuccess)
	{
		printf("Failed to get the state\n");
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

	printf("Serial port Connected\n");
	printf("BaudRate：%d，ByteSize：%d，Parity：%d，StopBits：%d\n", dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);

	IfSuccess = ReadFile(handleCom, ReceiveBuffer, 128, &dw_BytesRead, NULL);

	if (!IfSuccess)
	{
		printf("Failed to read\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("Receiving data：%s\n", ReceiveBuffer);
	}

	CloseHandle(handleCom);
	printf("Finish reading\n");

	return 0;
}
