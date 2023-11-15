#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int ReadCom(LPCWSTR PcComPort)   // ���մ�������
{
	if (PcComPort == NULL)
	{
		printf("���մ��ڳ���\n");
		return 1;
	}

	HANDLE handleCom;   // ���ھ��
	DCB dcb;   // ���ڲ����ṹ��
	BOOL IfSuccess;   // �ж��Ƿ�ɹ�
	char ReceiveBuffer[128] = { 0 };   // ���ջ�����
	DWORD dw_BytesRead = 0;   // �����ֽ���


	handleCom = CreateFile(PcComPort, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	// ��������α�ʾ���������ơ�����ʽ�򿪡��������ް�ȫ���ԡ��򿪶����Ǵ��������첽I/O����ģ���ļ� 

	if (handleCom == INVALID_HANDLE_VALUE)
	{
		printf("�򿪴���ʧ��\n");
		CloseHandle(handleCom);
		return 1;
	}

	// ��ȡ���ڲ���
	IfSuccess = GetCommState(handleCom, &dcb);
	// ����Ƿ�ɹ�
	if (!IfSuccess)
	{
		printf("��ȡ״̬ʧ��\n");
		CloseHandle(handleCom);
		return 1;
	}

	// ���ô��ڲ���
	dcb.BaudRate = CBR_9600;   // ���ò�����Ϊ9600
	dcb.ByteSize = 8;   // ��������λΪ8
	dcb.Parity = NOPARITY;   // ��������żУ��
	dcb.StopBits = ONESTOPBIT;   // ����ֹͣλΪ1

	// ���ô��ڲ���
	IfSuccess = SetCommState(handleCom, &dcb);

	// ����Ƿ�ɹ�
	if (!IfSuccess)
	{
		printf("���ڲ�������ʧ��\n");
		CloseHandle(handleCom);
		return 1;
	}

	// ��ӡ���ڲ���
	printf("����������\n");
	printf("�����ʣ�%d������λ��%d����żУ��״����%d��ֹͣλ��%d\n", dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);

	// ����������
	IfSuccess = ReadFile(handleCom, ReceiveBuffer, 128, &dw_BytesRead, NULL);
	// ��������α�ʾ�����ھ�������ջ����������ջ�������С��ʵ�ʽ����ֽ�����������OVERLAPPED�ṹ

	// ����Ƿ��ȡ�ɹ�
	if (!IfSuccess)
	{
		printf("��ȡʧ��\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("�����������£�%s\n", ReceiveBuffer);
	}

	// �رմ���
	CloseHandle(handleCom);
	printf("��ȡ��ɣ������ѹر�\n");

	return 0;
}