// 여러 단어가 담겨있는 'WORD.txt' 파일을 읽어  삽입정렬 방식으로 정렬하고, 'insert.txt'에 저장한다.
#include <stdio.h>
int main()
{
	FILE *fp = fopen("WORD.txt", "rt");
	FILE *fp1 = fopen("insert.txt", "wt");
	if (fp == NULL) exit(1);
	if (fp1 == NULL) exit(1);
	char word[2424][10], copy[10];
	int count = 0, i, j;
	int total = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	for (i = 0; i < count - 1; i++)
	{
		strcpy(copy, word[i + 1]);
		for (j = i; j >= 0; j--)
		{
			if (strcmp(copy, word[j]) < 0)
				strcpy(word[j + 1], word[j]);
			else
				break;
			total++;
		}
		strcpy(word[j + 1], copy);
	}
	for (i = 0; i < count; i++)
		fprintf(fp1, "%d: %s\n", i + 1, word[i]);
	printf("%d\n", total);
}
