#include <stdio.h>
int file()
{
	char filename1[1024], filename2[1024];
	char str1[5], str2[5];
	printf("파일 입력:");
	scanf("%s", filename1);
	printf("비교할 파일 입력:");
	scanf("%s", filename2);
	FILE *fp = fopen(filename1, "r");
	FILE *fp1 = fopen(filename2, "r");
	while (!feof(fp) || !feof(fp1))
	{
		fgets(str1, 5, fp);
		fgets(str2, 5, fp1);
		if (strcmp(str1,str2)==0)
			continue;
		else
		{
			printf("다른 파일 입니다\n");
			return 1;
		}
	}
	return 0;
 }