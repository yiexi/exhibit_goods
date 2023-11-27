/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: manger_log_on.c
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月16日 星期四 14时30分19秒
***************************************************/

#include "manger_log_on.h"
#include "exhibit_goods.h"
#include "interface_vending_machine.h"

void Creat()//注册账号
{
	int flag=1;
	Users use1;
	Users use2;//结构体 The_users 重命名定义
	FILE *fp = NULL;
	FILE *fp_record=NULL;
	fp = fopen("users1.txt","a+");
	if(fp==NULL)
	{
		perror("fopen");
		exit(1);
	}
	fp_record=fopen("users_record.txt","a+");
	if(fp_record==NULL)
	{
		perror("fopen");
		exit(1);
	}
	fclose(fp_record);
	char temp[20] = {0};
//	int count = 0;
	printf("欢迎来到注册界面！\n");
	while(1)
	{
		flag=0;
		printf("请输入账号：\n");
		scanf("%s",use1.id);
		rewind(fp);
		while(!feof(fp))
		{
			fread(&use2,sizeof(Users),1,fp);
			if(strcmp(use1.id,use2.id)==0)
			{
				flag=1;
				printf("此用户名已存在！请重新注册！\n");
				break;
			}
			
		}
		if(flag==0)
		{
			break;
		}
	}
	fclose(fp);
	printf("请输入昵称：\n");
	scanf("%s",use1.name);
	printf("请输入密码：\n");
	scanf("%s",use1.pwd);
	printf("请确认密码：\n");
	scanf("%s",temp);
	do
	{
		if(!strcmp(use1.pwd,temp))
		{
			fp = fopen("users1.txt","a");
			fp_record=fopen("users_record.txt","a+");
			fwrite(&use1, sizeof(Users),1,fp);
			fprintf(fp_record,"%-4s %-4s %-4s\n",use1.id,use1.name,use1.pwd);
			printf("账号注册成功，请登录！\n");
			fclose(fp);
			fclose(fp_record);
			break;
		}
		else
		{
			printf("两次密码不匹配！请重新输入！\n");
			scanf("%s",use1.pwd);
			printf("请确认密码\n");
			scanf("%s",temp);
		}
	}while(1);
//	manger_operate(temp);
}
void GetDataFromTxt(Users* data, const char* filename, int* n) //读取文件账号,统计账号个数
{
	FILE *fp = fopen(filename, "a+");//读取
	if( NULL == fp )
	{
		perror("fopen");
		exit(1);
	}
	int i = 0;
	while((fscanf(fp, "%s %s %s", data[i].id, data[i].name, data[i].pwd))!=EOF )//统计
	{
		i++;
	}
	*n = i;
}

void login_first()//用户登录函数
{
	int i,n;
	Users data[100];
	GetDataFromTxt(data, "users_record.txt", &n);//得到文件中账号的个数
	printf("n = %d\n", n);
	printf("账号\t昵称\t密码\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\n",data[i].id,data[i].name,data[i].pwd);//打印已经注册的账号信息正式使用时可以注释调
		putchar('\n');
	}
	char id[20]={0};
	char name[20]={0};
	char pwd[20]={0};
	do
	{
		printf("请输入账号：");
		scanf("%s", id);
		printf("请输入昵称：");
		scanf("%s", name);
		printf("请输入密码：");
		scanf("%s", pwd);
		for(i = 0; i < n; ++i)
		{
			if( strcmp(id,data[i].id)==0 && strcmp(pwd,data[i].pwd)==0 )//登陆界面输入的账号密码与记录在册的进行比较
			{
				printf("登陆成功！\n");
				break;
			}
		}
		if( i == n )
		{
			printf("账号或密码不正确！请重新输入！\n\n");
		}
		else
		{
			break;
		}
	}
	while(1);
}
