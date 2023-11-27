/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: exhibit_goods.c
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月16日 星期四 14时36分30秒
***************************************************/
#include "exhibit_goods.h"
#include "interface_vending_machine.h"

CONTAINER* find_end_point(CONTAINER*head)
{
	CONTAINER*end=head;//end末尾
	while(end->next!=NULL)
	{
		end=end->next;
	}
	return end;
}

CONTAINER* goods_grounding(CONTAINER* head, int len)//上货
{
	int i = 0;
	CONTAINER* end = head;// head头，end末尾
	head = NULL;//清空head,以保证输入的信息从head开始
	CONTAINER* temp = NULL; // temp当前遍历值
	if (head == NULL) { // 如果head为空，即链表为空
		CONTAINER* new_goods = (CONTAINER*)malloc(SIZE);
		memset(new_goods, 0, SIZE);
		
		printf("请输入商品名称：\n");
		scanf("%s", new_goods->name);
		printf("上架商品价格：\n");
		scanf("%f", &new_goods->price);
		printf("请输入上架商品数量：\n");
		scanf("%d", &new_goods->number);
		
		new_goods->id = 1; // 第一个商品的编号为1
		new_goods->next = NULL;
		
		head = new_goods;
		end = new_goods;
	}
	
	end = find_end_point(end); // end为尾
	for (i = 0; i < len-1; i++) 
	{
		CONTAINER* new_goods = (CONTAINER*)malloc(SIZE);
		memset(new_goods, 0, SIZE);
		// 编号递增
		new_goods->id = end->id + 1; // 末尾值+1
		int flag = 1;
		while (flag) 
		{
			printf("请输入商品名称：\n");
			scanf("%s", new_goods->name);
			
			temp = head; // 每次进入时初始化
			while (temp != NULL) 
			{
				// if判断商品是否重复
				if (strcmp(temp->name, new_goods->name) == 0) 
				{
					printf("商品已经上架\n");
					flag = 1;
					break;
				}
				flag = 0;
				temp = temp->next;
			}
		}
		printf("请输入上架商品价格：\n");
		scanf("%f", &new_goods->price);
		printf("请输入上架商品数量：\n");
		scanf("%d", &new_goods->number);
		// 尾插
		if (head == NULL)
		{
			head = new_goods;
			end = new_goods;
		}
		else
		{
			end->next = new_goods;
			new_goods->next = NULL;
			end = end->next;
		}
	}
	goodsInfo_write_file(head);
	return head;
}

CONTAINER* find_id(CONTAINER*head,int id,int len)//通过商品编号查找商品信息
{
	int flag = 0;
	CONTAINER*temp = head;
	CONTAINER* bef=temp;
	
	CONTAINER* value = NULL;
	
	while(temp!=NULL){	//查找id及位置
		if(id==temp->id){	//找到id
			printf("请查看商品信息\n");
			printf("id:\t%d\t\n",temp->id);
			printf("商品:\t%s\t\n",temp->name);
			printf("价格:\t%.2f\t\n",temp->price);
			printf("数量:\t%d\t\n",temp->number);
			flag = 1;
			break;
		}
		bef=temp;
		temp=temp->next;
	}
	if(len==0&&flag == 1)
	{	//当前位置
		value = temp;	
	}else if(len!=0&&flag == 1)
	{		//前一个位置
		value = bef;
	}
	
	//未找到
	if(flag == 0)
	{
		printf("未找到\n");
		value = head;
	}
	return value;
}

CONTAINER *goods_replenishment(CONTAINER*head)//补货
{
	CONTAINER* temp=head;
	char verify[10]={0};	//验证信息
	int key=0;		//退出死循环钥匙	
	int id=0;
	int num = 0;
	while(1)
	{
		printf("请输入商品编号\n");
		scanf("%d",&id);
		temp=find_id(temp,id,0);
		if(temp!=NULL)
		{
			printf("请输入'Y'or'N'\n");
			scanf("%s",verify);	//确认信息
			if(strcmp(verify,"Y") == 0||strcmp(verify,"y") == 0)
			{
				//具体修改的内容					
				printf("请输入添加货物数量:\n");
				scanf("%d",&num);
				temp->number=temp->number+num;
				key=1;	//修改成功
			}
		}	
		if(key==1)
		{	//判断是否修改成功
			break;	
		}
		else
		{
			printf("Input error\n""Please input again\n");
		}
	}
	goodsInfo_write_file(head);
	return head;
}
CONTAINER *goods_price_modify(CONTAINER *head)//修改商品价格
{
	CONTAINER* temp = head;
	char verify[10] = {0};    //验证信息
	int key = 0;        //退出死循环钥匙
	int id = 0;
	while(1)
	{
		printf("请输入商品编号\n");
		scanf("%d", &id);
		temp = find_id(temp, id, 0);
		if(temp != NULL)
		{
			printf("请输入'Y'or'N'\n");
			scanf("%s", verify);    //确认信息
			if(strcmp(verify, "Y") == 0 || strcmp(verify, "y") == 0)
			{
//具体修改的内容
				printf("请输入需要修改的价格:\n");
				scanf("%f", &temp->price);
				key = 1;    //修改成功
			}
		}
		if(key == 1)
		{
//判断是否修改成功
			break;
		}
		else
		{
			printf("Input error\n""Please input again\n");
		}
	}
	goodsInfo_write_file(head);
	return head;
}
CONTAINER* goods_off_shelf(CONTAINER* head)//下架商品
{
	CONTAINER* temp = head;
	CONTAINER* bef = NULL;
	char verify[10] = { 0 }; //验证信息
	int key = 0; //退出死循环钥匙	
	int id = 0;
	while (1)
	{
		printf("请输入商品编号\n");
		scanf("%d", &id);
		bef = find_id(temp,id,-1);
		if (bef != NULL) 
		{
			printf("请输入'Y'or'N'\n");
			scanf("%s", verify); //确认信息
			if (strcmp(verify, "Y") == 0 || strcmp(verify, "y") == 0)
			{
				temp = bef->next;
				bef->next = bef->next->next;
				free(temp);
				temp = NULL;
				key = 1;
			}
		}
		if (key == 1)
		{
			//判断是否下架成功
			break;
		}
		else
		{
			printf("Input error\n""Please input again\n");
		}
	}
	goodsInfo_write_file(head);
	return head;
}


FILE* open_file_goodsInfo(const char *filename, const char *mode)//打开文件
{
	FILE *fp = fopen(filename, mode);
	if (fp == NULL) 
	{
		perror("fopen");
		exit(1);
	}
	return fp;
}

void goodsInfo_write_file(CONTAINER *head) // 将商品信息写入文件
{
	char mode[10]={"w"};
	FILE *fp = open_file_goodsInfo("goods_info.txt", mode); // Open in write mode, overwriting existing contents
	while (head != NULL) 
	{
		fprintf(fp, "id:\t%d\nname:\t%s\nprice:\t%.2f\nnumber:\t%d\n", head->id, head->name, head->price, head->number);
		head = head->next;
	}
	fclose(fp);
}

CONTAINER* goodsOutput_read_file()// 从文件中读取商品信息
{
	char mode[10] = "r";
	FILE* fp = open_file_goodsInfo("goods_info.txt", mode); // Open in read mode
	CONTAINER* head = NULL; // Initialize the linked list head
	CONTAINER* current = NULL; // Initialize the current node
	while (1)
	{
		CONTAINER* new_node = (CONTAINER*)malloc(sizeof(CONTAINER)); // Allocate memory for a new node
		int scanned = fscanf(fp, "id:\t%d\nname:\t%s\nprice:\t%f\nnumber:\t%d\n", &new_node->id, new_node->name, &new_node->price, &new_node->number);;
//		printf("%d\n",scanned);
		if (scanned == 4)
		{ // If all 4 values are successfully scanned
			new_node->next = NULL;
			if (head == NULL)
			{
				head = new_node;
				current = head;
			}
			else
			{
				current->next = new_node;
				current = new_node;
			} 
		}
		else if (scanned == EOF)
		{ // If end of file is reached
			free(new_node); // Free the unused node
			break;
		}
		else
		{ // If the format does not match
			fprintf(stderr, "Error: Invalid format in the file\n");
			free(new_node); // Free the invalid node
			break;
		}
	}
	
	fclose(fp);
	goodsInfo_write_file(head);	
	return head; // Return the head of the linked list
	
}

void goods_report_form(CONTAINER *head) // 报表
{
	char mode[10]={"w"};
	FILE *fp = open_file_goodsInfo("goods_report_form.txt", mode); // Open in write mode, overwriting existing contents
	while (head != NULL) 
	{
		fprintf(fp, "id:\t%d\nname:\t%s\nprice:\t%.2f\nnumber:\t%d\n", head->id, head->name, head->price, head->number);
		head = head->next;
	}
	fclose(fp);
}
char* get_localtime(char*str)
{
	
	time_t timer = 0;
	time(&timer);
	printf("%ld\n",timer);
	struct tm *sp = NULL;
	sp = localtime(&timer);
	
//	strftime(str,100,"%Y-%m-%d %H:%M:%S",sp);
	
	sprintf(str,"%d/%d/%d %d:%d:%d",sp->tm_year+1900,sp->tm_mon+1,sp->tm_mday,sp->tm_hour,sp->tm_min,sp->tm_sec);
	puts(str);
	return str;
}

char *get_all_info(char *info,int line,char*err,char*itime,char*fun)
{
	sprintf(info,"%s %d %s %s\n",itime,line,err,fun);
	
	return info;
}

void write_file(char*str)
{
	FILE* fd = NULL;
	char tmp[100] = {0};
	char *ssp = NULL;
	char lin[100] = {0};
	char err[100] = {0};
	char fun[100] = {0};
	char info[1000] = {0};
	char *point = NULL;
	time_t timer = 0;
	FILE *fp = fopen("./err.log","a+");
	
	fprintf(fp,"%s",str);
	
	fclose(fp);
}
