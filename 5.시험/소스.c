#include <stdio.h>
#include "aes.h"
#include "aes_f.h"
#include "des.h"
#include "des_f.h"
#include "findfile.h"
#include "tiny.h"
#include "tea.h"
#include "virus.h"
#include "rsa2048.h"
#include "base64.h"
#include "common.h"

int main(int argc,int *argv[])
{
	int menu, a;
	char filename[260];
	while (1)
	{
		printf("\n--------------------------------\n");
		printf("C ������Ʈ �⸻��� ���α׷���\n");
		printf("--------------------------------\n");
		printf("1.�����Է� ���α׷�\n");
		printf("2.��ȣȭ/��ȣȭ ���α׷�\n");
		printf("  2,1 TEA ��ȣȭ/��ȣȭ\n");
		printf("  2,2 DES ��ȣȭ/��ȣȭ\n");
		printf("  2,1 RSA ��ȣȭ/��ȣȭ\n");
		printf("  2,1 AES ��ȣȭ/��ȣȭ\n");
		printf("3.���̷��� ���α׷�\n");
		printf("4.���ϰ˻� ���α׷�\n");
		printf("5.���� ������ ó�� ���α׷�\n");
		printf("--------------------------------\n");
		printf("�޴��� �Է��Ͻÿ� :");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			grade_input();
			break;
	case 2:
			printf("\n--��ȣȭ/��ȣȭ ���α׷�--\n");
			printf("1 TEA ��ȣȭ/��ȣȭ\n");
			printf("2 DES ��ȣȭ/��ȣȭ\n");
			printf("3 RSA ��ȣȭ/��ȣȭ\n");
			printf("4 AES ��ȣȭ/��ȣȭ\n");
			printf("---------------------------\n");
			printf("�Է�:");
			scanf("%d", &a);
			if (a == 1)
				tea();
			else if (a == 2)
				des();
			else if (a == 3)
				rsa();
			else if (a == 4)
				aes();
			else
				break;
			break;
		case 3:
			virus(argv[0]);
			break;
		case 4:
			printf("ã�� ���� �̸� �Է�:");
			scanf("%s", filename);
			if (findfile("c:\\*.*", filename) == 1)
				printf("c ����̺꿡 ���� ����\n");
			if (findfile("d:\\*.*", filename) == 1)
				printf("D ����̺꿡 ���� ����\n");
			break;
		case 5:
			gradeData();
			break;
		default:
			return 0;
		}
	}
}