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
	printf("����ó�� ���α׷�\n");
	printf("---------------------\n");
	printf("1.�л� ���� �Է�\n");                                           
	printf("2.�л� ���� ���\n");
	printf("3.���� ��û �Է�\n");
	printf("4.������û ���� ���\n");
	printf("5.���� �Է�\n");
	printf("6.��������\n");
	printf("7.����\n");
	printf("---------------------\n");
	printf("�޴��� �Է��Ͻÿ�:");
	scanf("%d", &menu);
	
		switch (menu)
		{
		case 1:
			printf("�а� �Է�:");
			scanf("%s", major);
			printf("�й� �Է�:");
			scanf("%s", id);
			printf("���� �Է�:");
			scanf("%s", name);
			printf("�г� �Է�:");
			scanf("%d", &grade);
			break;
		case 2:
			printf("�а�:%s �й�:%s ����:%s �г�:%d\n", major, id, name, grade);
			break;
		case 3:
			printf("�й� �Է�:");
			scanf("%s", id);
			printf("����������� �Է�:");
			scanf("%d", &num_s);
			for (i = 0; i < num_s; i++)
			{
				printf("������� �Է�:");
				scanf("%s", name_s[i]);
				getchar();
				printf("������ ���� �Է�:");
				scanf("%d", &s_score[i]);
				getchar();
				t_gs += s_score[i];
				
			}
			break;
		case 4:
			printf("�Ϲ�:%s �����������:%d ", id, num_s);
			for (i = 0; i < num_s; i++)
			{
				printf("%s %d���� ", name_s[i], s_score[i]);
			}
			break;
		case 5:
			for (i = 0; i < num_s; i++)
			{
				printf("%s����:", name_s[i]);
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