// 여러 단어가 담겨있는 'WORD.txt' 파일을 읽어  병합정렬 방식으로 정렬하고, 'merge.txt'에 저장한다.
#include <stdio.h>
int total = 0;

void merge(char A[][10], int p, int q, int r)
{
	int i, j;
	char temp[10];
	for (i = p; i <=q; i++)
	{
		for (j = r; j >=q+1; j--)
		{
			if (strcmp(A[i], A[j]) > 0)
			{
				strcpy(temp, A[i]);
				strcpy(A[i],A[j]);
				strcpy(A[j],temp);
				total++;
			}
		}
	}
}
void mergeSort(char A[][10], int p, int r)
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q+1, r);
		merge(A, p, q, r);
	}
}
int main()
{
	FILE *fp = fopen("WORD.txt", "rt");
	FILE *fp1 = fopen("merge.txt", "wt");
	if (fp == NULL) exit(1);
	if (fp1 == NULL) exit(1);
	char word[2424][10];
	int count = 0, i, j;

	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	mergeSort(word, 0, count-1);
	for (i = 0; i < count; i++)
		fprintf(fp1, "%d: %s\n", i + 1, word[i]);
	printf("%d\n", total);
}
