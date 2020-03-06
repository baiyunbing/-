#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data { //�����ṹ��
	char province[20];  //ʡ��
	char city[20];		//���� 
	int count;			//����
};  

int main(int argc, char *argv[])
{
	int i = 0;
	int count = 0;
	FILE *fp = NULL; //д���ļ�  
	struct data d[140];
	char p[20];  //��ǰʡ��
	if (argc != 2)
	{
		return 1;
	}
	fp = fopen(argv[1], "r");  //��ʱָ�����ļ�

	if (!fp)
	{
		printf("���ļ�ʧ��!\n");//���ļ�ʧ�� 
	}
	while (1)//���ļ�����ṹ������
	{
		if (fscanf(fp, "%s\t%s\t%d", &d[i].province, &d[i].city, &d[i].count) != EOF)
		{
			i++;
		}
		else break;
	}

	count = i;
	fclose(fp);

	fp = fopen("yq_out.txt", "w");  //��ʱָ�����ļ�

	if (!fp)
	{
		printf("���ļ�ʧ��!\n");//���ļ�ʧ�� 
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

