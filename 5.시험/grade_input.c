#include <stdio.h>
#include <Windows.h>
void grade_input()
{
	char major[1024], id[1024], name[1024], name_s[20][1024];
	int grade, num_s, s_score[20], score[20], i = 0, t_gs=0, total = 0, t_a = 0;
	double a = 0;
	int menu;
	FILE *fp = fopen("201702_score.txt", "at");
	while (1)
	{
	printf("\n---------------------\n");
	printf("성적처리 프로그램\n");
	printf("---------------------\n");
	printf("1.학생 정보 입력\n");                                           
	printf("2.학생 정보 출력\n");
	printf("3.수강 신청 입력\n");
	printf("4.수강신청 정보 출력\n");
	printf("5.성적 입력\n");
	printf("6.파일저장\n");
	printf("7.종료\n");
	printf("---------------------\n");
	printf("메뉴를 입력하시오:");
	scanf("%d", &menu);
	
		switch (menu)
		{
		case 1:
			printf("학과 입력:");
			scanf("%s", major);
			printf("학번 입력:");
			scanf("%s", id);
			printf("성명 입력:");
			scanf("%s", name);
			printf("학년 입력:");
			scanf("%d", &grade);
			break;
		case 2:
			printf("학과:%s 학번:%s 성명:%s 학년:%d\n", major, id, name, grade);
			break;
		case 3:
			printf("학번 입력:");
			scanf("%s", id);
			printf("수강교과목수 입력:");
			scanf("%d", &num_s);
			for (i = 0; i < num_s; i++)
			{
				printf("교과목명 입력:");
				scanf("%s", name_s[i]);
				getchar();
				printf("교과목 학점 입력:");
				scanf("%d", &s_score[i]);
				getchar();
				t_gs += s_score[i];
				
			}
			break;
		case 4:
			printf("하번:%s 수강교과목수:%d ", id, num_s);
			for (i = 0; i < num_s; i++)
			{
				printf("%s %d학점 ", name_s[i], s_score[i]);
			}
			break;
		case 5:
			for (i = 0; i < num_s; i++)
			{
				printf("%s점수:", name_s[i]);
				scanf("%d", &score[i]);
				total += score[i];
				if (score[i] <= 100 && score[i] >= 95) //A+
					t_a += s_score[i] * 4.5;
				else if (score[i] < 95 && score[i] >= 90)//A
					t_a += s_score[i] * 4.0;
				else if (score[i] < 90 && score[i] >= 85)//B+
					t_a += s_score[i] * 3.5;
				else if (score[i] < 85 && score[i] >= 80)//b
					t_a += s_score[i] * 3.0;
				else if (score[i] < 80 && score[i] >= 75) //c+
					t_a += s_score[i] * 2.5;
				else if (score[i] < 75 && score[i] >= 70)//c
					t_a += s_score[i] * 2.0;
				else if (score[i] < 70 && score[i] >= 65)//d+
					t_a += s_score[i] * 1.5;
				else if (score[i] < 65 && score[i] >= 60)//d
					t_a += s_score[i] * 1.0;
			}
			a = (double)t_a / t_gs;
			break;
		case 6:
			fprintf(fp, "%s %s %s %d %d %d", major, id, name, grade, num_s, t_gs);
			for (i = 0; i < num_s; i++)
			{
				fprintf(fp, " %s %d", name_s[i], score[i]);
			}
			fprintf(fp, " %d %.2lf %.2lf\n", total, (double)total / num_s, a);
			total = 0;
			t_a = 0;
			t_gs = 0;
			break;
		case 7:fclose(fp); return 0;
		}
	}
}