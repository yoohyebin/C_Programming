#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "des.h"

static FILE *key_file, *input_file, *output_file;

#define ACTION_GENERATE_KEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"
#define DES_KEY_SIZE 8

void Des_En(char *data_block, char *des_key, char *processed_block)
{
	key_set* key_sets = (key_set*)malloc(17 * sizeof(key_set));

	process_message(data_block, processed_block, key_sets, 1);
	memset(data_block, 0, 8);
	free(key_sets);
}

void Des_De(char *data_block, char *des_key, char *processed_block)
{
	key_set* key_sets = (key_set*)malloc(17 * sizeof(key_set));
	process_message(data_block, processed_block, key_sets, 0);
	memset(data_block, 0, 8);
	free(key_sets);
}

void des_fold_find()
{
	char folder[260];
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", folder1[260], folder2[260], a[4], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* des_key = (unsigned char*)malloc(9 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 8:");
	scanf("%s", des_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, ".\\%s\\en_%s_.exe", folder, fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, ".\\%s\\en_%s_.PNG", folder, fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, ".\\%s\\en_%s_.txt", folder, fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fwrite(data_block, 1, 8, output_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				Des_En(data_block, des_key, prossed_block);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void des_fold_re()
{
	char folder[260];
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", str1[260] = "", folder1[260], folder2[260], a[4], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* des_key = (unsigned char*)malloc(9 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 8:");
	scanf("%s", des_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, ".\\%s\\%s", folder, str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fread(data_block, 1, 8, input_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				Des_De(data_block, des_key, prossed_block);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void des()
{
	int menu;
	printf("\n----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		des_fold_find();
		break;
	case 2:
		des_fold_re();
		break;
	}
}