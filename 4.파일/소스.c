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
	printf("--1.���� ã��\n");
	printf("--2.���� ����\n");
	printf("--3.���� ��\n");
	printf("--4.�ּҷ�\n");
	printf("--------------------\n");
	printf("-->");
	gets(menu);
	switch (menu[0])
	{
	case '1':
		printf("ã�� ���� �Է�:");
		scanf("%s", &filename);
		if (findfile("*.*", filename) == 1)
			printf("���� ����\n");
		break;
	case '2':
		printf("������ ���� �Է�:");
		scanf("%s", filename);
		sprintf(filename, "%s\\*.*", filename);
		filesort(filename);
		sort();
		break;
	case '3':
		if (file() == 0)
			printf("���� �����Դϴ�\n");
		break;
	case '4':
		file_address();
		break;
	default:
		break;
	}
}