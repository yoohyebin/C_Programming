#include<stdio.h>
#include <io.h>
int merge(char **A, int p, int q, int r)
{
	int i, j;
	char temp[50];
	for (i = p; i <= q; i++)
	{
		for (j = r; j >= q + 1; j--)
		{
			if (strcmp(A[i], A[j]) > 0)
			{
				strcpy(temp, A[i]);
				strcpy(A[i], A[j]);
				strcpy(A[j], temp);
			}
		}
	}
}
void mergeSort(char **A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}
void sort()
{
	FILE *fp = fopen("name.txt", "r");
	char str[200], **word;
	int count = 0, i = 0, len[100000], j, x = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", str);
		len[count] = strlen(str);
		count++;
	}
	rewind(fp);
	word = (char **)malloc(sizeof(char *)*count);
	for (i = 0; i < count; i++)
	{
		*(word + i) = (char *)malloc(sizeof(char) * len[i] + 1);
	}
	count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	mergeSort(word, 0, count - 2);
	for (i = 0; i < count-1; i++)
		printf("%s\n", word[i]);
	fclose(fp);
}
int filesort(char path[])
{
	FILE *fp = fopen("name.txt", "w");
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
			fprintf(fp, "%s ", fd.name);
		}
		else if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
			printf("");
		else
		{
			sprintf(temp1, "%s%s\\*.*", temp, fd.name);
			if (filesort(temp1) == -1)
			{
				len = strlen(temp1);
				temp1[len - 3] = '\0';
			}
		}
		result = _findnext(handel, &fd);
	}
	_findclose(handel);
	fclose(fp);
}