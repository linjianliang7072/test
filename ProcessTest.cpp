// ProcessTest.cpp : ���x����̨���ó�ʽ���M���c��
//

#include "stdafx.h"
#include <windows.h>
#include "stdio.h"
#include <tlhelp32.h>
#include "Psapi.h"
#include <ctype.h>

bool IsProcessExist(TCHAR *exe_name)
{
	int num = 0;
	
	PROCESSENTRY32 pe32;//���ڴ�Ž�����Ϣ�Ľṹ��
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//�������̿���

	pe32.dwSize = sizeof(pe32);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bool exist = false;

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);//��ȡ��һ��������Ϣ��pe32�ṹ����

	while (bMore)
	{
		for (int i = 0; i < sizeof(pe32.szExeFile); i++)
			pe32.szExeFile[i] = towupper(pe32.szExeFile[i]);
		printf("name: %ls, num: %d, IDs: %d\n", pe32.szExeFile, num, pe32.th32ProcessID);

		if (!_tcscmp(exe_name, pe32.szExeFile))//����ҪѰ�ҵĽ��̺��������
		{
			exist = true;
			break;
		}
		num++;
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);

	return exist;
}

int main()
{
	/*
	int num = 0;
	TCHAR exe_name[20] = _T("sublime_text.exe");//Ҫ��ѯ�Ľ�����

	PROCESSENTRY32 pe32;//���ڴ�Ž�����Ϣ�Ľṹ��
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//�������̿���

	pe32.dwSize = sizeof(pe32);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed!\n");
		return -1;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);//��ȡ��һ��������Ϣ��pe32�ṹ����

	while (bMore)
	{
		printf("name: %ls, num: %d, IDs: %d\n", pe32.szExeFile, num, pe32.th32ProcessID);

		if (!_tcscmp(exe_name, pe32.szExeFile))//����ҪѰ�ҵĽ��̺��������
		{
			printf("find the file you want: %ls\n", pe32.szExeFile);
			break;
		}
		num++;
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	*/

	bool check = IsProcessExist(_T("SUBLIME_TEXT.EXE"));

	printf("check: %d\n", check);

	getchar();

    return 0;
}

