#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int WriteCom(LPCWSTR PcComPort)   // 接收串口名称
{
	if (PcComPort == NULL)
	{
		printf("接收串口出错！\n");
		return 1;
	}

	HANDLE handleCom;   // 串口句柄
	DCB dcb;   // 串口参数结构体
	BOOL IfSuccess;   // 函数返回值
	char SendBuffer[128] = "Test";   // 发送缓冲区，用来暂存要发送数据，可以用send函数将数据写入其中
	DWORD dw_BytesWrite = 4;   // 发送字节数

	handleCom = CreateFile(PcComPort, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// 传入的依次表示：串口名称、写方式打开、不共享、无安全属性、打开而不是创建、非异步I/O，无模板文件

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

	printf("请输入内容（请勿输入空格）：\n");
	cin >> SendBuffer;
	dw_BytesWrite = sizeof(SendBuffer);


	// 写串口数据
	IfSuccess = WriteFile(handleCom, SendBuffer, dw_BytesWrite, &dw_BytesWrite, NULL);
	// 传入的依次表示：串口句柄、发送缓冲区、发送字节数、实际发送字节数、不适用OVERLAPPED结构

	// 检查是否写入成功
	if (!IfSuccess)
	{
		printf("写入失败\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("发送成功\n");
	}

	// 关闭串口
	CloseHandle(handleCom);
	printf("发送完成，串口已关闭\n");

	return 0;
}
