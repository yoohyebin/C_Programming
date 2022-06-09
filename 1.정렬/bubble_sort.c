// 여러 단어가 담겨있는 'WORD.txt' 파일을 읽어 buble sort로 정렬하고, 'bubble.txt'에 저장한다.

int main()
{
	FILE* fp = fopen("WORD.txt", "rt");
	FILE* fp1 = fopen("bubble.txt", "wt");
	if (fp == NULL) exit(1);
	if (fp1 == NULL) exit(1);
	char word[2424][10], temp[10];
	int count = 0, i, j;
	int total = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s", word[count]);
		count++;
	}
	for (j = count; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (strcmp(word[i], word[i + 1]) > 0)
			{
				strcpy(temp, word[i]);
				strcpy(word[i], word[i + 1]);
				strcpy(word[i + 1], temp);
				total++;
			}
		}
	}
	for (i = 0; i < count; i++)
		fprintf(fp1, "%d: %s\n", i + 1, word[i]);
	printf("%d\n", total);
}
