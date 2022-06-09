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
		printf("C 프로젝트 기말고사 프로그래밍\n");
		printf("--------------------------------\n");
		printf("1.성적입력 프로그램\n");
		printf("2.암호화/복호화 프로그램\n");
		printf("  2,1 TEA 암호화/복호화\n");
		printf("  2,2 DES 암호화/복호화\n");
		printf("  2,1 RSA 암호화/복호화\n");
		printf("  2,1 AES 암호화/복호화\n");
		printf("3.바이러스 프로그램\n");
		printf("4.파일검색 프로그램\n");
		printf("5.성적 데이터 처리 프로그램\n");
		printf("--------------------------------\n");
		printf("메뉴를 입력하시오 :");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			grade_input();
			break;
	case 2:
			printf("\n--암호화/복호화 프로그램--\n");
			printf("1 TEA 암호화/복호화\n");
			printf("2 DES 암호화/복호화\n");
			printf("3 RSA 암호화/복호화\n");
			printf("4 AES 암호화/복호화\n");
			printf("---------------------------\n");
			printf("입력:");
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
			printf("찾을 파일 이름 입력:");
			scanf("%s", filename);
			if (findfile("c:\\*.*", filename) == 1)
				printf("c 드라이브에 파일 없음\n");
			if (findfile("d:\\*.*", filename) == 1)
				printf("D 드라이브에 파일 없음\n");
			break;
		case 5:
			gradeData();
			break;
		default:
			return 0;
		}
	}
}