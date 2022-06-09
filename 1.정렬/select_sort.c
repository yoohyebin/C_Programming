#include <stdio.h>
int main()
{
	FILE *fp = fopen("WORD.txt", "rt");
	FILE *fp1 = fopen("select.txt", "wt");
	if (fp == NULL) exit(1);
	if (fp1 == NULL) exit(1);
	char word[2424][10], temp[10], max[10];
	int count = 0, i, j, l;
	int total = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	for (j = count - 1; j >= 0; j--)
	{
		strcpy(max, word[0]);
		l = 0;
		for (i = 0; i < j + 1; i++)
		{
			if (strcmp(max, word[i]) < 0)
			{
				strcpy(max, word[i]);
				l = i;
				total++;
			}
		}
		strcpy(temp, word[j]);
		strcpy(word[j], word[l]);
		strcpy(word[l], temp);
	}
	for (i = 0; i < count; i++)
		fprintf(fp1, "%d: %s\n", i + 1, word[i]);
	printf("%d\n", total);
}
