#include <stdio.h>
#include "findfile.h"
#include "filesort.h"
#include "file.h"
#include"address.h"

void main()
{
	char menu[2];
	char filename[1024];
	printf("---------------------\n");
	printf("--1.파일 찾기\n");
	printf("--2.파일 정렬\n");
	printf("--3.파일 비교\n");
	printf("--4.주소록\n");
	printf("--------------------\n");
	printf("-->");
	gets(menu);
	switch (menu[0])
	{
	case '1':
		printf("찾을 파일 입력:");
		scanf("%s", &filename);
		if (findfile("*.*", filename) == 1)
			printf("파일 없음\n");
		break;
	case '2':
		printf("정렬할 폴더 입력:");
		scanf("%s", filename);
		sprintf(filename, "%s\\*.*", filename);
		filesort(filename);
		sort();
		break;
	case '3':
		if (file() == 0)
			printf("같은 파일입니다\n");
		break;
	case '4':
		file_address();
		break;
	default:
		break;
	}
}