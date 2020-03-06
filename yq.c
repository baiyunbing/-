#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data { //声明结构体
	char province[20];  //省份
	char city[20];		//城市 
	int count;			//数量
};  

int main(int argc, char *argv[])
{
	int i = 0;
	int count = 0;
	FILE *fp = NULL; //写入文件  
	struct data d[140];
	char p[20];  //当前省份
	if (argc != 2)
	{
		return 1;
	}
	fp = fopen(argv[1], "r");  //暂时指定打开文件

	if (!fp)
	{
		printf("打开文件失败!\n");//打开文件失败 
	}
	while (1)//读文件存入结构体数组
	{
		if (fscanf(fp, "%s\t%s\t%d", &d[i].province, &d[i].city, &d[i].count) != EOF)
		{
			i++;
		}
		else break;
	}

	count = i;
	fclose(fp);

	fp = fopen("yq_out.txt", "w");  //暂时指定打开文件

	if (!fp)
	{
		printf("打开文件失败!\n");//打开文件失败 
	}
	strcpy(p, d[0].province);
	fprintf(fp, "%s\n", p);
	fprintf(fp, "%s\t%d\n", d[0].city, d[0].count);
	for (i = 1; i < count;i++)
	{
		if (strcmp(p, d[i].province) == 0) fprintf(fp, "%s\t%d\n", d[i].city, d[i].count);
		else
		{
			strcpy(p, d[i].province);
			fprintf(fp, "\n%s\n", p); 
			fprintf(fp, "%s\t%d\n", d[i].city, d[i].count);
		}
	}

	fclose(fp);
	return 0;
}

