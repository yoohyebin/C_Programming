#include<stdio.h>
#include <io.h>
int findfile(char path[],char filename[])
{
	char temp[1024], temp1[1024];
	int result = 1, len;
	struct _finddata_t fd;
	long handel;
	strcpy(temp, path);
	strcpy(temp1, path);
	handel = _findfirst(temp, &fd);

	if (handel == 1)
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
			printf("%s\n", temp);
			if (strcmp(fd.name, filename) == 0)
			{
				printf("파일이 있습니다\n");
				return 0;
			}
		}
		else if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
			printf("%s\n", temp);
		else
		{
			sprintf(temp1, "%s%s\\*.*", temp, fd.name);
			if (findfile(temp1, filename )== -1)
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