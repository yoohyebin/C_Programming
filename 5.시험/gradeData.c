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
		printf("���� ������ ó�� ���α׷�\n");
		printf("--------------------------\n");
		printf("1.�б�/�л�/������ ���� �˻�\n");
		printf("  1.1�а��� ������ �˻�\n");
		printf("  1.2���� ������ �˻�\n");
		printf("  1.3�а�/�г⺰ ������ �˻�\n");
		printf("  1.4�й��˻�\n");
		printf("  1.5�̸� �˻�\n");
		printf("2.���� ������ ��� ó��\n");
		printf("  2.1 ������ ���� ������ ���\n");
		printf("  2.2 �а�/�г⺰ ���� ������ ���\n");
		printf("3.����\n");
		printf("-------------------------\n");
		printf("�޴��� �Է��Ͻÿ�:");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			printf("--------------------------\n");
			printf("1�а��� ������ �˻�\n");
			printf("2���� ������ �˻�\n");
			printf("3�а�/�г⺰ ������ �˻�\n");
			printf("4�й��˻�\n");
			printf("5�̸� �˻�\n");
			printf("--------------------------\n");
			printf("�޴��� �Է��Ͻÿ�:");
			scanf("%d", &a);
			if (a == 1)
			{
				printf("�˻��� �а��Է�:");
				scanf("%s", b);
				for(k=0;k<i;k++)
					if ((std[k].major, b) == 0)
					{
						printf("�̸�:%s �й�:%s �а�:%s �г�:%d �������:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 2)
			{
				printf("�˻��� �����Է�:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].name_s, b) == 0)
					{
						printf("�̸�:%s �й�:%s �а�:%s �г�:%d �������:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 3)
			{
				
			}
			else if (a == 4)
			{
				printf("�˻��� �й��Է�:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].id, b) == 0)
					{
						printf("�̸�:%s �й�:%s �а�:%s �г�:%d �������:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			else if (a == 5)
			{
				printf("�˻��� �̸��Է�:");
				scanf("%s", b);
				for (k = 0; k<i; k++)
					if ((std[k].name, b) == 0)
					{
						printf("�̸�:%s �й�:%s �а�:%s �г�:%d �������:%.1f\n", std[j].name, std[j].id, std[j].major, std[j].grade, std[j].a);
					}
			}
			break;
		case 2:
			printf("--------------------------------\n");
			printf("1 ������ ���� ������ ���\n");
			printf("2 �а�/�г⺰ ���� ������ ���\n");
			printf("--------------------------------\n");
			printf("�޴��� �Է��Ͻÿ�:");
			scanf("%d", &a);
			
		default:
			return 0;
		}
	}
}