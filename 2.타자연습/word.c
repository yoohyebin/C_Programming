#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int time_check()
{
	int t;
	t = 0;
	while (!kbhit())
	{
		t++;
		printf("★"); Sleep(500);
		if (t == 5)
			return 1;
	}
	return 2;
}
int main()
{
	char word[8000][30], answer[20], name[1024];
	int count = 0, i = 0, a = 0, T = 0, F = 0, target[5], flag[5] = { 0 }, j, k, t, l = 0, t_T = 0;
	FILE* fp = fopen("WORD.txt", "rt");
	FILE* fp1 = fopen("result.txt", "at");
	srand(time(NULL));
	if (fp == NULL) exit(1);
	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	printf("플레이어 이름 입력하시오:");
	scanf("%s", name);
	while (1)
	{
		system("cls");
		for (i = 0; i < 5; i++) target[i] = rand() % (count + 1);
		printf("-------------한글 타자 연습 프로그램--------------\n");
		printf("-----------끝내려면 'x'를 입력하시오--------------\n");
		printf("이름:%s 단어수:%d 정답수:%d 오답수:%d 학습날짜: %s\n", name, a, t_T, F, __DATE__);
		for (i = 0; i < 5; i++)
			printf("%s ", word[target[i]]);
		T = 0;
		while (1)
		{
			t = time_check();
			if (t == 1)  continue;;
			scanf("%s", answer);
			if (strcmp(answer, "x") == 0)
			{
				//printf("한글 타자 연습을 종료합니다\n");
				break;
			}
			for (i = 0; i < 5; i++)
			{
				if (strcmp(word[target[i]], answer) == 0)
				{
					flag[T] = i;
					T++;
					t_T++;
				}
			}
			a++;
			if (a - t_T != 0)
				F++;
			system("cls");
			if (T == 5)
				break;
			printf("-------------한글 타자 연습 프로그램--------------\n");
			printf("-----------끝내려면 'x'를 입력하시오--------------\n");
			printf("이름:%s 단어수:%d 정답수:%d 오답수:%d 학습날짜: %s\n", name, a, t_T, F, __DATE__);
			for (i = 0; i < 5; i++)
			{
				k = 0;
				for (j = 0; j < T; j++)
					if (flag[j] == i)
						k++;
				if (k == 0)
					printf("%s ", word[target[i]]);
			}
		}
		if (strcmp(answer, "x") == 0)
		{
			printf("한글 타자 연습을 종료합니다\n");
			break;
		}
	}
	fprintf(fp1, "이름:%8s 단어수:%5d 정답수:%5d 오답수:%5d 학습날짜: %s\n", name, a, T, F, __DATE__);
	fclose(fp);
	fclose(fp1);
}
