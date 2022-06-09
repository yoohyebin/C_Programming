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
	printf("이름:");
	gets(data[*count].name);
	sprintf(temp, "%s\n", data[*count].name);
	for(i=0;i<*count;i++)
		if (strcmp(data[i].name, temp) == 0)
		{
			printf("같은 이름이 있습니다 계속 입력 하시겠습니까?(y,n)");
			gets(an);
			if (an[0] == 'y')
				break;
			else
				return;
		}
	printf("전화:");
	gets(data[*count].phone);
	printf("주소:");
	gets(data[*count].add);
	printf("생년월일:");
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
	printf("정보를 삭제할 이름 입력:");
	gets(name);
	sprintf(temp, "%s\n", name);
	for(i=0;i<*count;i++)
		if (strcmp(temp, data[i].name) == 0)
		{
			j++;
			printf("이름:%s전화:%s주소:%s생년월일:%s\n", data[i].name, data[i].phone, data[i].add, data[i].birth);
			printf("정말 삭제하시겠습니까?(y or n)");
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
				printf("삭제되었습니다\n");
				(*count)--;
			}
		}
	if (j == 0)
	{
		printf("입력하신 이름은 없습니다\n");
		return;
	}
	for(i=0;i<*count;i++)
		fprintf(fp, "%s%s%s%s", data[i].name, data[i].phone, data[i].add, data[i].birth);
}
void find(address data[],int count)
{
	int i, j = 0;
	char name[1024], temp[1024];
	printf("검색할 이름 입력:");
	gets(name);
	sprintf(temp, "%s\n", name);
	for(i=0;i<count;i++)
		if (strcmp(data[i].name, temp) == 0)
		{
			printf("이름:%s전화:%s주소:%s생년월일:%s", data[i].name, data[i].phone, data[i].add, data[i].birth);
			j++;
		}
	if (j == 0)
		printf("입력하신 이름은 없습니다\n");
}
void print(address data[],int count)
{
	int i;
	for (i = 0; i < count; i++)
		printf("이름:%s전화:%s주소:%s생년월일:%s\n", data[i].name, data[i].phone, data[i].add, data[i].birth);
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
		printf("--1.입력\n");
		printf("--2.삭제\n");
		printf("--3.검색\n");
		printf("--4.전체 출력\n");
		printf("--5.종료\n");
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