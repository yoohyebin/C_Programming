#include<stdio.h>
#include <Windows.h>
#include <conio.h>
#include <io.h>
int findfile(char path[], char filename[])
{
	char temp[1024], temp1[1024], str[20];
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
			printf("%s%s\n", temp,fd.name);
			if (strcmp(fd.name, filename) == 0)
			{
				printf("파일이 있습니다\n");
				main();
			}
		}
		else if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
			printf("%s%s\n", temp,fd.name);
		else
		{
			sprintf(temp1, "%s%s\\*.*", temp, fd.name);
			if (findfile(temp1, filename) == -1)
			{
				len = strlen(temp1);
				temp1[len - 3] = '\0';
			}
		}
		result = _findnext(handel, &fd);
	}
	return 1;
	_findclose(handel);
}