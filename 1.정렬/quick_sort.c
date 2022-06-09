#include <stdio.h>

int total = 0;
int partition(char **A, int p, int r)
{
	int low = p + 1, high = r;
	char pivot[20], temp[20];
	strcpy(pivot, A[p]);
	while (low < high)
	{
		while (strcmp(pivot, A[low]) >= 0 && low <= r)
			low++;
		while (strcmp(pivot, A[high]) <= 0 && high >= p + 1)
			high--;
		if (low <= high)
		{
			strcpy(temp, A[low]);
			strcpy(A[low], A[high]);
			strcpy(A[high], temp);
			total++;
		}
	}
	strcpy(temp, A[p]);
	strcpy(A[p], A[high]);
	strcpy(A[high], temp);
	total++;
	return high;
}

void QS(char **A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition(A, p, r);
		QS(A, p, q - 1);
		QS(A, q + 1, r);
	}
}
int main()
{
	char str[200], filename[256], **word, temp[20], max[20], copy[20];
	int count = 0, i = 0, len[10000], a, j, l;
	printf("입력할 파일이름을 입력하시오.");
	scanf("%s", filename);
	FILE *fp = fopen("WORD.txt", "r");
	FILE *fp1 = fopen(filename, "w");
	if (fp == NULL)
		exit(1);
	while (!feof(fp))
	{
		fscanf(fp, "%s", str);
		len[count] = strlen(str);
		count++;
	}
	rewind(fp);
	word = (char **)malloc(sizeof(char *)*count);
	for (i = 0; i < count; i++)
	{
		*(word + i) = (char *)malloc(sizeof(char) * len[i] + 1);
	}
	count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	QS(word, 0, count - 1);
	for (i = 0; i < count; i++)
		fprintf(fp1, "%d:%s\n", i, word[i]);
	printf("total:%d\n", total);
	fclose(fp);
	fclose(fp1);
}
