#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;


int WriteCom(LPCWSTR PcComPort)   // ���մ�������
{
	if (PcComPort == NULL)
	{
		printf("���մ��ڳ���\n");
		return 1;
	}

	HANDLE handleCom;   // ���ھ��
	DCB dcb;   // ���ڲ����ṹ��
	BOOL IfSuccess;   // ��������ֵ
	char SendBuffer[128] = "Test";   // ���ͻ������������ݴ�Ҫ�������ݣ�������send����������д������
	DWORD dw_BytesWrite = 4;   // �����ֽ���

	handleCom = CreateFile(PcComPort, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// ��������α�ʾ���������ơ�д��ʽ�򿪡��������ް�ȫ���ԡ��򿪶����Ǵ��������첽I/O����ģ���ļ�

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

	printf("���������ݣ���������ո񣩣�\n");
	cin >> SendBuffer;
	dw_BytesWrite = sizeof(SendBuffer);


	// д��������
	IfSuccess = WriteFile(handleCom, SendBuffer, dw_BytesWrite, &dw_BytesWrite, NULL);
	// ��������α�ʾ�����ھ�������ͻ������������ֽ�����ʵ�ʷ����ֽ�����������OVERLAPPED�ṹ

	// ����Ƿ�д��ɹ�
	if (!IfSuccess)
	{
		printf("д��ʧ��\n");
		CloseHandle(handleCom);
		return 1;
	}
	else
	{
		printf("���ͳɹ�\n");
	}

	// �رմ���
	CloseHandle(handleCom);
	printf("������ɣ������ѹر�\n");

	return 0;
}
