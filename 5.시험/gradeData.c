#include <stdio.h>
#include <Windows.h>
typedef struct Score
{
	char major[1024], id[1024], name[1024], name_s[20][1024];
	int grade, num_s, score[20], t_gs, total;
	double a, a_s;
}score;
typedef struct Score1
{
	char id[50], name[50], major[50], subject[50][100];
	int grade, s[10], num_s, total;
	double a, t;
}score1;

void swap(score1 std[], int p, int r)
{
	score1 temp;
	temp = std[p];
	std[p] = std[r];
	std[r] = temp;
}

void mergesort_m(score1 std[], int p, int q, int r)
{
	int i = 0, j = 0;
	for (i = p; i <= q; i++)
	{
		for (j = r; j > q; j--)
		{
			if (std[i].a<std[j].a)
				swap(std, i, j);
		}
	}
}

void merge_m(score1 std[], int p, int r)
{
	int q = 0;
	if (p < r) {
		q = (p + r) / 2;
		merge_m(std, p, q);
		merge_m(std, q + 1, r);
		mergesort_m(std, p, q, r);
	}
}
void gradeData()
{
	FILE *fp = fopen("201702_score.txt", "rt");
	FILE *fp1 = fopen("score.txt", "wt");
	score std[50];
	char b[100];
	int menu, a, i = 0, j = 0, k, count = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %d %d %d", std[i].major, std[i].id, std[i].name, &std[i].grade, &std[i].num_s, &std[i].t_gs);
		printf("%s %s %s %d %d %d", std[i].major, std[i].id, std[i].name, std[i].grade, std[i].num_s, std[i].t_gs);
		for (j = 0; j < std[i].num_s; j++)
		{
			fscanf(fp, " %s %d", std[i].name_s[j], &std[i].score);
			printf(" %s %d", std[i].name_s[j], std[i].score);
		}
		fscanf(fp, " %d %lf %lf", &std[i].total, &std[i].a_s, &std[i].a);
		printf(" %d %lf %lf", std[i].total, std[i].a_s, std[i].a);
		i++;
	}
	while (1)
	{
		count = 0;
		printf("\n-------------------------\n");
		printf("성적 데이터 처리 프로그램\n");
		printf("--------------------------\n");
		printf("1.학괴/학생/교과목 정보 검색\n");
		printf("  1.1학과별 데이터 검색\n");
		printf("  1.2과목별 데이터 검색\n");
		printf("  1.3학과/학년별 데이터 검색\n");
		printf("  1.4학번검색\n");
		printf("  1.5이름 검색\n");
		printf("2.성적 데이터 출력 처리\n");
		printf("  2.1 교과목별 성적 데이터 출력\n");
		printf("  2.2 학과/학년별 성적 데이터 출력\n");
		printf("3.종료\n");
		printf("-------------------------\n");
		printf("메뉴를 입력하시오:");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			printf("--------------------------\n");
			printf("1학과별 데이터 검색\n");
			printf("2과목별 데이터 검색\n");
			printf("3학과/학년별 데이터 검색\n");
			printf("4학번검색\n");
			printf("5이름 검색\n");
			printf("--------------------------\n");
			printf("메뉴를 입력하시오:");
			scanf("%d", &a);
			if (a == 1)
			{
				printf("검색할 학과입력:");
				scanf("%s", b);
				for(k=0;k<i;k++)
					if ((std[k].major, b) == 0)
					{
						printf("이름:%s 학번:%s 학과:%s 학년:%d 평점평균:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 2)
			{
				printf("검색할 과목입력:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].name_s, b) == 0)
					{
						printf("이름:%s 학번:%s 학과:%s 학년:%d 평점평균:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 3)
			{
				
			}
			else if (a == 4)
			{
				printf("검색할 학번입력:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].id, b) == 0)
					{
						printf("이름:%s 학번:%s 학과:%s 학년:%d 평점평균:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 5)
			{
				printf("검색할 이름입력:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].name, b) == 0)
					{
						printf("이름:%s 학번:%s 학과:%s 학년:%d 평점평균:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			break;
		case 2:
			printf("--------------------------------\n");
			printf("1 교과목별 성적 데이터 출력\n");
			printf("2 학과/학년별 성적 데이터 출력\n");
			printf("--------------------------------\n");
			printf("메뉴를 입력하시오:");
			scanf("%d", &a);
			
		default:
			return 0;
		}
	}
}