#include <stdio.h>
typedef struct Address {
	char name[20];
	char phone[20];
	char add[100];
	char birth[20];
}address;
void input(address data[], int *count)
{
	int i;
	char an[2], temp[1024];
	FILE *fp = fopen("address.txt", "at+");
	printf("�̸�:");
	gets(data[*count].name);
	sprintf(temp, "%s\n", data[*count].name);
	for(i=0;i<*count;i++)
		if (strcmp(data[i].name, temp) == 0)
		{
			printf("���� �̸��� �ֽ��ϴ� ��� �Է� �Ͻðڽ��ϱ�?(y,n)");
			gets(an);
			if (an[0] == 'y')
				break;
			else
				return;
		}
	printf("��ȭ:");
	gets(data[*count].phone);
	printf("�ּ�:");
	gets(data[*count].add);
	printf("�������:");
	gets(data[*count].birth);
	fprintf(fp, "%s\n%s\n%s\n%s\n", data[*count].name, data[*count].phone, data[*count].add, data[*count].birth);	
	(*count)++;
	fclose(fp);
}
void del(address data[], int *count)
{
	int i, j = 0, k;
	char name[1024], temp[1024], an[2];
	FILE *fp = fopen("address.txt", "w");
	printf("������ ������ �̸� �Է�:");
	gets(name);
	sprintf(temp, "%s\n", name);
	for(i=0;i<*count;i++)
		if (strcmp(temp, data[i].name) == 0)
		{
			j++;
			printf("�̸�:%s��ȭ:%s�ּ�:%s�������:%s\n", data[i].name, data[i].phone, data[i].add, data[i].birth);
			printf("���� �����Ͻðڽ��ϱ�?(y or n)");
			gets(an);
			if (an[0] == 'y')
			{	
				for (k = i; k < *count-1; k++)
				{
					strcpy(data[k].name, data[k + 1].name);
					strcpy(data[k].phone, data[k + 1].phone);
					strcpy(data[k].add, data[k + 1].add);
					strcpy(data[k].birth, data[k + 1].birth);
				}
				printf("�����Ǿ����ϴ�\n");
				(*count)--;
			}
		}
	if (j == 0)
	{
		printf("�Է��Ͻ� �̸��� �����ϴ�\n");
		return;
	}
	for(i=0;i<*count;i++)
		fprintf(fp, "%s%s%s%s", data[i].name, data[i].phone, data[i].add, data[i].birth);
}
void find(address data[],int count)
{
	int i, j = 0;
	char name[1024], temp[1024];
	printf("�˻��� �̸� �Է�:");
	gets(name);
	sprintf(temp, "%s\n", name);
	for(i=0;i<count;i++)
		if (strcmp(data[i].name, temp) == 0)
		{
			printf("�̸�:%s��ȭ:%s�ּ�:%s�������:%s", data[i].name, data[i].phone, data[i].add, data[i].birth);
			j++;
		}
	if (j == 0)
		printf("�Է��Ͻ� �̸��� �����ϴ�\n");
}
void print(address data[],int count)
{
	int i;
	for (i = 0; i < count; i++)
		printf("�̸�:%s��ȭ:%s�ּ�:%s�������:%s\n", data[i].name, data[i].phone, data[i].add, data[i].birth);
}
void file_address()
{
	char menu[2], readData[100];
	int count = 0;
	address data[1000];
	FILE *fp = fopen("address.txt", "at+");
	while (!feof(fp))
	{
		while (fgets(readData, 100, fp) != NULL)
		{
			strcpy(data[count].name, readData);
			fgets(data[count].phone, 20, fp);
			fgets(data[count].add, 20, fp);
			fgets(data[count].birth, 20, fp);
			count++;
		}
	}
	fclose(fp);
	while(1)
	{	
		printf("------------------\n");
		printf("--1.�Է�\n");
		printf("--2.����\n");
		printf("--3.�˻�\n");
		printf("--4.��ü ���\n");
		printf("--5.����\n");
		printf("------------------\n");
		printf("-->");
		gets(menu);
		switch (menu[0])
		{
		case '1':
			input(&data,&count);
			break;
		case '2':
			del(&data,&count);
			break;
		case '3':
			find(&data, count);
			break;
		case '4':
			print(&data, count);
			break;
		default:
			return;
		}
	}
}