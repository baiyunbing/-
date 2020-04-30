#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data { //声明城市结构体
	char city[20];		//城市 
	int count;			//病患数量
};  

struct pro { //声明省信息结构体
	int index;//标号
	char province[20];  //省份
	int sum;			//病患总数
	int c;				//城市数量
};  

void sortdatacount(struct data a[], int count)//城市数量排序
{
	int i,j;
	struct data temp;
	for (i=0;i<count - 1;i++)
	{
		for (j=0;j<count - i - 1;j++)
		{
			if (a[j].count<a[j+1].count)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void sortdataname(struct data a[], int count)//城市名称排序
{
	int i,j;
	struct data temp;
	for (i=0;i<count - 1;i++)
	{
		for (j=0;j<count - i - 1;j++)
		{
			if (strcmp(a[j].city,a[j+1].city)<0)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}


void sortprocount(struct pro a[], int count)//省病患人数排序
{
	int i,j;
	struct pro temp;
	for (i=0;i<count - 1;i++)
	{
		for (j=0;j<count - i - 1;j++)
		{
			if (a[j].sum<a[j+1].sum)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void sortproname(struct pro a[], int count)//省名称排序
{
	int i,j;
	struct pro temp;
	for (i=0;i<count - 1;i++)
	{
		for (j=0;j<count - i - 1;j++)
		{
			if (strcmp(a[j].province,a[j+1].province)<0)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int i,j,count = 0;//省数量
	FILE *fp = NULL; //写入文件  
	struct data d[30][20];
	struct pro p[30];
	char province[20],city[20];  //省份市
	char pstr[20] = {0};//当前省份
	int c = 0, sum = 0;
	if (argc != 3)
	{
		return 1;
	}
	fp = fopen(argv[1], "r");  //暂时指定打开文件
	if (!fp)
	{
		printf("打开文件失败!\n");//打开文件失败 
	}
	memset(&p, 0, sizeof(struct pro) * 30);
	memset(&d, 0, sizeof(struct data) * 30 * 20);
	while (1)//读文件存入结构体数组
	{
		if (fscanf(fp, "%s\t%s\t%d", province, city, &c) != EOF)
		{
			if (strlen(pstr) == 0) strcpy(pstr, province);
			if (strcmp(pstr,province) == 0)
			{
				strcpy(d[count][p[count].c].city, city);
				d[count][p[count].c].count = c;
				sum += c;//累加病患
				p[count].c++;//累加城市
			}
			else
			{
				strcpy(p[count].province, pstr);
				p[count].index = count;
				p[count].sum = sum;
				strcpy(pstr, province);
				count++;
				sum = c;
				strcpy(d[count][p[count].c].city, city);
				d[count][p[count].c].count = c;
				p[count].c++;//累加城市
			}
		}
		else
		{
			strcpy(p[count].province, pstr);
			p[count].index = count;
			p[count].sum = sum;
			count++;
			break;
		}
	}

	fclose(fp);

	for (i=0;i<count;i++)
	{
		sortdataname(d[i], p[i].c);
		sortdatacount(d[i], p[i].c);
	}

	sortproname(p, count);
	sortprocount(p, count);
	fp = fopen(argv[2], "w");  //暂时指定打开文件
	if (!fp)
	{
		printf("打开文件失败!\n");//打开文件失败 
	}

	for (i = 0; i < count;i++)
	{
		fprintf(fp, "%s\t%d\n", p[i].province, p[i].sum);
		for (j=0;j<p[i].c;j++)
		{
			fprintf(fp, "%s\t%d\n", d[p[i].index][j].city, d[p[i].index][j].count);
		}
	}
	fclose(fp);
	return 0;
}
