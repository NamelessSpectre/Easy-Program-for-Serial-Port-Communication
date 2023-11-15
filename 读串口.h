#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int ReadCom(LPCWSTR PcComPort)   // 接收串口名称
{
	if (PcComPort == NULL)
	{
		printf("接收串口出错！\n");
		return 1;
	}

	HANDLE handleCom;   // 串口句柄
	DCB dcb;   // 串口参数结构体
	BOOL IfSuccess;   // 判断是否成功
	char ReceiveBuffer[128] = { 0 };   // 接收缓冲区
	DWORD dw_BytesRead = 0;   // 接收字节数


	handleCom = CreateFile(PcComPort, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	// 传入的依次表示：串口名称、读方式打开、不共享、无安全属性、打开而不是创建、非异步I/O，无模板文件 

	if (handleCom == INVALID_HANDLE_VALUE)
	{
		printf("打开串口失败\n");
		CloseHandle(handleCom);
		return 1;
	}

	// 获取串口参数
	IfSuccess = GetCommState(handleCom, &dcb);
	// 检查是否成功
	if (!IfSuccess)
	{
		printf("获取状态失败\n");
		CloseHandle(handleCom);
		return 1;
	}

	// 配置串口参数
	dcb.BaudRate = CBR_9600;   // 设置波特率为9600
	dcb.ByteSize = 8;   // 设置数据位为8
	dcb.Parity = NOPARITY;   // 设置无奇偶校验
	dcb.StopBits = ONESTOPBIT;   // 设置停止位为1

	// 设置串口参数
	IfSuccess = SetCommState(handleCom, &dcb);

	// 检查是否成功
	if (!IfSuccess)
	{
		printf("串口参数设置失败\n");
		CloseHandle(handleCom);
		return 1;
	}

	// 打印串口参数
	printf("串口已连接\n");
	printf("波特率：%d，数据位：%d，奇偶校验状况：%d，停止位：%d\n", dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);

	// 读串口数据
	IfSuccess = ReadFile(handleCom, ReceiveBuffer, 128, &dw_BytesRead, NULL);
	// 传入的依次表示：串口句柄、接收缓冲区、接收缓冲区大小、实际接收字节数、不适用OVERLAPPED结构

	// 检查是否读取成功
	if (!IfSuccess)
	{
		printf("读取失败\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("接收数据如下：%s\n", ReceiveBuffer);
	}

	// 关闭串口
	CloseHandle(handleCom);
	printf("读取完成，串口已关闭\n");

	return 0;
}