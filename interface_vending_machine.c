/***************************************************
> Copyright (C) 2023 ==KINGYI== All rights reserved.
> File Name: interface_vending_machine.c
> Author:cor
> Mail:cor_02@163.com 
> Created Time: 2023年11月21日 星期二 15时14分12秒
***************************************************/
#include "interface_vending_machine.h"
#include "manger_log_on.h"
#include "exhibit_goods.h"
#include "user_client.h"
void interface_vending_machine(int temp)
{
	printf("1.购买\n");
	printf("2.管理员\n");
	scanf("%d",&temp);
	switch (temp)
	{
	case 1:
		printf("购买\n");
		interface_buys(temp);
		break;
	case 2:
		printf("管理员\n");
		manger_operate(temp);
		break;
	default:
		printf("无效操作\n");
		break;
	}
}


void interface_buys(int temp)
{
	CONTAINER *head;
	printf("1.购买\n");
	printf("2.退出\n");
	scanf("%d",&temp);
	switch (temp) 
	{
	case 1:
		printf("购买\n");
		head=goodsOutput_read_file();
		head=goods_buy(head);
		interface_buys(temp);
		break;
	case 2:
		printf("退出\n");
		interface_vending_machine(temp);
		break;	
	default:
		printf("无效操作\n");
		break;
	}	
}
void manger_operate(int temp)
{
	printf("1.注册\n");
	printf("2.登录\n");
	printf("3.退出\n");
	scanf("%d",&temp);
	switch (temp)
	{
	case 1:
	//	printf("注册");
		Creat();
		manger_operate(temp);
		break;
		printf("无效操作\n");
	case 2:
		printf("登录\n");
//		Users *head = NULL;
/*		int result = login_first();
		if(result == 1)
		{
			printf("Login successful\n");
		}
		else
		{
			printf("Login failed\n");
		}*/
		login_first();
		interface_manger(temp);
		break;
	case 3:
		printf("退出\n");
		interface_vending_machine(temp);
		break;
	default:
		printf("无效操作\n");
		break;
	}
}
void interface_manger(int temp)
{
	CONTAINER *head;
	head=(CONTAINER*)malloc(sizeof(CONTAINER));
	memset(head,0,sizeof(CONTAINER));
	head->next=NULL;
	printf("1.上货\n");
	printf("2.下架\n");
	printf("3.补货\n");
	printf("4.修改价格\n");
	printf("5.报表\n");
	printf("6.退出\n");
	scanf("%d",&temp);
	switch (temp)
	{
	case 1:
		printf("上货\n");
		head=goodsOutput_read_file();
		head=goods_grounding(head,10);
		interface_manger(temp);
		break;
	case 2:
		printf("下架\n");
		head=goodsOutput_read_file();
		head=goods_off_shelf(head);
		interface_manger(temp);
		break;
	case 3:
		printf("补货\n");
		head=goodsOutput_read_file();
		head=goods_off_shelf(head);
		interface_manger(temp);
		break;
	case 4:
		printf("修改价格\n");
		head=goodsOutput_read_file();
		head=goods_price_modify(head);
		interface_manger(temp);
		break;
	case 5:
		printf("报表\n");
		head=goodsOutput_read_file();
		goods_report_form(head);
		interface_manger(temp);
		break;
	case 6:	
		printf("退出\n");
		manger_operate(temp);
	default:
		printf("无效操作\n");
		break;
	}
}
