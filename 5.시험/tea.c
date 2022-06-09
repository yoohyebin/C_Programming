#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include "tiny.h"
#include <stdint.h>
void tiny_en(uint32_t * v, uint32_t * k)
{
	uint32_t v0 = v[0], v1 = v[1], sum = 0, i;
	uint32_t delta = 0x9e3779b9;
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
	for (i = 0; i < 32; i++)
	{
		sum += delta;
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
	}
	v[0] = v0; v[1] = v1;
}
void tiny_de(uint32_t * v, uint32_t * k)
{
	uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;
	uint32_t delta = 0x9e3779b9;
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
	for (i = 0; i < 32; i++)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;
	}
	v[0] = v0; v[1] = v1;
}
void tiny_fold_find()
{
	char folder[260];
	struct _finddata_t fd;
	long handle;
	int result = 1, i, j, len = 0;
	char str[260] = "", folder1[260], folder2[260], a[4], b[260];
	FILE *en_file = fopen("title.exe", "rb");
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* tiny_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", tiny_key);

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
				memcpy(prossed_block, data_block, 8);
				tiny_en(prossed_block, tiny_key);
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
void tiny_fold_re()
{
	char folder[260];
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", str1[260] = "", folder1[260], folder2[260], a[260], b[260];
	FILE *en_file = fopen("title.exe", "rb");
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* tiny_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", tiny_key);

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
				memcpy(prossed_block, data_block, 8);
				tiny_de(prossed_block, tiny_key);
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
void tea()
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
		tiny_fold_find();
		break;
	case 2:
		tiny_fold_re();
		break;
	}
}